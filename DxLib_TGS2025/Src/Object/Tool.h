#pragma once



enum eToolMotionState
{
	PickaxeState1,
	PickaxeState2,
};

enum eToolState
{
	eRoad,
	eLog,
	eAx,
	ePickaxe,
};

struct Tool
{
	int item_number;	//選択しているアイテムの種類
	int road_num;		//道の所持数
	int sub_flag;		//岩の数を引くフラグ
	float draw_x[100];	//描画座標ｘ
	float draw_y[100];	//描画座標ｙ
};

void ToolInit(void);
void ToolManagerUpdate(void);
void ToolDraw(void);
void Move_Frame(void);
void Put_Road(void);
void Draw_Road(void);

const Tool* Get_Tool(void);

