#include"DxLib.h"
#include"Goal.h"
#include"../Scene/InGame/InGameScene.h"
#include"../Utility/PadInputManager.h"
#include "../Object/Car.h"
#include "../Object/Map.h"


//仮名
bool goalprint=false;
Goal goal;
int i=255;

//スタートしたか？
void GoalStart(const InGame* ingame);
void GoalFlag(const InGame* ingame, const Car* car,const CreateStage*stage);
void GameOverDraw(const GameOver* gameover);
//Goalの旗を揺らすアニメーション
void GoalFlagAnim(const Car* car);




//初期化
void GoalInit(void)
{
	//ゴールしたかの判定フラグ
	goal.flag = false;

	//ゲームがスタートしたかの判定フラグ
	goal.start = false;
	goal.menu_flag = false;
	goal.count = 0;
	goal.print_count = 0;
	goal.flag_idx = 0;
	goal.flag_cnt = 0;

	goal.print_flag = false;
	
	goal.firework_count = 0;
	goal.firework_x[0] = 150.0f;
	goal.firework_x[1] = 1100.0f;
	goal.firework_x[2] = 650.0f;
	for (int i = 0; i < 3; i++)
	{
		goal.old_num[i] = 0;
		goal.add_y[i] = 0.0f;
		goal.firework_rate[i] = 0.0f;
		goal.firework_num[i] = 0;
	}
}


void GoalResourceInit(void)
{
	//画像の読み込み
	goal.whiteback_image = LoadGraph("Resource/images/white_back.png");
	goal.blackback_image = LoadGraph("Resource/images/black_back.png");
	goal.flag_image[0] = LoadGraph("Resource/images/goal_image1.png");
	goal.flag_image[1] = LoadGraph("Resource/images/goal_image2.png");
	goal.flag_image[2] = LoadGraph("Resource/images/goal_image3.png");
	goal.flag_image[3] = LoadGraph("Resource/images/goal_image4.png");
	goal.print_image = LoadGraph("Resource/images/GOAL.png");

	goal.gameover_image = LoadGraph("Resource/images/GAMEOVER.png");
	LoadDivGraph("Resource/images/firework.png", 12, 6, 2, 300, 300, goal.firework_image);
	LoadDivGraph("Resource/images/firework2.png", 12, 6, 2, 300, 300, goal.firework_image2);
	LoadDivGraph("Resource/images/firework3.png", 12, 6, 2, 300, 300, goal.firework_image3);

	//音読み込み
	goal.firework_se = LoadSoundMem("Resource/Sounds/firework.mp3"); 
}
//更新
void GoalUpdate(void)
{
	//ゴール処理をスタート
	GoalStart(GetInGame());
	//ゴールしたかどうか
	GoalFlag(GetInGame(), GetCar(), GetStage());

	if (goal.start == false && goal.menu_flag == false)
	{
		GoalReset();
	}


	if (goal.start == true)
	{
		GoalFlagAnim(GetCar());
	}
	//花火処理
	if (goal.print_flag == true)
	{

		//１フレーム前の画像番号を格納
		for (int i = 0; i < 3; i++)
		{
			goal.old_num[i] = goal.firework_num[i];
		}

		goal.firework_count++;
		if (goal.firework_count > 150)
		{
			goal.firework_count = 0;
			goal.add_y[0] = 0.0f;
			goal.add_y[1] = 0.0f;
			goal.add_y[2] = 0.0f;
			goal.firework_x[0] = GetRand(1000) % (200 - 100 + 1) + 100;
			goal.firework_x[1] = GetRand(1000) % (1150 - 1050 + 1) + 1050;
			goal.firework_x[2] = GetRand(1000) % (700 - 600 + 1) + 600;
		}

		for (int i = 0; i < 3; i++)
		{
			if (goal.firework_count - i * 25 < 35&& goal.firework_count - i * 25 > 0)
			{
				goal.add_y[i] += 5.0f;
			}

			if (goal.firework_count - i * 25 > 35)
			{
				goal.firework_rate[i] = 2.0f;
			}
			else
			{
				goal.firework_rate[i] = 1.0f;
			}
		}
		goal.firework_num[0] = goal.firework_count / 5;
		goal.firework_num[1] = (goal.firework_count - 25) / 5;
		goal.firework_num[2] = (goal.firework_count - 50) / 5;

		for (int i = 0; i < 3; i++)
		{
			if (goal.old_num[i] == 6 && goal.firework_num[i] == 7)
			{
				PlaySoundMem(goal.firework_se, DX_PLAYTYPE_BACK);
				ChangeVolumeSoundMem(255 * 60 / 100, goal.firework_se);
			}
		}
	}
}

//描画
void GoalDraw(void)
{
	if (goal.print_flag == true)
	{
		DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, goal.whiteback_image, TRUE);
		DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, goal.whiteback_image, TRUE);
		//花火描画
		if (goal.firework_num[0] < 12&& goal.firework_num[0] > 0)
		{
			DrawRotaGraphF(goal.firework_x[0], 570.0f - goal.add_y[0], goal.firework_rate[0] - 0.2f, 0.0, goal.firework_image[goal.firework_num[0]], TRUE);
		}
		if (goal.firework_num[1] < 12 && goal.firework_num[1] > 0)
		{
			DrawRotaGraphF(goal.firework_x[1], 750.0f - goal.add_y[1], goal.firework_rate[1], 0.0, goal.firework_image2[goal.firework_num[1]], TRUE);
		}
		if (goal.firework_num[2] < 12 && goal.firework_num[2] > 0)
		{
			DrawRotaGraphF(goal.firework_x[2], 500.0f - goal.add_y[2], goal.firework_rate[2], 0.0, goal.firework_image3[goal.firework_num[2]], TRUE);
		}
		//ここまで
		DrawRotaGraphF(615.0f, 380.0f, 1.0, 0.0, goal.print_image, TRUE);
	}
	GameOverDraw(GetGameOver());

	DrawFormatString(100, 100, GetColor(255, 255, 0), "%d\n%d", goal.flag_cnt, goal.flag_idx);
}
	


//ゴール処理スタート
void GoalStart(const InGame* ingame)
{
	if(ingame->start == true && ingame->menu_flag == false)
	{
		goal.start = true;
	}
	else if (ingame->start == false&& ingame->menu_flag == false)
	{
		goal.start = false;
	}
	goal.menu_flag = ingame->menu_flag;
}

//Goalの旗を揺らすアニメーション
void GoalFlagAnim(const Car*car)
{
	if (car->direction != eStop)
	{
		goal.flag_cnt++;

		if (goal.flag_cnt > 10)
		{
			goal.flag_idx++;
			goal.flag_cnt = 0;
		}

		if (goal.flag_idx > 3)
		{
			goal.flag_idx = 0;
		}
	}
}

const Goal* GetGoal(void)
{
	return &goal;
}


void GoalFlag(const InGame* ingame, const Car* car,const CreateStage*stage)
{

	if (car->current_x == stage->goal_x[0] && car->current_y == stage->goal_y[0] && car->direction == eStop)
	{
		/*goal.print_flag = true;*/

		if (goal.print_count == 0)
		{
			goal.print_flag = true;
			goal.count++;
		}
		
		if (goal.count > 240)
		{
			goal.flag = true;
			goal.print_flag = false;
			goal.print_count = 1;
			goal.count = 0;
		}
		
	}

	if (ingame->next_stage_flag == true)
	{
		goal.flag = false;
		goal.print_count = 0;
	}

}

void GoalReset(void)
{
	//ゴールしたかの判定フラグ
	goal.flag = false;

	//ゲームがスタートしたかの判定フラグ
	goal.start = false;
	goal.menu_flag = false;
	goal.count = 0;
	goal.print_count = 0;

	goal.firework_count = 0;
	for (int i = 0; i < 3; i++)
	{
		goal.old_num[i] = 0;
		goal.add_y[i] = 0.0f;
		goal.firework_rate[i] = 0.0f;
		goal.firework_num[i] = 0;
	}
}

void GameOverDraw(const GameOver* gameover)
{
	if (gameover->image_flag == true)
	{
		DrawRotaGraphF(640.0f, 360.0f, 4.0, 0.0, goal.blackback_image, TRUE);
		DrawRotaGraphF(615.0f, 380.0f, 1.0, 0.0, goal.gameover_image, TRUE);
	}
}