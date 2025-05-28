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

	goal.print_flag = false;
	//画像の読み込み
	goal.flag_image = LoadGraph("Resource/images/GOAL_FLAG2.png");
	goal.print_image = LoadGraph("Resource/images/GOAL.png");

	goal.gameover_image= LoadGraph("Resource/images/GAMEOVER.png");
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

}

//描画
void GoalDraw(void)
{
	if (goal.print_flag == true)
	{
		DrawRotaGraphF(615, 380, 1.0, 0.0, goal.print_image, TRUE);
	}

	GameOverDraw(GetGameOver());
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
		
		if (goal.count > 120)
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
}

void GameOverDraw(const GameOver* gameover)
{
	if (gameover->image_flag == true)
	{
		DrawRotaGraphF(615, 380, 1.0, 0.0, goal.gameover_image, TRUE);
	}
}

