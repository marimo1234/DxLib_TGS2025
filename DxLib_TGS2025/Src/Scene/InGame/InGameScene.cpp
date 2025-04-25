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

void HitCheck(const Cursor* cursor, const Obstacle* obstacle, int index);
void PlayBgm(void);

Start start;
int Before_Hit[10];		//前の当たり判定
int Now_Hit[10];		//今の当たり判定
eStage stage;
NextStage nextstage;



void InGameSceneInit(void)
{
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
	start.GameStart = FALSE;
	stage = eOne;
	
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
	//スタートボタン
	StarButton();
	//ゴールの更新
	GoalUpdate();



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
	//背景画像の描画
	/*DrawGraphF(scrool_x, 0, , TRUE);
	DrawGraphF(1280.0f + scrool_x, 0, , TRUE);*/
	DrawFormatString(50, 10, GetColor(255, 255, 255), "スペースでリザルト画面へ");

	//マップの描画
	MapDraw(stage);

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
}
const Start* GetStart(void)
{
	return &start;
}
void StarButton()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		start.GameStart = TRUE;
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

const NextStage* Stageselect(void)
{
	switch (stage)
	{
	case eOne:
		nextstage.nextstage =true;
		break;
	case eTwo:
		nextstage.nextstage = true;
		break;
	case eThree:
		nextstage.nextstage = true;
		break;
	case eFour:
		nextstage.nextstage = true;
		break;
	case eFive:
		nextstage.nextstage = true;
		break;
	default:
		break;
	}
}




//インゲームBGM再生
void PlayBgm(void)
{
	/*PlaySoundMem(, DX_PLAYTYPE_LOOP);*/
}

void StageChenge(void)
{
	switch (start.StageNumber)
	{
	case 1:
		stage = eOne;
	case 2:
		stage = eTwo;
	case 3:
		stage = eThree;
	case 4:
		stage = eFour;
	case 5:
		stage = eFive;
	default:
		break;
	}
}

