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


float scrool_x;			//‰¡ƒXƒNƒ[ƒ‹
int Before_Hit[10];		//‘O‚Ì“–‚½‚è”»’è
int Now_Hit[10];		//¡‚Ì“–‚½‚è”»’è

void InGameSceneInit(void)
{
	PlayBgm();

	//ƒvƒŒƒCƒ„[‚Ì‰Šú‰»
	PlayerInit();
	//áŠQ•¨‚Ì‰Šú‰»
	ObstacleManagerInit();

	scrool_x = 0.0f;
}

eSceneType InGameSceneUpdate()
{
	//ƒvƒŒƒCƒ„[‚ÌXV
	PlayerUpdate();
	//áŠQ•¨‚ÌXV
	ObstacleManagerUpdate();

	//ƒvƒŒƒCƒ„[‚ªˆÚ“®‚µ‚½•ª‚¾‚¯”wŒi‚ð‚¸‚ç‚·
	scrool_x -= GetPlayer()->velocity.x;
	if (scrool_x <= -1280.0f)
	{
		scrool_x += 1280.0f;
	}

	/*“–‚½‚è”»’è‚ÌŒvŽZiƒvƒŒƒCƒ„[‚ÆáŠQ•¨j*/
	for (int i = 0; i < D_OBSTACLE_MAX; i++)
	{
		HitCheck(GetPlayer(), GetObstacle(i), i);
	}

	if (GetKeyInputState(KEY_INPUT_SPACE) == ePress)
	{
		return eInGame;	//ƒCƒ“ƒQ[ƒ€‰æ–Ê‚Ö
	}

	return eInGame;
}

void InGameSceneDraw(void)
{
	//”wŒi‰æ‘œ‚Ì•`‰æ
	/*DrawGraphF(scrool_x, 0, , TRUE);
	DrawGraphF(1280.0f + scrool_x, 0, , TRUE);*/

	//áŠQ•¨‚Ì•`‰æ
	ObstacleManagerDraw();

	//ƒvƒŒƒCƒ„[‚Ì•`‰æ
	PlayerDraw();
}


//‹éŒ`“¯Žm‚Ì“–‚½‚è”»’è‚ÌŒvŽZ•”•ª
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

//ƒCƒ“ƒQ[ƒ€BGMÄ¶
void PlayBgm(void)
{
	/*PlaySoundMem(, DX_PLAYTYPE_LOOP);*/
}

