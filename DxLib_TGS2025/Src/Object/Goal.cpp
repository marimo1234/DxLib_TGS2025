#include"DxLib.h"
#include"Goal.h"

Goal goal;

void GoalInit(void)
{
	//ゴールしたかどうか
	goal.flg = false;

	//画像の読み込み
	goal.image = LoadGraph("Resource/images/GOAL_FLAG2.png");
}
void GoalUpdate(void)
{

}
void GoalDraw(void)
{
	//画像の描画
	DrawRotaGraphF(720, 340, 0.1, 0.0, goal.image, TRUE);
}