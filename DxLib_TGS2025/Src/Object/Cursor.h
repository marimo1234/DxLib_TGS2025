#pragma once

#include "../Utility/Geometry.h"
#include"../Utility/PadInputManager.h"
#include"../Object/Tool.h"


struct Cursor
{
	Position2D position;
	Size2D box_size;		//矩形の大きさ
	Vector2D velocity;
	int array_x;
	int array_y;
	int image;
	int is_jump;
	bool menu_flag;
	bool operable_flag;
	int array_x_min;
	int array_x_max;
	int array_y_min;
	int array_y_max;


	//仮
	int possible_rock;
};

void CursorInit(void);
void CursorUpdate(void);
void CursorDraw(const Tool* tool);
const Cursor* GetCursor1(void);
void CursorReset(void);
void CursorResourceInit(void);
