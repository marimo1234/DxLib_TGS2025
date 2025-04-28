#include"DxLib.h"
#include"Goal.h"
#include"../Scene/InGame/InGameScene.h"
#include"../Utility/PadInputManager.h"
#include "../Object/Car.h"




Goal goal;

//スタートしたか？
void GoalStart(const InGame* ingame);
void GoalFlag(const InGame* ingame, const Car* car);




//初期化
void GoalInit(void)
{
	goal.position.x = 690.0f;
	goal.position.y = 380.0f;
	//ゴールしたかの判定フラグ
	goal.flag = false;

	//ゲームがスタートしたかの判定フラグ
	goal.start = false;

	//画像の読み込み
	goal.image = LoadGraph("Resource/images/GOAL_FLAG2.png");
}

//更新
void GoalUpdate(void)
{
	//ゴール処理をスタート
	GoalStart(GetInGame());
	//ゴールしたかどうか
	GoalFlag(GetInGame(),GetCar());
}

//描画
void GoalDraw(void)
{
	//画像の描画
	DrawRotaGraphF(goal.position.x, goal.position.y, 0.1, 0.0, goal.image, TRUE);
}

//ゴール処理スタート
void GoalStart(const InGame* ingame)
{
	if(ingame->start == true)
	{
		goal.start = true;
	}
}



const Goal* GetGoal(void)
{
	return &goal;
}


void GoalFlag(const InGame* ingame, const Car* car)
{

	if (goal.position.x < car->position.x && goal.position.y == car->position.y)
	{
		goal.flag = true;
	}

	if (ingame->next_stage_flag == true)
	{
		goal.flag = false;
	}


}