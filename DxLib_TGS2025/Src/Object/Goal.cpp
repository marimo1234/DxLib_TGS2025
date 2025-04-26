#include"DxLib.h"
#include"Goal.h"
#include"../Scene/InGame/InGameScene.h"
#include"../Utility/PadInputManager.h"



Goal goal;

//スタートしたか？
void GoalStart(const InGame* ingame);
void GoalFlag(const InGame* ingame);

//初期化
void GoalInit(void)
{
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
	GoalFlag(GetInGame());
}

//描画
void GoalDraw(void)
{
	//画像の描画
	DrawRotaGraphF(720, 340, 0.1, 0.0, goal.image, TRUE);
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

//ゴールした時にフラグをtrueにする
//今だけYボタンを押したらゴール判定になるようにしている
void GoalFlag(const InGame* ingame)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetButtonInputState(XINPUT_BUTTON_Y) == ePadInputState::ePress)
	{
		goal.flag = true;
	}

	if (ingame->next_stage_flag == true)
	{
		goal.flag = false;
	}


}