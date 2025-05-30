#include "DxLib.h"
#include "car.h"
#include "../Utility/InputManager.h"
#include"../Scene/InGame/InGameScene.h"
#include"../Object/map.h"
#include"../Object/tool.h"


#define CAR_TROUT_LNEGTH (80.0f)

int overroad;

void CarStart(const InGame* ingame);
void CarDetectPosition(void);
void GetNextDestination(const Tool* tool);
void OverRoad(void);
void CarGoalCheck(const CreateStage* stage);
void GetBreakRoadPosition(const Tool* tool);
void CutIn(const CreateStage* stage);
void Play_Sound_Car(int sound, int volume);
void CarMovePosition(const CreateStage*stage);


Car car;
GameOver gameover;
void CarInit(void)
{

	overroad = 0;
	car.position.x = car.current_x * CAR_TROUT_LNEGTH + 200.0f;//初期位置
	car.position.y = car.current_y * CAR_TROUT_LNEGTH + 120.0f;
	car.velocity.x = 0.2f;//速度
	car.velocity.y = 0.2f;
	car.direction = eRight;//進行方向
	car.road_count = 0;//取得する道のカウント
	car.next_count = 0;//取得した道の配列番号
	car.goal_flag = false;//ゴールまで道がつながっているかどうか


	gameover.image_flag = false;//GameOverをだすか
	gameover.image_count = 0;//GameOverの画像を出す時間のカウント
	gameover.flag = false;//GameOver後にリセットさせるフラグ


	//画像の読み込み
	car.image[0] = LoadGraph("Resource/images/car2_right.png");
	car.image[1] = LoadGraph("Resource/images/car2_left.png");
	car.image[2] = LoadGraph("Resource/images/car2_up.png");
	car.image[3] = LoadGraph("Resource/images/car2_down.png");

	car.cutin_image[0] = LoadGraph("Resource/images/cutin.png");
	car.cutin_image[1] = LoadGraph("Resource/images/cutin2.png");
	car.cutin_image[2] = LoadGraph("Resource/images/cutin3.png");

	car.ivy_image= LoadGraph("Resource/images/ivy_car_right.png");

	car.warn_se = LoadSoundMem("Resource/Sounds/Warn_se.mp3");
	car.warn_se_flag = false;

	car.start = false;//車の処理フラグ
	car.menu_flag == false;
	
	car.current_x = 2;//ステージ①の初期位置
	car.current_y = 3;
	car.animation = car.image[0];

	//次の目的地の初期化
	for (int i = 0; i < 84; i++)
	{
		car.next_x[i] = -1;
		car.next_y[i] = -1;
	}

	car.next_x[0] = 3;
	car.next_y[0] = 3;
}

void CarManagerUpdate(void)
{
	//車の処理をスタートするフラグ
	CarStart(GetInGame());

	//次の進行場所を取得する
	GetNextDestination(Get_Tool());
	GetBreakRoadPosition(Get_Tool());
	//処理開始がtrueなら
	if (car.start == true && car.menu_flag == false)
	{
		//車の移動処理
		CarGoalCheck(GetStage());
		CarMovePosition(GetStage());

	}
	else if (car.start == false && car.menu_flag == false)
	{
		//ステージ切り替えの時リセットする
		CarReset();
	}


}

void CarDraw(void)
{
	DrawRotaGraph(car.position.x, car.position.y, 0.1, 0.0, car.animation, TRUE);

	/*	DrawFormatString(930, 300, GetColor(255, 255, 255), "%f",car.position.x);
		DrawFormatString(930, 200, GetColor(255, 255, 255), "%f", car.position.y);
		DrawFormatString(930, 100, GetColor(255, 255, 255), "%d", car.x);
		DrawFormatString(930, 150, GetColor(255, 255, 255), "%d", car.direction);*/
	
	/*DrawFormatString(300, 350, GetColor(255, 255, 255), "%d\n%d\n%d", car.next_x[car.road_count], car.next_y[car.road_count], car.road_count);
	DrawFormatString(350, 350, GetColor(255, 255, 255), "%d\n%d\n%d", car.next_x[car.next_count], car.next_y[car.next_count], car.next_count);
	DrawFormatString(400, 350, GetColor(255, 255, 255), "%d\n%d\n%d", car.current_x, car.current_y, car.next_count);
	DrawFormatString(450, 350, GetColor(255, 255, 255), "%f\n%f\n", car.velocity.x, car.velocity.y );*/
	/*DrawFormatString(450, 350, GetColor(255, 255, 255), "%d",gameover.image_count); */
}


//車の処理をスタートするフラグ
void CarStart(const InGame* ingame)
{
	if (ingame->start == true&& ingame->menu_flag == false)
	{
		car.start = true;
	}
	else if (ingame->start == false && ingame->menu_flag == false)
	{
		car.start = false;
	}
	car.menu_flag = ingame->menu_flag;
}

//車の情報を取得
const Car* GetCar(void)
{
	return &car;
}

//ゲームオーバー情報を取得
const GameOver* GetGameOver(void)
{
	return &gameover;
}

//ステージ切り替えするときのリセット
void CarReset(void)
{
	car.current_x = 2;//ステージ①の初期位置
	car.current_y = 3;
	car.position.x = car.current_x * CAR_TROUT_LNEGTH + 200.0f;
	car.position.y = car.current_y * CAR_TROUT_LNEGTH + 120.0f;
	car.direction = eRight;
	car.velocity.x = 0.2f;//速度
	car.velocity.y = 0.2f;
	car.road_count = 0;
	car.next_count = 0;
	car.goal_flag = false;//ゴールまで道がつながっているかどうか
	overroad = 0;
	car.start = false;//車の処理フラグ
	car.warn_se_flag = false;
	car.menu_flag == false;//車のメニュー処理フラグ
	car.current_x = 2;//ステージ①の初期位置
	car.current_y = 3;
	car.animation = car.image[0];

	gameover.image_flag = false;//GameOverをだすか
	gameover.image_count = 0;//GameOverの画像を出す時間のカウント
	gameover.flag = false;//GameOver後にリセットさせるフラグ

	for (int i = 0; i < 84; i++)
	{
		car.next_x[i] = -1;
		car.next_y[i] = -1;
	}
	car.next_x[0] = 3;
	car.next_y[0] = 3;
}

//次の進行場所を取得する
void GetNextDestination(const Tool* tool)
{
	//道が置かれたときの座標を取得して番号をつける
	//次の移動位置が同じでないなら
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			/*car.next_x[car.road_count] != destination->x || car.next_y[car.road_count] != destination->y*/
			if (tool->road_flag[i][j] == true || tool->wood_road_flag[i][j] == true)
			{
				car.road_count++;
				car.next_x[car.road_count] = i;
				car.next_y[car.road_count] = j;


			}
		}
	}
}

//壊すポジションを取得
void GetBreakRoadPosition(const Tool* tool)
{
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			if (tool->road_break_flag[i][j] == true)
			{

				car.next_x[car.road_count] = -1;
				car.next_y[car.road_count] = -1;
				car.road_count--;
			}
		}
	}
}


//車の移動処理
void CarMovePosition(const CreateStage* stage)
{
	switch (car.direction)
	{

	case eStop://止まる
		if (car.goal_flag == false)
		{
			/*car.animation = car.ivy_image;*/
			if (overroad < 400)
			{
				OverRoad();
				gameover.image_flag = true;
				car.animation = car.ivy_image;
			}
			if (overroad > 399)
			{
				gameover.image_count++;
				car.position.x += 0.0f;
				car.position.y += 0.0f;
				/*gameover.image_flag = true;*/

				if (gameover.image_count > 120)
				{
					gameover.flag = true;
					gameover.image_count = 0;
				}
			}
		}
		

		break;
	case eUp://上に
		car.animation = car.image[2];
		car.position.y -= car.velocity.y;
		if (car.position.y < (car.current_y * CAR_TROUT_LNEGTH) + 120.2f)//微調整で120に0.2足している
		{
			//車の現在位置を検知して次の進行方向を決める
			CarDetectPosition();
			
		}
		else if (car.position.y < (car.current_y * CAR_TROUT_LNEGTH) + 150.0f&&
			car.current_y != stage->goal_y[0])
		{
			CarWarnSE();
		}
		break;
	case eDown://下に
		car.animation = car.image[3];
		car.position.y += car.velocity.y;
		if (car.position.y > (car.current_y * CAR_TROUT_LNEGTH) +119.8f)//微調整で120から0.2引いている
		{
			//車の現在位置を検知して次の進行方向を決める
			CarDetectPosition();
			
		}
		else if (car.position.y > (car.current_y * CAR_TROUT_LNEGTH) + 90.0f&&
			car.current_y != stage->goal_y[0])
		{
			CarWarnSE();
		}
		break;
	case eRight://右に
		car.animation = car.image[0];
		car.position.x += car.velocity.x;
		if (car.position.x > (car.current_x * CAR_TROUT_LNEGTH) + 199.8f)//微調整で200から0.2引いている
		{
			//車の現在位置を検知して次の進行方向を決める
			CarDetectPosition();
			
		}
		else if (car.position.x > (car.current_x * CAR_TROUT_LNEGTH) + 170.0f &&
			car.current_x != stage->goal_x[0])
		{
			CarWarnSE();
		}
		break;

	case eLeft:
		car.animation = car.image[1];
		car.position.x -= car.velocity.x;
		if (car.position.x < (car.current_x * CAR_TROUT_LNEGTH) +200.2f)//微調整で200から0.2足している
		{
			//車の現在位置を検知して次の進行方向を決める
			CarDetectPosition();
			
		}
		else if (car.position.x < (car.current_x * CAR_TROUT_LNEGTH) + 230.0f&&
			car.current_x != stage->goal_x[0])
		{
			CarWarnSE();
		}
		break;

	default:
		break;
	}
}

//車の現在位置を検知して次の進行方向を決める
void CarDetectPosition(void)
{

	car.warn_se_flag = false;
	//現在のX位置よりも次のX位置が大きかったら
	if (car.current_x < car.next_x[car.next_count] &&
		car.current_y == car.next_y[car.next_count])
	{
		car.direction = eRight;//右に
		car.old_direction = eRight;
		car.current_x = car.next_x[car.next_count];//現在の位置につぎの位置を格納
		car.current_y = car.next_y[car.next_count];
		car.next_count++;                          //次の位置の配列番号にする
	}
	else if (car.current_x > car.next_x[car.next_count] &&
		car.current_y == car.next_y[car.next_count])
	{
		car.direction = eLeft;//右に
		car.old_direction = eLeft;
		car.current_x = car.next_x[car.next_count];//現在の位置につぎの位置を格納
		car.current_y = car.next_y[car.next_count];
		car.next_count++;
	}
	//現在のY位置よりも次のY位置が小さかったら
	else if (car.current_y > car.next_y[car.next_count] &&
		car.current_x == car.next_x[car.next_count])
	{
		car.direction = eUp;//上に
		car.old_direction = eUp;
		car.current_x = car.next_x[car.next_count];//現在の位置につぎの位置を格納
		car.current_y = car.next_y[car.next_count];
		car.next_count++;                          //次の位置の配列番号にする
	}
	//現在のY位置よりも次のY位置が大きかったら
	else if (car.current_y < car.next_y[car.next_count] &&
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
//GameOver時のアニメーション
void OverRoad(void)
{
	switch (car.old_direction)
	{
	case eUp://上に
		car.animation = car.image[2];
		car.position.y -= 0.1f;
		overroad += 2;
		break;
	case eDown://下に
		car.animation = car.image[3];
		car.position.y += 0.1f;
		overroad += 2;
		break;
	case eRight://右に
		car.animation = car.image[0];
		car.position.x += 0.1f;
		overroad += 2;
		break;
	case eLeft:
		car.animation = car.image[1];
		car.position.x -= 0.1f;
		overroad += 2;
		break;

	default:
		break;
	}
}

void CarGoalCheck(const CreateStage* stage)
{
	//右または上または下にゴールがあるなら
	if (stage->array[car.next_x[car.road_count] + 1][car.next_y[car.road_count]] == 7 ||
		stage->array[car.next_x[car.road_count] - 1][car.next_y[car.road_count]] == 7 ||
		stage->array[car.next_x[car.road_count]][car.next_y[car.road_count] - 1] == 7 ||
		stage->array[car.next_x[car.road_count]][car.next_y[car.road_count] + 1] == 7)
	{
		//車の速度を上げる
		car.velocity.x = 4.0f;
		car.velocity.y = 4.0f;

		//ゴールの配列番号を一番先端に入れる
		car.next_x[car.road_count + 1] = stage->goal_x[0];
		car.next_y[car.road_count + 1] = stage->goal_y[0];
		//ゴールまで道がつながったかどうか
		car.goal_flag = true;
	}
	else
	{
		//ゴール以外の時の速度
		car.velocity.x = 0.1f;
		car.velocity.y = 0.1f;
	}

}

void CutIn(const CreateStage* stage)
{

}

void CarWarnSE(void) 
{
	if (car.next_x[car.next_count] == -1 && car.next_y[car.next_count] == -1&&
		car.warn_se_flag==false)
	{
		Play_Sound_Car(car.warn_se, 100);
		/*PlaySoundMem(car.warn_se, DX_PLAYTYPE_BACK);*/
		car.warn_se_flag = true;
	}
}

void Play_Sound_Car(int sound, int volume)
{
	if (CheckSoundMem(sound) == 0)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);
		ChangeVolumeSoundMem(volume, sound);
	}

}