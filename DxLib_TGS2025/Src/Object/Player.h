#pragma once

#include "../Utility/Geometry.h"
#include"../Utility/PadInputManager.h"

struct Player
{
	Position2D position;
	Size2D box_size;		//矩形の大きさ
	Vector2D velocity;
	int image;
	int is_jump;
};

void PlayerInit(void);
void PlayerUpdate(void);
void PlayerDraw(void);
const Player* GetPlayer(void);
void CursolButtonMovement();         // 十字キーの移動
static int move_lane_num;            // 移動レーン
static int move_wait_time;           // 移動するときの待ち時間