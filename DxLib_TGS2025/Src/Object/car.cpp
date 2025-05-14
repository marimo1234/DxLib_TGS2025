#include "DxLib.h"
#include "car.h"
#include "../Utility/InputManager.h"
#include"../Scene/InGame/InGameScene.h"
#include"../Object/map.h"


#define CAR_TROUT_LNEGTH (80.0f)

int overroad;

void CarStart(const InGame* ingame);
void CarDetectPosition(void);
void GetNextDestination(const NextDestination* destination);
void OverRoad(void);
void CarGoalCheck(const CreateStage* stage);

Car car;
void CarInit(void)
{

	overroad = 0;
	car.position.x= car.current_x * CAR_TROUT_LNEGTH + 200.0f;//初期位置
	car.position.y= car.current_y * CAR_TROUT_LNEGTH + 120.0f;
	car.velocity.x = 0.2f;//速度
	car.velocity.y = 0.2f;
	car.direction = eRight;//進行方向
	car.road_count = 0;//取得する道のカウント
	car.next_count = 1;//取得した道の配列番号
	car.goal_flag = false;
	car.gameover_image = false;

	car.image[0] = LoadGraph("Resource/images/car_right.png");
	car.image[1] = LoadGraph("Resource/images/car_left.png");
	car.image[2] = LoadGraph("Resource/images/car_up.png");
	car.image[3] = LoadGraph("Resource/images/car_down.png");
	car.gameover = LoadGraph("Resource/images/GAMEOVER.png");
	car.goal = LoadGraph("Resource/images/GOAL.png");
	car.start = false;//車の処理フラグ
	car.goalprint = false;
	car.current_x = 2;//ステージ①の初期位置
	car.current_y = 3;
	
	//次の目的地の初期化
	for (int i = 0; i < 84; i++)
	{
		car.next_x[i] = -1;
		car.next_y[i] = -1;
	}
}

void CarManagerUpdate(void)
{
	//車の処理をスタートするフラグ
	CarStart(GetInGame());
	
	
	//処理開始がtrueなら
	if (car.start == true)
	{
		//車の移動処理
		CarGoalCheck(GetStage());
		CarMovePosition();
		
	}
	else
	{
		//ステージ切り替えの時リセットする
		CarReset();
	}

	//次の進行場所を取得する
	GetNextDestination(GetDestination());
}

void CarDraw(void)
{
		DrawRotaGraph(car.position.x, car.position.y, 0.1, 0.0, car.animation, TRUE);
		DrawFormatString(930, 300, GetColor(255, 255, 255), "%f",car.position.x);
		DrawFormatString(930, 200, GetColor(255, 255, 255), "%f", car.position.y);
		DrawFormatString(930, 100, GetColor(255, 255, 255), "%d", car.x);
		DrawFormatString(930, 150, GetColor(255, 255, 255), "%d", car.direction);
		if (car.gameover_image==true)
		{
			DrawRotaGraphF(615, 380, 1.0, 0.0, car.gameover, TRUE);
		}
		if (car.goalprint == true)
		{
			//ゴールの文字を出す
			DrawRotaGraphF(615,380, 1.0, 0.0, car.goal, TRUE);
		}
		DrawFormatString(300, 350, GetColor(255, 255, 255), "%d\n%d\n%d", car.next_x[car.road_count], car.next_y[car.road_count], car.road_count);
		DrawFormatString(350, 350, GetColor(255, 255, 255), "%d\n%d\n%d", car.current_x, car.current_y, car.next_count);
		DrawFormatString(400, 350, GetColor(255, 255, 255), "%f\n%f\n", car.velocity.x, car.velocity.y );
		
}


//車の処理をスタートするフラグ
void CarStart(const InGame* ingame)
{
	if (ingame->start == true)
	{
		car.start = true;
	}
	else
	{
		car.start = false;
	}
	
}

//車の情報を取得
const Car* GetCar(void)
{
	return &car;
}

//ステージ切り替えするときのリセット
void CarReset(void)
{
	car.position.x = car.current_x * CAR_TROUT_LNEGTH + 200.0f;
	car.position.y = car.current_y * CAR_TROUT_LNEGTH + 120.0f;
	car.direction = eRight;
	car.road_count = 0;
	car.next_count = 1;
}

//次の進行場所を取得する
void GetNextDestination(const NextDestination* destination)
{
	//道が置かれたときの座標を取得して番号をつける
	//次の移動位置が同じでないなら
	if (car.next_x[car.road_count] != destination->x || car.next_y[car.road_count] != destination->y)
	{
			car.road_count++;
			car.next_x[car.road_count] = destination->x;
			car.next_y[car.road_count] = destination->y;
	}
}

//車の移動処理
void CarMovePosition(void)
{
	switch (car.direction)
	{

	case eStop://止まる
		if (car.goal_flag == false)
		{
			if (overroad < 400)
			{
				OverRoad();
			}
			if (overroad > 399)
			{
				car.position.x += 0.0f;
				car.position.y += 0.0f;
				car.gameover_image = true;
			}
		}
		else if (car.goal_flag == true)
		{
			car.goalprint = true;
		}
				
		break;
	case eUp://上に
		car.animation = car.image[2];
		car.position.y -= car.velocity.y;
		if (car.position.y < (car.current_y * CAR_TROUT_LNEGTH) + 120.2f)//微調整で120に1足している
		{
			//車の現在位置を検知して次の進行方向を決める
			CarDetectPosition();
		}
		break;
	case eDown://下に
		car.animation = car.image[3];
		car.position.y += car.velocity.y;
		if (car.position.y > (car.current_y * CAR_TROUT_LNEGTH) + 119.8f)//微調整で120から1引いている
		{
			//車の現在位置を検知して次の進行方向を決める
			CarDetectPosition();
		}
		break;
	case eRight://右に
		car.animation = car.image[0];
		car.position.x += car.velocity.x;
		if (car.position.x > (car.current_x * CAR_TROUT_LNEGTH) + 199.8f)//微調整で200から1引いている
		{
			//車の現在位置を検知して次の進行方向を決める
			CarDetectPosition();
		}
		break;
	
	default:
		break;
	}
}

//車の現在位置を検知して次の進行方向を決める
void CarDetectPosition(void)
{
	//現在のX位置よりも次のX位置が大きかったら
	if (car.current_x < car.next_x[car.next_count]&&
		car.current_y == car.next_y[car.next_count])
	{
		car.direction = eRight;//右に
		car.old_direction = eRight;
		car.current_x = car.next_x[car.next_count];//現在の位置につぎの位置を格納
		car.current_y = car.next_y[car.next_count];
		car.next_count++;                          //次の位置の配列番号にする
	}
	//現在のY位置よりも次のY位置が小さかったら
	else if (car.current_y > car.next_y[car.next_count]&&
		car.current_x == car.next_x[car.next_count])
	{
		car.direction = eUp;//上に
		car.old_direction = eUp;
		car.current_x = car.next_x[car.next_count];//現在の位置につぎの位置を格納
		car.current_y = car.next_y[car.next_count];
		car.next_count++;                          //次の位置の配列番号にする
	}
	//現在のY位置よりも次のY位置が大きかったら
	else if (car.current_y < car.next_y[car.next_count]&&
		car.current_x == car.next_x[car.next_count])
	{
		car.direction = eDown;//下に
		car.old_direction = eDown;
		car.current_x = car.next_x[car.next_count];//現在の位置につぎの位置を格納
		car.current_y = car.next_y[car.next_count];
		car.next_count++;                          //次の位置の配列番号にする
	}
	//次の進行位置がなければストップ
	else
	{
		car.direction = eStop;//ストップ
	}

}
void OverRoad(void)
{
	switch (car.old_direction)
	{
	case eUp://上に
		car.animation = car.image[2];
		car.position.y -= 0.2;
		overroad+=2;
		break;
	case eDown://下に
		car.animation = car.image[3];
		car.position.y += 0.2;
		overroad+=2;
		break;
	case eRight://右に
		car.animation = car.image[0];
		car.position.x += 0.2;
		overroad+=2;
		break;

	default:
		break;
	}
}

void CarGoalCheck(const CreateStage* stage)
{
	//右または上または下にゴールがあるなら
	if (stage->array[car.next_x[car.road_count] + 1][car.next_y[car.road_count]] == 7 ||
		stage->array[car.next_x[car.road_count]][car.next_y[car.road_count] - 1] == 7 ||
		stage->array[car.next_x[car.road_count]][car.next_y[car.road_count] + 1] == 7)
	{
		car.velocity.x = 2.0f;
		car.velocity.y = 2.0f;

		car.next_x[car.road_count + 1] = stage->goal_x[0];
		car.next_y[car.road_count + 1] = stage->goal_y[0];
		car.goal_flag = true;
	}
	else
	{
		car.velocity.x = 0.2f;
		car.velocity.y = 0.2f;
	}


	
}