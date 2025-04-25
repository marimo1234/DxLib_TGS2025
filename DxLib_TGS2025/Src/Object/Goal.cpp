#include"DxLib.h"
#include"Goal.h"

int goalflag;
void GoalInit(void)
{
	goalflag = LoadGraph("Resource/images/GOAL_FLAG2.png");
}
void GoalUpdate(void)
{

}
void GoalDraw(void)
{
	DrawRotaGraphF(720, 340, 0.1, 0.0, goalflag, TRUE);
}