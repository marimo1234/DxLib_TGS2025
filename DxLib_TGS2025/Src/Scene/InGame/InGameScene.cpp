#include "InGameScene.h"
#include "../../Utility/InputManager.h"
#include "../../Object/Player.h"
#include "../../Object/Obstacle.h"
#include "../Result/ResultScene.h"
#include "../../Utility/PadInputManager.h"
#include "../../Object/car.h"
#include "../../Object/WoodRock.h"
#include "../../Object/map.h"
#include "../../Object/Tool.h"
#include "DxLib.h"

#include <math.h>
#include <stdlib.h>

#define D_SCROOL_SPEED		(200.0f)

void HitCheck(const Player* player, const Obstacle* obstacle, int index);
void PlayBgm(void);

int Before_Hit[10];		//前の当たり判定
int Now_Hit[10];		//今の当たり判定
int stage;

void InGameSceneInit(void)
{
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
	//プレイヤーの初期化
	PlayerInit();

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
	//プレイヤーの更新
	PlayerUpdate();





	/*当たり判定の計算（プレイヤーと障害物）*/
	for (int i = 0; i < D_OBSTACLE_MAX; i++)
	{
		HitCheck(GetPlayer(), GetObstacle(i), i);
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

	//プレイヤーの描画
	PlayerDraw();
}


//矩形同士の当たり判定の計算部分
void HitCheck(const Player* player, const Obstacle* obstacle, int index)
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

//インゲームBGM再生
void PlayBgm(void)
{
	/*PlaySoundMem(, DX_PLAYTYPE_LOOP);*/
}

