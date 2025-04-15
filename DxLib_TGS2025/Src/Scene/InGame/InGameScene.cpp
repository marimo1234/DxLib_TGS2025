#include "InGameScene.h"
#include "../../Utility/InputManager.h"
#include "../../Object/Player.h"
#include "../../Object/Obstacle.h"
#include "../Result/ResultScene.h"
#include "DxLib.h"

#include <math.h>
#include <stdlib.h>

#define D_SCROOL_SPEED		(200.0f)

void HitCheck(const Player* player, const Obstacle* obstacle, int index);
void PlayBgm(void);


float scrool_x;			//横スクロール
int Before_Hit[10];		//前の当たり判定
int Now_Hit[10];		//今の当たり判定

void InGameSceneInit(void)
{
	PlayBgm();

	//プレイヤーの初期化
	PlayerInit();
	//障害物の初期化
	ObstacleManagerInit();

	scrool_x = 0.0f;
}

eSceneType InGameSceneUpdate()
{
	//プレイヤーの更新
	PlayerUpdate();
	//障害物の更新
	ObstacleManagerUpdate();

	//プレイヤーが移動した分だけ背景をずらす
	scrool_x -= GetPlayer()->velocity.x;
	if (scrool_x <= -1280.0f)
	{
		scrool_x += 1280.0f;
	}

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
	DrawFormatString(100, 100, GetColor(255, 255, 255), "スペースでリザルト画面へ");

	//障害物の描画
	ObstacleManagerDraw();

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

