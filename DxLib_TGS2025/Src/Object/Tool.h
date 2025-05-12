#pragma once



enum eToolMotionState
{
	PickaxeState1,
	PickaxeState2,
};

enum eToolState
{
	eRoad,
	eWoodRoad,
	eAx,
	ePickaxe,
};

enum eRoadImgState
{
	eVertical,		//縦
	eBeside,		//横
	eRtop,			//右上
	eRbottom,		//右下
};

struct Tool
{
	int frameselect_x;			//選択枠のｘ座標
	int frameselect_y;			//選択枠のｙ座標
	int base_x;					//配列の基準ｘ
	int base_y;					//配列の基準ｙ
	int item_number;			//選択しているアイテムの種類
	int road_img;				//道の画像ハンドル
	int road_num;				//道の所持数
	int road_flag[12][7];		//道を置いたことを知らせるフラグ
	int wood_road_img;			//丸太の道の画像ハンドル
	int wood_road_num;			//丸太の道の所持数
	int wood_road_flag[12][7];	//丸太の道を置いたことを知らせるフラグ
	int rock_sub_flag;			//岩の所持数を引くフラグ
	int wood_sub_flag;			//木の所持数数を引くフラグ
};

struct Tool_Img
{
	int pickaxe;		//つるはしの画像ハンドル
	int itemframe;		//枠の画像ハンドル
	int ax;				//斧の画像ハンドル
	int item_select;	//選択枠（アイテム）の画像ハンドル
	int road_beside;	//左右への道の画像ハンドル
	int road_vertical;	//上下への道の画像ハンドル
	int road_Rbottom;	//右下への道の画像ハンドル
	int road_Rtop;		//右上への道の画像ハンドル
};

void ToolInit(void);
void ToolManagerUpdate(void);
void ToolDraw(void);
void Move_ItemSelect(void);
void Sub_Num(void);
void Tool_Reset(void);


const Tool* Get_Tool(void);