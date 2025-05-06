#pragma once

#include "../Utility/Geometry.h"
#include"../Utility/PadInputManager.h"


struct Cursor
{
	Position2D position;
	Size2D box_size;		//矩形の大きさ
	Vector2D velocity;
	int array_x;
	int array_y;
	int image;
	int is_jump;

};

void CursorInit(void);
void CursorUpdate(void);
void CursorDraw(void);
const Cursor* GetCursor1(void);
void CursolButtonMovement();         // 十字キーの移動
