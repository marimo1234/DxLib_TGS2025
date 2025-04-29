#include "InGameScene.h"
#include "../../Utility/InputManager.h"
#include "../../Object/Cursor.h"
#include "../../Object/Obstacle.h"
#include "../Result/ResultScene.h"
#include "../../Utility/PadInputManager.h"
#include "../../Object/car.h"
#include "../../Object/WoodRock.h"
#include "../../Object/map.h"
#include "../../Object/Tool.h"
#include "../../Object/Goal.h"
#include "DxLib.h"

#include <math.h>
#include <stdlib.h>

#define D_SCROOL_SPEED		(200.0f)

//確認用変数　後に消します
int atr ;
int btr ;

//この辺まだ使っていない
void HitCheck(const Cursor* cursor, const Obstacle* obstacle, int index);
void PlayBgm(void);

InGame ingame;

void NextStageFlag(const Goal* goal);

//初期化
void InGameSceneInit(void)
{
	//インゲームスタートのフラグ変数
	ingame.start = false;
	//ステージを1ステージ目に設定
	ingame.stage_num = eOne;
	//ステージ次のステージに変更するフラグ
	ingame.next_stage_flag = false;


	//確認用変数　後々消します
	atr = 0;
	btr = 1;

	//BGMの初期化
		PlayBgm();
		//マップの初期化
		MapInit();
		//障害物の初期化
		ObstacleManagerInit();
		//木岩の初期化
		WoodRockInit();
		//ツールの初期化
		ToolInit();
		//車の初期化
		CarInit();
		//カーソルの初期化
		CursorInit();
		//ゴールの読み込み
		GoalInit();


	
}

eSceneType InGameSceneUpdate()
{
	//マップの更新
	MapUpdate();
	//障害物の更新
	ObstacleManagerUpdate();
	//木岩の更新
	WoodRockUpdate();
	//ツールの更新
	ToolManagerUpdate();
	//車の更新
	CarManagerUpdate();
	//カーソルの更新
	CursorUpdate();
	//ゲームスタート
	GameStart();
	//ゴールの更新
	GoalUpdate();

	//ゴールを受け取ったらステージを変えることを可能にする
	NextStageFlag(GetGoal());

	//ゴールしたなら次のステージへ
	StageChange();


	/*当たり判定の計算（プレイヤーと障害物）*/
	for (int i = 0; i < D_OBSTACLE_MAX; i++)
	{
		HitCheck(GetCursor1(), GetObstacle(i), i);
	}

	if (GetKeyInputState(KEY_INPUT_SPACE) == ePress)
	{
		return eResult;	//インゲーム画面へ
	}

	return eInGame;
}

void InGameSceneDraw(void)
{
	DrawFormatString(50, 10, GetColor(255, 255, 255), "Xボタンでゲームスタート");
	DrawFormatString(50, 60, GetColor(255, 255, 255), "Aで伐る、壊す、作った道を置く");
	DrawFormatString(50, 110, GetColor(255, 255, 255), "Bで材料があれば道、橋を作れる");
	DrawFormatString(50, 160, GetColor(255, 255, 255), "");
	//背景画像の描画
	/*DrawGraphF(scrool_x, 0, , TRUE);
	DrawGraphF(1280.0f + scrool_x, 0, , TRUE);*/
	DrawFormatString(50, 10, GetColor(255, 255, 255), "スペースでリザルト画面へ");

	//マップの描画
	MapDraw();

	//障害物の描画
	ObstacleManagerDraw();

	//木岩の描画
	WoodRockDraw();

	//ツールの描画
	ToolDraw();

	//車の描画
	CarDraw();

	//カーソルの描画
	CursorDraw();

	//ゴールの描画
	GoalDraw();

	//atrがgoal.flagを受け取っているかの確認、btrがステージ遷移できるかどうかの確認
	//後々消します
	DrawFormatString(300, 300, GetColor(255, 255, 255), "%d %d", atr,btr);
}
const InGame* GetInGame(void)
{
	return &ingame;
}

//Gameスタート
void GameStart(void)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (ingame.start == false)
	{
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_X) == ePadInputState::ePress)
		{
			ingame.start = true;
		}
	}
}

//矩形同士の当たり判定の計算部分
void HitCheck(const Cursor* player, const Obstacle* obstacle, int index)
{
	if (obstacle->is_active == TRUE)
	{
		float dx = fabsf(player->position.x - obstacle->position.x);
		float dy = fabsf(player->position.y - obstacle->position.y);

		float bx = (player->box_size.x + obstacle->box_size.x) * 0.5f;
		float by = (player->box_size.y + obstacle->box_size.y) * 0.5f;

		if ((dx < bx) && (dy < by))
		{
			
		}
		else
		{
			
		}
	}
}
           //今のところどこで使うかわかんない↑↑↑↑↑

//インゲームBGM再生
void PlayBgm(void)
{
	/*PlaySoundMem(, DX_PLAYTYPE_LOOP);*/
}


//ステージチェンジを可能にするフラグ
void NextStageFlag(const Goal* goal)
{
	ingame.next_stage_flag = false;

	if (goal->flag == true)
	{
		ingame.next_stage_flag = true;
		atr ++;
		ingame.start = false;
	}

	
}

//ステージチェンジ処理
void StageChange(void)
{
	switch (ingame.stage_num)
	{
	case eOne:
		if (ingame.next_stage_flag == true)
		{
			ingame.stage_num = eTwo;
			btr ++;
		}
		break;
	case eTwo:
		if (ingame.next_stage_flag == true)
		{
			ingame.stage_num = eThree;
			btr ++;
		}
		break;
	case eThree:
		if (ingame.next_stage_flag == true)
		{
			ingame.stage_num = eFour;
			btr ++;
		}
		break;
	case eFour:
		if (ingame.next_stage_flag == true)
		{
			ingame.stage_num = eFive;
			btr ++;
		}
		break;
	case eFive:
		if (ingame.next_stage_flag == true)
		{
			ingame.stage_num = eOne;
			btr = 1;
		}
		break;
	default:
		break;
	}
}

