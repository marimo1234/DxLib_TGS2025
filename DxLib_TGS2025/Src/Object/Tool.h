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
	eHammer,
	eAx,
	ePickaxe,
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

	bool rock_sub_flag;				//岩の所持数を引くフラグ
	bool wood_sub_flag;				//木の所持数数を引くフラグ
	bool rock_add_flag;				//岩の所持数を足すフラグ
	bool wood_add_flag;				//木の所持数を足すフラグ
	bool road_break_flag[12][7];	//道を壊したことを伝えるフラグ


	int break_x;
	int break_y;
	int put_road_fps;
	int put_woodroad_fps;
	int break_road_fps;
	int break_woodroad_fps;

	bool put_road_flag;
	bool put_woodroad_flag;
	bool break_road_flag;
	bool break_woodroad_flag;

	int menu_flag;
	
	
};

struct Tool_Img
{
	int pickaxe;				//つるはしの画像ハンドル
	int itemframe;				//枠の画像ハンドル
	int ax;						//斧の画像ハンドル
	int drill;					//ドリルの画像ハンドル
	int item_select;			//選択枠（アイテム）の画像ハンドル
	int wood_road_img;			//木の道の画像ハンドル
	int rb;						//Rトリガー
	int lb;						//Lトリガー
	
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
	int possible_break;			//破壊可能位置の画像ハンドル
	
	int put_road[3];
	int put_woodroad[3];
	int break_road[3];
	int break_woodroad[3];

	float item_frame_ex_rate;	//アイテム枠の拡大率
	float pickaxe_ex_rate;		//つるはしの拡大率
	float ax_ex_rate;			//斧の拡大率
	float drill_ex_rate;		//ドリルの拡大率
	float woodroad_ex_rate;		//木の道の拡大率
	float road_ex_rate;			//道の拡大率
	float road_num_ex_rate;		//道の所持数の拡大率
	float woodroad_num_ex_rate;	//木の道の所持数の拡大率
};

struct Tool_SE
{
	int break_se;               //破壊時のSEハンドル
	int wood_road_se;			//木の道のサウンドハンドル
	int road_se;				//道のサウンドハンドル
	int craft_item_se;			//アイテム数を増やすときのサウンドハンドル
	int select_se;				//アイテムセレクト欄サウンドハンドル
};

void ToolInit(void);
void ToolManagerUpdate(void);
void ToolDraw(void);
void Move_ItemSelect(void);
void Sub_Num(void);

void Base_Chenge(void);
void Road_FLAG_OFF(void);
void Add_Road_Num(void);
void Item_Frame_Draw(void);
void Search_Old_Position(void);



const Tool* Get_Tool(void);