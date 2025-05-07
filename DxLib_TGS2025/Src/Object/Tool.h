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
	int road_img;		//道の画像ハンドル
	int road_num;		//道の所持数
	int road_flag[40];		//道を置くときのフラグ
	int wood_road_img;	//丸太の道の画像ハンドル
	int wood_road_num;	//丸太の道の所持数
	int wood_road_flag;
	int rock_sub_flag;	//岩の数を引くフラグ
	int wood_sub_flag;	//木の数を引くフラグ
	float draw_x[10];	//描画座標ｘ
	float draw_y[10];	//描画座標ｙ
};

void ToolInit(void);
void ToolManagerUpdate(void);
void ToolDraw(void);
void Move_Frame(void);
void Put_Wood_Road(void);
void Sub_Num(void);
void Tool_Reset(void);
void Road_Flag_off(void);
void Wood_Road_Flag_off(void);


const Tool* Get_Tool(void);