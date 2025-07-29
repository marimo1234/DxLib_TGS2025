#include "DxLib.h"
#include "car.h"
#include "../Utility/InputManager.h"
#include"../Scene/InGame/InGameScene.h"
#include"../Object/map.h"
#include"../Object/tool.h"
#include"../Object/Goal.h"

//1マスの大きさ
#define CAR_TROUT_LNEGTH (80.0f)

int overroad;

void CarStart(const InGame* ingame);
void CarDetectPosition(const CreateStage* stage);
void GetNextDestination(const Tool* tool,int x,int y);
void OverRoad(void);
void CarGoalCheck(const CreateStage* stage);
void Play_Sound_Car(int sound, int volume);
void Play_Sound_Car_Loop(int sound, int volume);
void CarMovePosition(const CreateStage*stage);
void GetCarStageNum(const InGame*ingame);
void CarWarnUpdate(const Goal* goal, const GameOver* gameover,const InGame* ingame);
void CarWarnDraw(void);
void CarIvyAnimation(void);
void CarIvyDraw(int carx, int cary);
void CarLakeAnimation(void);
void CarLakeDraw(int carx, int cary,const InGame*ingame);
void CarBoomAnimation(void);
void CarBoomDraw(int carx, int cary);

Car car;
GameOver gameover;
void CarInit(void)
{

	overroad = 0;

	car.position.x = car.current_x * CAR_TROUT_LNEGTH + 200.0f;//初期位置
	car.position.y = car.current_y * CAR_TROUT_LNEGTH + 120.0f;
	car.velocity.x = 0.2f;//速度
	car.velocity.y = 0.1f;
	car.velocity.y = 0.1f;
	car.direction = eRight;//進行方向
	car.road_count = 0;//取得する道のカウント
	car.next_count = 0;//取得した道の配列番号

	car.animation_count = 0;
	car.goal_flag = false;//ゴールまで道がつながっているかどうか

	car.ivy_flag = false;//ツタのアニメーションフラグ
	car.ivy_count = 0;//ツタのアニメーションカウント
	car.ivy_num = 0;//ツタのアニメーションナンバー

	car.lake_flag = false;//湖の中に落ちるアニメーションフラグ
	car.lake_count = 0;//湖の中に落ちるアニメーションカウント
	car.lake_num = 0;//湖の中に落ちるアニメーションナンバー
	car.lake_mul = 0;//湖の中に落ちるアニメーション**

	car.boom_flag = false;//爆発のアニメーションフラグ
	car.boom_count = 0;//爆発のアニメーションカウント
	car.boom_num = 0;//爆発のアニメーションナンバー

	car.overcount.x = 0.0f;
	car.overcount.y = 0.0f;


	gameover.image_flag = false;//GameOverをだすか
	gameover.image_count = 0;//GameOverの画像を出す時間のカウント
	gameover.flag = false;//GameOver後にリセットさせるフラグ


	//画像の読み込み
	
	car.warn_image_flag = false;
	car.warn_count = 0;
	car.warn_count_max = 40;//警告マークを表示する時間
	car.warn_num = 0;


	car.start = false;//車の処理フラグ
	car.menu_flag = false;
	car.mitibiki_flag = false;
	car.warntutorial_car_flag = false;
	
	//ステージ番号と車の初期位置を取得
	GetCarStageNum(GetInGame());
	car.animation = car.image[0];

	//次の目的地の初期化
	for (int i = 0; i < 84; i++)
	{
		car.next_x[i] = -1;
		car.next_y[i] = -1;
	}
}

void CarResourceInit(void)
{
	car.image[0] = LoadGraph("Resource/images/car2_right.png");
	car.image[1] = LoadGraph("Resource/images/car2_left.png");
	car.image[2] = LoadGraph("Resource/images/car2_up.png");
	car.image[3] = LoadGraph("Resource/images/car2_down.png");
	car.move_image[0]= LoadGraph("Resource/images/car2_right2.png");
	car.move_image[1]= LoadGraph("Resource/images/car2_left2.png");
	car.move_image[2]= LoadGraph("Resource/images/car2_up2.png");
	car.move_image[3]= LoadGraph("Resource/images/car2_down2.png");

	car.cutin_image[0] = LoadGraph("Resource/images/cutin.png");
	car.cutin_image[1] = LoadGraph("Resource/images/cutin2.png");
	car.cutin_image[2] = LoadGraph("Resource/images/cutin3.png");

	car.ivy_image[0] = LoadGraph("Resource/images/ivy_car_right.png");
	car.ivy_image[1] = LoadGraph("Resource/images/ivy_car_left.png");
	car.ivy_image[2] = LoadGraph("Resource/images/ivy_car_up.png");
	car.ivy_image[3] = LoadGraph("Resource/images/ivy_car_down.png");

	// GameOverの食虫植物の画像
	LoadDivGraph("Resource/images/PlantAnim_L.png", 19, 4, 5, 400, 400, car.ivy_anim_left);    // 左
	LoadDivGraph("Resource/images/PlantAnim_R.png", 19, 4, 5, 400, 400, car.ivy_anim_right);   // 右
	LoadDivGraph("Resource/images/PlantAnim_U.png", 19, 4, 5, 400, 400, car.ivy_anim_up);      // 上
	
	car.ivy_anim_down[0] = LoadGraph("Resource/images/PlantAnim0_D.png");
	car.ivy_anim_down[1] = LoadGraph("Resource/images/PlantAnim1_D.png");
	car.ivy_anim_down[2] = LoadGraph("Resource/images/PlantAnim2_D.png");
	car.ivy_anim_down[3] = LoadGraph("Resource/images/PlantAnim3_D.png");
	car.ivy_anim_down[4] = LoadGraph("Resource/images/PlantAnim4_D.png");
	car.ivy_anim_down[5] = LoadGraph("Resource/images/PlantAnim5_D.png");
	car.ivy_anim_down[6] = LoadGraph("Resource/images/PlantAnim6_D.png");
	car.ivy_anim_down[7] = LoadGraph("Resource/images/PlantAnim7_D.png");
	car.ivy_anim_down[8] = LoadGraph("Resource/images/PlantAnim8_D.png");
	car.ivy_anim_down[9] = LoadGraph("Resource/images/PlantAnim9_D.png");
	car.ivy_anim_down[10] = LoadGraph("Resource/images/PlantAnim10_D.png");
	car.ivy_anim_down[11] = LoadGraph("Resource/images/PlantAnim11_D.png");
	car.ivy_se= LoadSoundMem("Resource/Sounds/ivy_se.mp3");                                    // 音

	car.lake_right_anim[0] = LoadGraph("Resource/images/car_inR_lake0.png");
	car.lake_right_anim[1] = LoadGraph("Resource/images/car_inR_lake1.png");
	car.lake_right_anim[2] = LoadGraph("Resource/images/car_inR_lake2.png");
	car.lake_right_anim[3] = LoadGraph("Resource/images/car_inR_lake3.png");
	car.lake_right_anim[4] = LoadGraph("Resource/images/car_inR_lake4.png");
	car.lake_right_anim[5] = LoadGraph("Resource/images/car_inR_lake5.png");
	car.lake_right_anim[6] = LoadGraph("Resource/images/car_inR_lake6.png");

	car.lake_left_anim[0] = LoadGraph("Resource/images/car_inL_lake0.png");
	car.lake_left_anim[1] = LoadGraph("Resource/images/car_inL_lake1.png");
	car.lake_left_anim[2] = LoadGraph("Resource/images/car_inL_lake2.png");
	car.lake_left_anim[3] = LoadGraph("Resource/images/car_inL_lake3.png");
	car.lake_left_anim[4] = LoadGraph("Resource/images/car_inL_lake4.png");
	car.lake_left_anim[5] = LoadGraph("Resource/images/car_inL_lake5.png");
	car.lake_left_anim[6] = LoadGraph("Resource/images/car_inL_lake6.png");

	car.lake_up_anim[0] = LoadGraph("Resource/images/car_inU_lake0.png");
	car.lake_up_anim[1] = LoadGraph("Resource/images/car_inU_lake1.png");
	car.lake_up_anim[2] = LoadGraph("Resource/images/car_inU_lake2.png");
	car.lake_up_anim[3] = LoadGraph("Resource/images/car_inU_lake3.png");
	car.lake_up_anim[4] = LoadGraph("Resource/images/car_inU_lake4.png");
	car.lake_up_anim[5] = LoadGraph("Resource/images/car_inU_lake5.png");
	car.lake_up_anim[6] = LoadGraph("Resource/images/car_inU_lake6.png");

	car.lake_down_anim[0] = LoadGraph("Resource/images/car_inD_lake0.png");
	car.lake_down_anim[1] = LoadGraph("Resource/images/car_inD_lake1.png");
	car.lake_down_anim[2] = LoadGraph("Resource/images/car_inD_lake2.png");
	car.lake_down_anim[3] = LoadGraph("Resource/images/car_inD_lake3.png");
	car.lake_down_anim[4] = LoadGraph("Resource/images/car_inD_lake4.png");
	car.lake_down_anim[5] = LoadGraph("Resource/images/car_inD_lake5.png");
	car.lake_down_anim[6] = LoadGraph("Resource/images/car_inD_lake6.png");

	car.boom_right_animtion[0] = LoadGraph("Resource/images/car2_right_boom0.png");
	car.boom_right_animtion[1] = LoadGraph("Resource/images/car2_right_boom1.png");
	car.boom_right_animtion[2] = LoadGraph("Resource/images/car2_right_boom2.png");
	car.boom_right_animtion[3] = LoadGraph("Resource/images/fire_car_right_0.png");
	car.boom_right_animtion[4] = LoadGraph("Resource/images/fire_car_right_1.png");
	car.boom_right_animtion[5] = LoadGraph("Resource/images/fire_car_right_2.png");

	car.boom_left_animtion[0] = LoadGraph("Resource/images/car2_left_boom0.png");
	car.boom_left_animtion[1] = LoadGraph("Resource/images/car2_left_boom1.png");
	car.boom_left_animtion[2] = LoadGraph("Resource/images/car2_left_boom2.png");
	car.boom_left_animtion[3] = LoadGraph("Resource/images/fire_car2_left0.png");
	car.boom_left_animtion[4] = LoadGraph("Resource/images/fire_car2_left1.png");
	car.boom_left_animtion[5] = LoadGraph("Resource/images/fire_car2_left2.png");

	car.warn_image[0] = LoadGraph("Resource/images/Warn_image2.png");
	car.warn_image[1] = LoadGraph("Resource/images/Warn_image.png");
	car.warn_se[0] = LoadSoundMem("Resource/Sounds/Warn3_se.mp3");
	car.warn_se[1] = LoadSoundMem("Resource/Sounds/Warn3_se4.mp3");
	car.lake_se= LoadSoundMem("Resource/Sounds/water1.mp3");

	gameover.circle= LoadGraph("Resource/images/car_circle_black.png");
}

void CarManagerUpdate(void)
{
	//車の処理をスタートするフラグ
	CarStart(GetInGame());

	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			//次の進行場所を取得する
			GetNextDestination(Get_Tool(),i,j);

		}
	}
	
	//警告更新
	CarWarnUpdate(GetGoal(), GetGameOver(), GetInGame());
	//処理開始がtrueなら
	if (car.start == true && car.menu_flag == false&&car.mitibiki_flag == false)
	{
		//車の移動処理
		CarGoalCheck(GetStage());
		CarMovePosition(GetStage());
		CarIvyAnimation();
		CarLakeAnimation();
		CarBoomAnimation();
	}
	else if (car.start == false && car.menu_flag == false && car.mitibiki_flag == false)
	{
		//ステージ切り替えの時リセットする
		CarReset();
	}
}

void CarDraw(void)
{
	//車の描画
	if (car.lake_flag == false && car.ivy_flag == false)
	{
		DrawRotaGraph(car.position.x, car.position.y, 0.1, 0.0, car.animation, TRUE);
	}
	//警告マークの描画
	CarWarnDraw();
	CarWarnSE();

	//ツタの描画
	CarIvyDraw(car.position.x, car.position.y);
	CarLakeDraw(car.position.x, car.position.y, GetInGame());
	CarBoomDraw(car.position.x, car.position.y);

	/*DrawFormatString(930, 300, GetColor(255, 255, 255), "%f", car.position.x);*/
	//DrawFormatString(930, 100, GetColor(255, 255, 255), "%d", car.ivy_num);
	//DrawFormatString(300, 350, GetColor(255, 255, 255), "%d\n%d\n%d", car.next_x[car.road_count], car.next_y[car.road_count], car.road_count);
	//DrawFormatString(350, 350, GetColor(255, 255, 255), "%d\n%d\n%d", car.next_x[car.next_count], car.next_y[car.next_count], car.next_count);
	/*DrawFormatString(400, 350, GetColor(255, 255, 255), "%d\n%d\n%d", car.lake_flag, car.lake_num,car.lake_count);*/
	//DrawFormatString(450, 350, GetColor(255, 255, 255), "%f\n%f\n%f\n%f\n", car.position.x, car.position.y,car.overcount.x,car.overcount.y);
	/*DrawFormatString(200, 350, GetColor(255, 255, 255), "%d %d",car.boom_count,car.boom_flag);*/
}


//車の処理をスタートするフラグ
void CarStart(const InGame* ingame)
{
	if (ingame->start == true && ingame->menu_flag == false && ingame->mitibiki_flag == false)
	{
		car.start = true;
	}
	else if (ingame->start == false && ingame->menu_flag == false && ingame->mitibiki_flag == false)
	{
		car.start = false;
	}
	car.menu_flag = ingame->menu_flag;
	car.mitibiki_flag= ingame->mitibiki_flag;
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
	for (int i = 0; i < 84; i++)
	{
		car.next_x[i] = -1;
		car.next_y[i] = -1;
	}
	GetCarStageNum(GetInGame());
	//car.current_x = 2;//ステージ①の初期位置
	//car.current_y = 3;
	car.position.x = car.current_x * CAR_TROUT_LNEGTH + 200.0f;
	car.position.y = car.current_y * CAR_TROUT_LNEGTH + 120.0f;
	car.direction = eRight;
	car.velocity.x = 0.2f;//速度
	car.velocity.y = 0.2f;
	car.road_count = 0;
	car.next_count = 0;
	car.animation_count = 0;
	car.goal_flag = false;//ゴールまで道がつながっているかどうか
	overroad = 0;
	car.start = false;//車の処理フラグ
	car.warntutorial_car_flag = false;
	car.warn_image_flag = false;//警告マークのフラグ
	car.warn_count = 0;//警告マークを表示する時間
	car.warn_count_max = 40;//警告マークを表示する時間
	car.warn_num = 0;
	car.menu_flag == false;//車のメニュー処理フラグ
	car.animation = car.image[0];
	car.mitibiki_flag = false;
	car.overcount.x = 0.0f;
	car.overcount.y = 0.0f;

	car.ivy_flag = false;
	car.ivy_count = 0;
	car.ivy_num = 0;

	car.lake_flag = false;//湖の中に落ちるアニメーションフラグ
	car.lake_count = 0;//湖の中に落ちるアニメーションカウント
	car.lake_num = 0;//湖の中に落ちるアニメーションナンバー

	car.boom_flag = false;//爆発するアニメーションフラグ
	car.boom_count = 0;//爆発するアニメーションカウント
	car.boom_num = 0;//爆発するアニメーションナンバー

	gameover.image_flag = false;//GameOverをだすか
	gameover.image_count = 0;//GameOverの画像を出す時間のカウント
	gameover.flag = false;//GameOver後にリセットさせるフラグ

	//仮
	/*DeleteSoundMem(car.lake_se);
	car.lake_se = LoadSoundMem("Resource/Sounds/water1.mp3");*/
}

//次の進行場所を取得する
void GetNextDestination(const Tool* tool, int x, int y)
{
	//道が置かれたときの座標を取得して番号をつける
	//次の移動位置が同じでないなら
	if (tool->road_flag[x][y] == true || tool->wood_road_flag[x][y] == true)
	{
		car.road_count++;
		car.next_x[car.road_count] = x;
		car.next_y[car.road_count] = y;


	}
}


//車の移動処理
void CarMovePosition(const CreateStage* stage)
{
	car.animation_count++;
	if (car.animation_count > 60)
	{
		car.animation_count = 0;
	}
	switch (car.direction)
	{

	case eStop://止まる
		if (car.goal_flag == false)
		{
			if (overroad < 300)
			{
				OverRoad();
				/*gameover.image_flag = true;*/
			}
			if (overroad > 299)
			{
				gameover.image_count++;
				car.position.x += 0.0f;
				car.position.y += 0.0f;
				gameover.image_flag = true;
				Stop_InGameBgm();
				if (gameover.image_count > 240)
				{
					gameover.flag = true;
					gameover.image_count = 0;
				}
			}
		}
		break;
	case eUp://上に
		if (car.animation_count < 30)
		{
			car.animation = car.image[2];
		}
		else
		{
			car.animation = car.move_image[2];
		}
		car.position.y -= car.velocity.y;
		if (car.position.y < (car.current_y * CAR_TROUT_LNEGTH) + 120.2f)//微調整で120に0.2足している
		{
			//車の現在位置を検知して次の進行方向を決める
			CarDetectPosition(GetStage());

		}
		else if (car.position.y < (car.current_y * CAR_TROUT_LNEGTH) + 120.0f + car.warn_range*0.3&&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 1;
		}
		else if (car.position.y < (car.current_y * CAR_TROUT_LNEGTH) + 120.0f+  car.warn_range &&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 0;
		}
		break;
	case eDown://下に
		if (car.animation_count < 30)
		{
			car.animation = car.image[3];
		}
		else
		{
			car.animation = car.move_image[3];
		}
		car.position.y += car.velocity.y;
		if (car.position.y > (car.current_y * CAR_TROUT_LNEGTH) + 119.8f)//微調整で120から0.2引いている
		{
			//車の現在位置を検知して次の進行方向を決める
			CarDetectPosition(GetStage());

		}
		else if (car.position.y > (car.current_y * CAR_TROUT_LNEGTH) + 120.0f - car.warn_range*0.3 &&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 1;
		}
		else if (car.position.y > (car.current_y * CAR_TROUT_LNEGTH) + 120.0f- car.warn_range &&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 0;
		}
		break;
	case eRight://右に
		if (car.animation_count < 30)
		{
			car.animation = car.image[0];
		}
		else
		{
			car.animation = car.move_image[0];
		}
		
		car.position.x += car.velocity.x;
		if (car.position.x > (car.current_x * CAR_TROUT_LNEGTH) + 199.8f)//微調整で200から0.2引いている
		{
			//車の現在位置を検知して次の進行方向を決める
			CarDetectPosition(GetStage());

		}
		else if (car.position.x > (car.current_x * CAR_TROUT_LNEGTH) + 200.0f - car.warn_range*0.3&&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 1;
		}
		else if (car.position.x > (car.current_x * CAR_TROUT_LNEGTH) + 200.0f- car.warn_range &&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 0;
		}
		break;

	case eLeft:
		if (car.animation_count < 30)
		{
			car.animation = car.image[1];
		}
		else
		{
			car.animation = car.move_image[1];
		}
		car.position.x -= car.velocity.x;
		if (car.position.x < (car.current_x * CAR_TROUT_LNEGTH) + 200.2f)//微調整で200から0.2足している
		{
			//車の現在位置を検知して次の進行方向を決める
			CarDetectPosition(GetStage());

		}
		else if (car.position.x < (car.current_x * CAR_TROUT_LNEGTH) + 200.0f+ car.warn_range*0.3 &&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 1;
		}
		else if (car.position.x < (car.current_x * CAR_TROUT_LNEGTH) + 200.0f+ car.warn_range &&
			car.goal_flag == false)
		{
			car.warn_image_flag = true;
			car.warn_num = 0;
		}
		break;

	default:
		break;
	}
}

//車の現在位置を検知して次の進行方向を決める
void CarDetectPosition(const CreateStage* stage)
{
	//現在のX位置よりも次のX位置が大きかったら
	if (car.current_x < car.next_x[car.next_count] &&
		car.current_y == car.next_y[car.next_count])
	{
		if (car.direction != eRight)
		{
			car.position.x += car.overcount.x;
			car.position.y += car.overcount.y;
		}
		car.overcount.x = 0.0f;
		car.overcount.y = 0.0f;
		car.direction = eRight;//右に
		car.old_direction = eRight;
		car.current_x = car.next_x[car.next_count];//現在の位置につぎの位置を格納
		car.current_y = car.next_y[car.next_count];
		car.next_count++;                          //次の位置の配列番号にする
	}
	else if (car.current_x > car.next_x[car.next_count] &&
		car.current_y == car.next_y[car.next_count])
	{
		if (car.direction != eLeft)
		{
			car.position.x += car.overcount.x;
			car.position.y += car.overcount.y;
		}
		car.overcount.x = 0.0f;
		car.overcount.y = 0.0f;
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
		if (car.direction != eUp)
		{
			car.position.x += car.overcount.x;
			car.position.y += car.overcount.y;
		}
		car.overcount.x = 0.0f;
		car.overcount.y = 0.0f;
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
		if (car.direction != eDown)
		{
			car.position.x += car.overcount.x;
			car.position.y += car.overcount.y;
		}
		car.overcount.x = 0.0f;
		car.overcount.y = 0.0f;
		car.direction = eDown;//下に
		car.old_direction = eDown;
		car.current_x = car.next_x[car.next_count];//現在の位置につぎの位置を格納
		car.current_y = car.next_y[car.next_count];
		car.next_count++;                          //次の位置の配列番号にする
	}
	//次の進行位置がなければストップ
	else
	{
		if (car.goal_flag == false)
		{
			//car.direction = eStop;//ストップ
			switch (car.direction)
			{
			case eUp://上に
				car.overcount.y += car.speed.y;
				if (car.position.y < (car.current_y * CAR_TROUT_LNEGTH) + 90.0f)
				{
					if (stage->array[car.current_x][car.current_y - 1] == 6 && car.next_y[car.road_count] != 0)
					{
						car.lake_flag = true;
					}
					else if (stage->array[car.current_x][car.current_y - 1] == 2 && car.next_y[car.road_count] != 0)
					{
						car.boom_flag = true;
					}
					else
					{
						car.ivy_flag = true;
					}

					car.direction = eStop;//ストップ
					car.overcount.y = 0.0f;
				}
				break;
			case eDown://下に
				car.overcount.y -= car.speed.y;
				if (car.position.y > (car.current_y * CAR_TROUT_LNEGTH) + 150.0f)
				{
					if (stage->array[car.current_x][car.current_y + 1] == 6 && car.next_y[car.road_count] != 6)
					{
						car.lake_flag = true;
					}
					else if (stage->array[car.current_x][car.current_y + 1] == 2 && car.next_y[car.road_count] != 6)
					{
						car.boom_flag = true;
					}
					else
					{
						car.ivy_flag = true;
					}
					car.direction = eStop;//ストップ
					car.overcount.y = 0.0f;
				}
				break;
			case eRight://右に
				car.overcount.x -= car.speed.x;
				if (car.position.x > (car.current_x * CAR_TROUT_LNEGTH) + 230.0f)
				{
					if (stage->array[car.current_x + 1][car.current_y] == 6 && car.next_x[car.road_count] != 11)
					{
						car.lake_flag = true;
					}
					else if (stage->array[car.current_x + 1][car.current_y] == 2 && car.next_x[car.road_count] != 11)
					{
						car.boom_flag = true;
					}
					else
					{
						car.ivy_flag = true;
					}
					car.direction = eStop;//ストップ
					car.overcount.x = 0.0f;
				}
				break;
			case eLeft://左に
				car.overcount.x += car.speed.x;
				if (car.position.x < (car.current_x * CAR_TROUT_LNEGTH) + 170.0f)
				{
					if (stage->array[car.current_x - 1][car.current_y] == 6 && car.next_x[car.road_count] != 0)
					{
						car.lake_flag = true;
					}
					else if (stage->array[car.current_x - 1][car.current_y] == 2 && car.next_x[car.road_count] != 0)
					{
						car.boom_flag = true;
					}
					else
					{
						car.ivy_flag = true;
					}
					car.direction = eStop;//ストップ
					car.overcount.x = 0.0f;
				}
				break;
			default:
				break;
			}
		}
		else
		{
			car.direction = eStop;//ストップ
			car.overcount.y = 0.0f;
		}
	}
}
//GameOver時のアニメーション
void OverRoad(void)
{
	switch (car.old_direction)
	{
	case eUp://上に
		/*car.position.y -= 0.1f;*/
		overroad += 2;
		break;
	case eDown://下に
		/*car.position.y += 0.1f;*/
		overroad += 2;
		break;
	case eRight://右に
		/*car.position.x += 0.1f;*/
		overroad += 2;
		break;
	case eLeft:
		/*car.position.x -= 0.1f;*/
		overroad += 2;
		break;

	default:
		break;
	}
}

void CarGoalCheck(const CreateStage* stage)
{
	//右または上または下にゴールがあるなら
	if (stage->array[car.next_x[car.road_count] + 1][car.next_y[car.road_count]] == 7 && car.next_x[car.road_count] != 11 ||
		stage->array[car.next_x[car.road_count] - 1][car.next_y[car.road_count]] == 7 && car.next_x[car.road_count] != 0 ||
		stage->array[car.next_x[car.road_count]][car.next_y[car.road_count] - 1] == 7 && car.next_y[car.road_count] != 0 ||
		stage->array[car.next_x[car.road_count]][car.next_y[car.road_count] + 1] == 7 && car.next_y[car.road_count] != 6)
	{
		//車の速度を上げる
		car.velocity.x = 5.0f;
		car.velocity.y = 5.0f;

		//ゴールの配列番号を一番先端に入れる
		car.next_x[car.road_count + 1] = stage->goal_x[0];
		car.next_y[car.road_count + 1] = stage->goal_y[0];
		//ゴールまで道がつながったかどうか
		car.goal_flag = true;
	}
	else
	{
		//ゴール以外の時の速度
		car.velocity.x = car.speed.x;
		car.velocity.y = car.speed.y;
	}

}
void CarWarnSE(void) 
{
	if (car.warn_image_flag == true && car.next_x[car.next_count] == -1 && car.next_y[car.next_count] == -1)
	{
		switch (car.warn_num)
		{
		case 0:
			if (CheckSoundMem(car.warn_se[0]) == 0 && CheckSoundMem(car.warn_se[1]) == 0)
			{
				Play_Sound_Car(car.warn_se[0], 100);
			}
			break;
		case 1:
			if (CheckSoundMem(car.warn_se[0]) == 0 && CheckSoundMem(car.warn_se[1]) == 0)
			{
				Play_Sound_Car(car.warn_se[1], 100);
			}
			break;
		}
		
	}
	else if(car.warn_image_flag == false)
	{
		StopSoundMem(car.warn_se[0]);
		StopSoundMem(car.warn_se[1]);
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

void Play_Sound_Car_Loop(int sound, int volume)
{
	//TRUEだとバック再生
	PlaySoundMem(sound, DX_PLAYTYPE_LOOP, TRUE);
	ChangeVolumeSoundMem(volume, sound);
}


void CarWarnUpdate(const Goal*goal,const GameOver*gameover,const InGame*ingame)
{
	//警告マークの点滅速度を変える
	switch (car.warn_num)
	{
	case 0:
		car.warn_count_max = 40;
		break;
	case 1:
		car.warn_count_max = 20;
		break;
	}

	if (car.next_x[car.next_count] != -1 && car.next_y[car.next_count] != -1||
		goal->print_flag == true || gameover->image_flag == true ||ingame->menu_flag==true||car.direction==eStop)
	{
		car.warn_image_flag = false;
		car.warn_count = 0;
	}
}

 void CarWarnDraw(void)
{
	 if (car.warn_image_flag == true && car.next_x[car.next_count] == -1 && car.next_y[car.next_count] == -1)
	 {
		 car.warn_count++;
		 if (car.warn_count % car.warn_count_max< car.warn_count_max / 2)
		 {
			 switch (car.direction)
			 {
			 case eUp: case eDown:
				 DrawRotaGraphF(car.position.x - 80.0f, car.position.y, 1.0, 0.0, car.warn_image[car.warn_num], TRUE);
				 car.warntutorial_car_flag = true;
				 break;
			 case eRight: case eLeft:
				 DrawRotaGraphF(car.position.x, car.position.y - 80.0f, 1.0, 0.0, car.warn_image[car.warn_num], TRUE);
				 car.warntutorial_car_flag = true;
				 break;
			 }
		 }
	 }
	
}

 void CarIvyAnimation(void)
 {
	 if (car.ivy_flag == true)
	 {
		 car.ivy_count++;
		 if (car.ivy_count > 20&&car.ivy_count % 4 == 0 && car.ivy_num < 11)
		 {
			 car.ivy_num++;
		 }

		 if (car.start == false)
		 {
			 car.ivy_flag = false;
			 car.ivy_count = 0;
			 car.ivy_num = 0;
		 }
	 }
 }

 void CarIvyDraw(int carx, int cary)
 {
	 if (car.ivy_flag == true)
	 {
		 switch (car.old_direction)
		 {
		 case eUp:
			 DrawRotaGraphF(carx + 18, cary - 50, 1.7, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx + 18, cary - 55, 0.4, 0.0, car.ivy_anim_up[car.ivy_num], TRUE);
			 if (car.ivy_num < 18)
			 {
				 DrawRotaGraphF(carx + 18, cary - 55, 0.4, 0.0, car.ivy_anim_up[0], TRUE);
			 }
			 break;
		 case eDown:
			 if (car.ivy_num < 18)
			 {
				 DrawRotaGraphF(carx - 18, cary + 50, 0.4, 0.0, car.ivy_anim_down[0], TRUE);
			 }
			 DrawRotaGraphF(carx - 18, cary + 50, 1.7, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx - 18, cary + 50, 0.4, 0.0, car.ivy_anim_down[car.ivy_num], TRUE);
			 
			 break;
		 case eRight:
			 DrawRotaGraphF(carx + 22, cary - 25, 1.7, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx + 14, cary - 44, 0.4, 0.0, car.ivy_anim_right[car.ivy_num], TRUE);
			 if (car.ivy_num < 18)
			 {
				 DrawRotaGraphF(carx + 14, cary - 44, 0.4, 0.0, car.ivy_anim_right[0], TRUE);
			 }
			 break;
		 case eLeft:
			 DrawRotaGraphF(carx - 22, cary - 25, 1.7, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx - 14, cary - 44, 0.4, 0.0, car.ivy_anim_left[car.ivy_num], TRUE);
			 if (car.ivy_num < 18)
			 {
				 DrawRotaGraphF(carx - 14, cary - 44, 0.4, 0.0, car.ivy_anim_left[0], TRUE);
			 }
			 break;
		 }
		 /* DrawRotaGraphF(carx, cary, 1.0, 0.0, gameover.circle, TRUE);
		  DrawRotaGraphF(carx - 14, cary - 44, 0.4, 0.0, car.ivy_animation[car.ivy_num], TRUE);*/
		 if (car.ivy_count < 60)
		 {
			 Play_Sound_Car(car.ivy_se, 150);
		 }
	 }
	 else if (car.ivy_flag == false)
	 {
		 StopSoundMem(car.ivy_se);
	 }
 }

 void CarLakeAnimation(void)
 {
	 if (car.lake_flag == true)
	 {
		 car.lake_count++;
		 if (car.lake_count > 30 && car.lake_count % 8 == 0 && car.lake_num < 6)
		 {
			 car.lake_num++;
			 
		 }

		 if (car.start == false)
		 {
			 car.lake_flag = false;
			 car.lake_count = 0;
			 car.lake_num = 0;
		 }
	 }
 }
 void CarLakeDraw(int carx, int cary,const InGame*ingame)
 {
	 if (car.lake_flag == true)
	 {
		 switch (car.old_direction)
		 {
		 case eUp:
			 DrawRotaGraphF(carx, cary - car.lake_num * 8 - 5, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx, cary - car.lake_num * 8 - 5, 0.1, 0.0, car.lake_up_anim[car.lake_num], TRUE);
			 break;
		 case eDown:
			 DrawRotaGraphF(carx, cary + car.lake_num * 2 + 10, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx, cary + car.lake_num * 2 + 5, 0.1, 0.0, car.lake_down_anim[car.lake_num], TRUE);
			 break;
		 case eRight:
			 DrawRotaGraphF(carx + car.lake_num * 8, cary, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx + car.lake_num * 8, cary, 0.1, 0.0, car.lake_right_anim[car.lake_num], TRUE);
			 break;
		 case eLeft:
			 DrawRotaGraphF(carx - car.lake_num * 8, cary, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx - car.lake_num * 8, cary, 0.1, 0.0, car.lake_left_anim[car.lake_num], TRUE);
			 break;
		 }
		 /*if (car.lake_count > 40 && car.lake_count < 170 && ingame->menu_flag == false)
		 {
			 PlaySoundMem(car.lake_se, DX_PLAYTYPE_BACK, FALSE);
		 }
		 else if (car.lake_count >= 170)
		 {
			 StopSoundMem(car.lake_se);
		 }
		 
		 if (CheckSoundMem(car.lake_se)==1&&car.menu_flag == true)
			 {
				 StopSoundMem(car.lake_se);
			 }*/

		 if (car.lake_count > 40 && car.lake_count < 50)
		 {
			 Play_Sound_Car(car.lake_se, 200);
		 }
	 }

	 else if (car.lake_flag == false)
	 {
		 StopSoundMem(car.lake_se);
	 }
 }

 void CarBoomAnimation(void)
 {
	 if (car.boom_flag == true)
	 {
		 car.boom_count++;
		 if (car.boom_count > 30 && car.boom_count % 10 == 0 && car.boom_num < 5)
		 {
			 car.boom_num++;
		 }
		 if (car.start == false)
		 {
			 car.boom_flag = false;
			 car.boom_count = 0;
			 car.boom_num = 0;
		 }
	 }
 }

 void CarBoomDraw(int carx,int cary)
 {
	 if (car.boom_flag == true)
	 {
		 switch (car.old_direction)
		 {
		 case eRight:
			 DrawRotaGraphF(carx, cary, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx, cary, 0.12, 0.0, car.boom_right_animtion[car.boom_num], TRUE);
			 break;
		 case eLeft:
			 DrawRotaGraphF(carx, cary, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx, cary, 0.1, 0.0, car.boom_left_animtion[car.boom_num], TRUE);
			 break;
		 case eUp:
			 DrawRotaGraphF(carx, cary, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx, cary, 0.1, 0.0, car.boom_up_animtion[car.boom_num], TRUE);
			 break;
		 case eDown:
			 DrawRotaGraphF(carx, cary, 1.0, 0.0, gameover.circle, TRUE);
			 DrawRotaGraphF(carx, cary, 0.1, 0.0, car.boom_down_animtion[car.boom_num], TRUE);
			 break;
		 }
		 //if (car.boom_count > 30)
		 //{
			 //if (car.boom_count < 60)
			 //{
				// Play_Sound_Car(car.boom_se, 150);
			 //}
		 //}
	 }
 }


//ステージ番号と車の初期位置を取得
void GetCarStageNum(const InGame* ingame)
{
	//ステージごとの初期位置
	switch (ingame->stage_num)
	{
	case eOne:
		car.current_x = 1;//ステージ①の初期位置
		car.current_y = 4;
		car.speed.x = 0.05f;
		car.speed.y = 0.05f;
		car.next_x[0] = 3;
		car.next_y[0] = 4;
		car.warn_range = 20.0f;
		break;
	case eTwo:
		car.current_x = 1;//ステージ②の初期位置
		car.current_y = 3;
		car.speed.x = 0.1f;
		car.speed.y = 0.1f;
		car.next_x[0] = 3;
		car.next_y[0] = 3;
		car.warn_range = 20.0f;
		break;
	case eThree:
		car.current_x = 1;//ステージ③の初期位置
		car.current_y = 3;
		car.speed.x = 0.1f;
		car.speed.y = 0.1f;
		car.next_x[0] = 3;
		car.next_y[0] = 3;
		car.warn_range = 20.0f;
		break;
	case eFour:
		car.current_x = 0;//ステージ④の初期位置
		car.current_y = 0;
		car.speed.x = 0.4f;
		car.speed.y = 0.4f;
		car.next_x[0] = 2;
		car.next_y[0] = 0;
		car.warn_range = 40.0f;
		break;
	case eFive:
		car.current_x = 1;//ステージ⑤の初期位置
		car.current_y = 3;
		car.speed.x = 0.2f;
		car.speed.y = 0.2f;
		car.next_x[0] = 3;
		car.next_y[0] = 3;
		car.warn_range = 40.0f;
		break;
	case eSix:
		car.current_x = 0;//ステージ⑥の初期位置
		car.current_y = 6;
		car.speed.x = 0.3f;
		car.speed.y = 0.3f;
		car.next_x[0] = 2;
		car.next_y[0] = 6;
		car.warn_range = 60.0f;
		break;
	}
}