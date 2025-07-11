#pragma once

#include "../Utility/Geometry.h"
#include"../Utility/PadInputManager.h"
#include"../Object/Tool.h"
#include"../Object/map.h"


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
	int impossible[12];		//置けないマーク画像
	int img_count;			//画像のカウント
	int img_num;			//カウントに対応した変数
};

void CursorInit(void);
void CursorUpdate(void);
void CursorDraw(const Tool* tool);
const Cursor* GetCursor1(void);
void CursorReset(void);
void CursorResourceInit(void);
void FPS_Reset(void);