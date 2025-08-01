﻿#pragma once



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
	eHammer,
};

enum eOldPosition
{
	eRP,		//右
	eLP,		//左
	eTP,		//上
	eBP,		//下
};

enum eNowBaseState
{
	eBlank,
	eLake,
};

struct Tool
{
	int frameselect_x;				//選択枠のｘ座標
	int frameselect_y;				//選択枠のｙ座標
	int base_x;						//配列の基準ｘ
	int base_y;						//配列の基準ｙ
	int item_frame_x;				//枠のｘ座標
	int item_frame_y;				//枠のｙ座標

	int item_number;				//選択しているアイテムの種類
	int road_add_Acount[6];			//道の加算アニメーションカウント
	int woodroad_add_Acount[6];		//木の道の加算アニメーションカウント
	int road_num;					//道の所持数
	int road_flag[12][7];			//道を置いたことを知らせるフラグ
	int wood_road_num;				//木の道の所持数
	int wood_road_flag[12][7];		//木の道を置いたことを知らせるフラグ
	int road_img_array[12][7];		//道の画像ハンドル配列
	int stage_number;				//何ステージか
	int old_base_array[12][7];		//道を置いた順番
	int stage_array_exceed_x;		//ステージごとの配列上限（ｘ
	int stage_array_below_x;		//ステージごとの配列下限（ｘ
	int stage_array_exceed_y;		//ステージごとの配列上限（ｙ
	int stage_array_below_y;		//ステージごとの配列下限（ｙ
	int stage_begin_array[12][7];	//ステージ読み込み時の配列
	int old_position_direction;
	int now_base_state;
	int possible_fps;				//設置可能位置の点滅fps

	
	bool rock_sub_flag;				//岩の所持数を引くフラグ
	bool wood_sub_flag;				//木の所持数数を引くフラグ
	bool rock_add_flag;				//岩の所持数を足すフラグ
	bool wood_add_flag;				//木の所持数を足すフラグ

	int put_road_fps;
	int put_woodroad_fps;

	bool put_road_flag;
	bool put_woodroad_flag;

	bool menu_flag;
	bool mitibiki_flag;
};

struct Tool_Img
{
	int pickaxe;				//つるはしの画像ハンドル
	int itemframe;				//枠の画像ハンドル
	int ax;						//斧の画像ハンドル
	int item_select;			//選択枠（アイテム）の画像ハンドル
	int item_select_inner;		//選択枠（アイテム）の内側の画像ハンドル
	int wood_road_img;			//木の道の画像ハンドル
	int rb[2];					//Rトリガー
	int lb[2];					//Lトリガー
	
	int road_beside;			//左右への道の画像ハンドル
	int road_vertical;			//上下への道の画像ハンドル
	int road_Btmright;			//下右への道の画像ハンドル
	int road_Topright;			//上右への道の画像ハンドル
	int road_Rbottom;			//右下への道の画像ハンドル
	int road_Rtop;				//右上への道の画像ハンドル
	
	int wood_road_beside;		//左右への木の道の画像ハンドル
	int wood_road_vertical;		//上下への木の道の画像ハンドル
	int wood_road_Btmright;		//下右への木の道の画像ハンドル
	int wood_road_Topright;		//上右への木の道の画像ハンドル
	int wood_road_Rbottom;		//右下への木の道の画像ハンドル
	int wood_road_Rtop;			//右上への木の道の画像ハンドル
	
	int possible_roadB;			//設置可能位置の道の画像ハンドル(横
	int possible_roadV;			//設置可能位置の道の画像ハンドル(縦
	int possible_wood_roadB;	//設置可能位置の木の道の画像ハンドル(横
	int possible_wood_roadV;	//設置可能位置の木の道の画像ハンドル(縦
	
	int put_road[3];
	int put_woodroad[3];

	int make_animation[7];
	int make_animation2[7];
	int make_rx[6];				//道の数を増やしたときのアニメーション描画位置（ｘ
	int make_ry[6];				//道の数を増やしたときのアニメーション描画位置（ｙ
	int makeR_Anum[6];			//道の数を増やしたときのアニメーション描画画像番号
	int make_wrx[6];			//木の道の数を増やしたときのアニメーション描画位置（ｘ
	int make_wry[6];			//木の道の数を増やしたときのアニメーション描画位置（ｙ
	int makeWR_Anum[6];			//木の道の数を増やしたときのアニメーション描画画像番号

	float item_frame_ex_rate;	//アイテム枠の拡大率
	float pickaxe_ex_rate;		//つるはしの拡大率
	float ax_ex_rate;			//斧の拡大率

	float woodroad_ex_rate;		//木の道の拡大率
	float road_ex_rate;			//道の拡大率
	float road_num_ex_rate;		//道の所持数の拡大率
	float woodroad_num_ex_rate;	//木の道の所持数の拡大率
};

struct Tool_SE
{
	int wood_road;				//木の道のSE
	int road;					//道のSE
	int make_road;				//道の数を増やすときのSE
	int make_woodroad;			//木の道の数を増やすときのSE
	int select_se;				//アイテムセレクト欄SE
	int swing;					//ツール空振りのSE
};

void ToolInit(void);
void ToolManagerUpdate(void);
void ToolDraw(void);
void ToolResourceInit(void);
void Sub_Num(void);

void Base_Chenge(void);
void Road_FLAG_OFF(void);
void Add_Road_Num(void);
void Search_Old_Position(void);

const Tool* Get_Tool(void);