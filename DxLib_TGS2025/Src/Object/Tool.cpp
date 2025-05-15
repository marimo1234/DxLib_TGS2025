#include "DxLib.h"
#include "Tool.h"
#include "../Utility/InputManager.h"
#include "../Utility/PadInputManager.h"
#include "../Scene/InGame/InGameScene.h"
#include "../Object/WoodRock.h"
#include "../Object/Cursor.h"
#include "../Object/map.h"


#define PICKAXE_X				(1120)		//つるはし(x)
#define PICKAXE_Y				(680)		//つるはし(y)
#define FRAME_X					(1000)		//枠(x)
#define FRAME_Y					(680)		//枠(y)
#define ROAD_X					(880)		//道路(x)
#define ROAD_Y					(680)		//道路(y)
#define WOODROAD_X				(960)		//木の道路(x)
#define WOODROAD_Y				(680)		//木の道路(y)
#define AX_X					(1040)		//斧(x)
#define AX_Y					(680)		//斧(y)
#define ROAD_NUM_X				(870)		//道路の所持数(x)
#define ROAD_NUM_Y				(690)		//道路の所持数(y)
#define WOODROAD_NUM_X			(950)		//木の道路の所持数(x)
#define WOODROAD_NUM_Y			(690)		//木の道路の所持数(y)
#define ITEM_SELECT_BASE		(1120)		//アイテムセレクトの基準(x)
#define MAP_TROUT_LENGTH		(80)		//マップの配列の
#define ARRAY_EXCEED_LIMIT_X	(12)		//配列要素を超過した値(x
#define ARRAY_BELOW_LIMIT_X		(-1)		//配列要素を下回った値(x
#define ARRAY_EXCEED_LIMIT_Y	(7)			//配列要素を超過した値(y
#define ARRAY_BELOW_LIMIT_Y		(-1)		//配列要素を下回った値(y

bool tool_start;			//ゲームスタート

Tool tool;
Tool_Img tool_img;

void Tool_Start(const InGame* ingame);
void const Road_Add_Num(const Rock* rock);
void const WoodRoad_Add_Num(const Wood* wood);
void Put_Road_FLAG(const Cursor*cursor,const CreateStage* stage);
void Put_Wood_Road_FLAG(const Cursor* cursor, const CreateStage* stage);
void Road_Imghandle_Init(const CreateStage* stage);
void Road_Imghandle_Update(const CreateStage* stage);
void Poosible_Prace(const CreateStage* stage);


//初期化
void ToolInit(void) 
{
	//初期化
	tool.frameselect_x = 1120;
	tool.frameselect_y = 680;
	tool.item_number = ePickaxe;
	tool.road_num = 0;
	tool.wood_road_num = 0;
	tool_start = false;
	tool.rock_sub_flag = false;
	tool.wood_sub_flag = false;
	tool.stage_number = 0;
	tool.stage_array_exceed_x = 0;
	tool.stage_array_exceed_y = 0;
	tool.stage_array_below_x = 0;
	tool.stage_array_below_y = 0;
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{				
			tool.road_flag[i][j] = false;
			tool.wood_road_flag[i][j] = false;
			tool.road_img_array[i][j] = -1;
			tool.old_base_array[i][j] = 0;
		}
	}
	Stage_Init();

	//******画像読み込み******//
	//アイテム枠
	tool_img.itemframe = LoadGraph("Resource/images/item_frame.png");
	//ピッケル
	tool_img.pickaxe=LoadGraph("Resource/images/pickaxe.png");
	//木の道
	tool.wood_road_img = LoadGraph("Resource/images/Log.png");
	//斧
	tool_img.ax = LoadGraph("Resource/images/ax2.0.png");
	//選択枠(アイテム)
	tool_img.item_select = LoadGraph("Resource/images/frameselect.png");
	//道
	tool_img.road_vertical = LoadGraph("Resource/images/RoadVertical.png");
	tool_img.road_beside = LoadGraph("Resource/images/RoadBeside.png");
	tool_img.road_Topright = LoadGraph("Resource/images/RoadTopRight.png");
	tool_img.road_Btmright = LoadGraph("Resource/images/RoadBottomRight.png");
	tool_img.road_Rbottom = LoadGraph("Resource/images/RoadRightBottom.png");
	tool_img.road_Rtop = LoadGraph("Resource/images/RoadRightTop.png");
	//透過させた道
	tool_img.possible_beside = LoadGraph("Resource/images/Possible_Beside.png");
	tool_img.possible_vertical= LoadGraph("Resource/images/Possible_Vertical.png");
	tool_img.possible_wood_road= LoadGraph("Resource/images/possible_wood_road.png");
	Road_Imghandle_Init(GetStage());
}

//更新
void ToolManagerUpdate(void)
{
	Sub_Num();
	Tool_Start(GetInGame());

	//ゲームスタートがtrueなら
	if (tool_start == true)
	{
		Move_ItemSelect();
		Road_WoodRoad_FLAG_OFF();
		//道路設置
		Put_Road_FLAG(GetCursor1(),GetStage());
		Put_Wood_Road_FLAG(GetCursor1(), GetStage());
	}
	else
	{
		Tool_Reset();
	}
	
	Road_Add_Num(GetRock());
	WoodRoad_Add_Num(GetWood());
}

//描画
void ToolDraw(void) 
{
	//アイテム枠
	DrawRotaGraph(FRAME_X, FRAME_Y, 1.0, 0.0, tool_img.itemframe, TRUE);
	//つるはしの描画（アイテム枠）
	DrawRotaGraph(PICKAXE_X, PICKAXE_Y, 0.5, 0.0, tool_img.pickaxe, TRUE);
	//斧の描画（アイテム枠）
	DrawRotaGraph(AX_X, AX_Y, 1.0, 0.0, tool_img.ax, TRUE);
	//道路の描画（アイテム枠）
	DrawRotaGraph(ROAD_X, ROAD_Y, 0.8, 0.0, tool_img.road_vertical, TRUE);
	//丸太の地面の描画（アイテム枠）
	DrawRotaGraph(WOODROAD_X, WOODROAD_Y, 0.4, 0.0, tool.wood_road_img, TRUE);
	//枠選択の描画（アイテム枠）
	DrawRotaGraph(tool.frameselect_x, tool.frameselect_y, 1.0, 0.0, tool_img.item_select, TRUE);
	//道路の所持数
	DrawExtendFormatString(ROAD_NUM_X, ROAD_NUM_Y, 1.5, 1.5, GetColor(255, 255, 255), "×%d", tool.road_num);
	//木の道の所持数
	DrawExtendFormatString(WOODROAD_NUM_X, WOODROAD_NUM_Y, 1.5, 1.5, GetColor(255, 255, 255), "×%d", tool.wood_road_num);
	//設置可能位置表示
	Poosible_Prace(GetStage());

	//仮
	DrawFormatString(50, 400, GetColor(255, 255, 255), "tool%d", tool.stage_number);
	
}

//アイテムセレクトの動き
void Move_ItemSelect(void)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//ＲＢが押されたら右にずれていく
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_RIGHT_SHOULDER) == ePadInputState::ePress)
	{
		switch (tool.item_number)
		{
		case eRoad:
			tool.item_number = eWoodRoad;
			break;
		case eWoodRoad:
			tool.item_number = eAx;
			break;
		case eAx:
			tool.item_number = ePickaxe;
			break;
		case ePickaxe:
			tool.item_number = eRoad;
			break;
		}
	}

	//ＬＢが押されたら左にずれていく
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_LEFT_SHOULDER) == ePadInputState::ePress)
	{
		switch (tool.item_number)
		{
		case eRoad:
			tool.item_number = ePickaxe;
			break;
		case eWoodRoad:
			tool.item_number = eRoad;
			break;
		case eAx:
			tool.item_number = eWoodRoad;
			break;
		case ePickaxe:
			tool.item_number = eAx;
			break;
		}
	}
	//x座標変更
	tool.frameselect_x = ITEM_SELECT_BASE - ((3 - tool.item_number) * 80);
}

//道路を置く
void Put_Road_FLAG(const Cursor* cursor,const CreateStage*stage)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	
	//Aボタンが押されたら
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{

		//アイテムが道路なら
		if (tool.item_number == 0)
		{

			//道路の数が0より多いなら
			if (tool.road_num > 0)
			{

				//ゴールとつながっていないなら
				if (((stage->array[tool.base_x + 1][tool.base_y] != 7) && (stage->array[tool.base_x][tool.base_y + 1]) != 7)&&stage->array[tool.base_x][tool.base_y-1]!=7)
				{
					//右の時
					if (cursor->array_x == tool.base_x + 1 && cursor->array_y == tool.base_y)
					{
						//カーソルの位置のマップの配列の中身が0なら
						if (stage->array[cursor->array_x][cursor->array_y] == 0)
						{
							tool.road_num--;
							tool.road_flag[cursor->array_x][cursor->array_y] = true;
							Base_Chenge();
							tool.base_x += 1;
						}
					}

					//左の時
					else if (cursor->array_x == tool.base_x-1 && cursor->array_y == tool.base_y)
					{
						//カーソルの位置のマップの配列の中身が0なら
						if (stage->array[cursor->array_x][cursor->array_y] == 0)
						{
							tool.road_num--;
							tool.road_flag[cursor->array_x][cursor->array_y] = true;
							Base_Chenge();
							tool.base_x -= 1;
						}
					}
					//上の時
					else if (cursor->array_x == tool.base_x && cursor->array_y == tool.base_y - 1)
					{
						//カーソルの位置のマップの配列の中身が0なら
						if (stage->array[cursor->array_x][cursor->array_y] == 0)
						{
							tool.road_num--;
							tool.road_flag[cursor->array_x][cursor->array_y] = true;
							Base_Chenge();
							tool.base_y -= 1;
						}
					}
					//下の時
					else if (cursor->array_x == tool.base_x && cursor->array_y == tool.base_y + 1)
					{
						//カーソルの位置のマップの配列の中身が0なら
						if (stage->array[cursor->array_x][cursor->array_y] == 0)
						{
							tool.road_num--;
							tool.road_flag[cursor->array_x][cursor->array_y] = true;
							Base_Chenge();
							tool.base_y += 1;
						}
					}
					Road_Imghandle_Update(GetStage());
				}
			}
		}
	}
}

//丸太の道路を置く
void Put_Wood_Road_FLAG(const Cursor* cursor, const CreateStage* stage)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	//Aボタンが押されたら
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{

		//アイテムが木の道路なら
		if (tool.item_number == 1)
		{

			//木の道路の数が0より多いなら
			if (tool.wood_road_num > 0)
			{

				//ゴールにつながっていないか
				if (((stage->array[tool.base_x + 1][tool.base_y] != 7) && (stage->array[tool.base_x][tool.base_y + 1]) != 7) && stage->array[tool.base_x][tool.base_y - 1] != 7)
				{
					//右の時
					if (cursor->array_x == tool.base_x + 1 && cursor->array_y == tool.base_y)
					{
						//カーソルの位置のマップの配列の中身が6なら
						if (stage->array[cursor->array_x][cursor->array_y] == 6)
						{
							tool.wood_road_num--;
							tool.wood_road_flag[cursor->array_x][cursor->array_y] = true;
							Base_Chenge();
							tool.base_x += 1;
						}
					}
					//左の時
					else if (cursor->array_x == tool.base_x - 1 && cursor->array_y == tool.base_y)
					{
						//カーソルの位置のマップの配列の中身が0なら
						if (stage->array[cursor->array_x][cursor->array_y] == 6)
						{
							tool.wood_road_num--;
							tool.wood_road_flag[cursor->array_x][cursor->array_y] = true;
							Base_Chenge();
							tool.base_x -= 1;
						}
					}
					//上の時
					else if (cursor->array_x == tool.base_x && cursor->array_y == tool.base_y - 1)
					{
						//カーソルの位置のマップの配列の中身が0なら
						if (stage->array[cursor->array_x][cursor->array_y] == 6)
						{
							tool.wood_road_num--;
							tool.wood_road_flag[cursor->array_x][cursor->array_y] = true;
							Base_Chenge();
							tool.base_y -= 1;
						}
					}
					//下の時
					else if (cursor->array_x == tool.base_x && cursor->array_y == tool.base_y + 1)
					{
						//カーソルの位置のマップの配列の中身が0なら
						if (stage->array[cursor->array_x][cursor->array_y] == 6)
						{
							tool.wood_road_num--;
							tool.wood_road_flag[cursor->array_x][cursor->array_y] = true;
							Base_Chenge();
							tool.base_y += 1;
						}
					}
					Road_Imghandle_Update(GetStage());
				}
			}
		}
	}
}

//道と木の道のフラグをFALSEにする
void Road_WoodRoad_FLAG_OFF(void)
{
	if (tool.road_flag[tool.base_x][tool.base_y] == true)
	{
		tool.road_flag[tool.base_x][tool.base_y] = false;
	}
	if (tool.wood_road_flag[tool.base_x][tool.base_y] == true)
	{
		tool.wood_road_flag[tool.base_x][tool.base_y] = false;
	}
} 

//ゲームスタート受け取り
void Tool_Start(const InGame* ingame)
{
	//TRUEならtoolもTRUEに
	if (ingame->start == true)
	{
		tool_start = true;
	}

	//そうでなければFALSEに
	else
	{
		tool_start = false;
	}

	//なんステージ目か
	/*tool.stage_number = ingame->stage_num;*/
}

//構造体Toolの値渡し
const Tool* Get_Tool(void)
{
	return &tool;
}

//道の数を増やす
void const Road_Add_Num(const Rock* rock)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//アイテムが道路なら
	if (tool.item_number == 0)
	{
		
		//岩の所持数が1以上なら
		if (rock->item_num >= 1)
		{

			//Ｂボタンが押されたら
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				tool.road_num++;
				tool.rock_sub_flag = true;
			}
		}
	}
}

//木の道の数を増やす
void const WoodRoad_Add_Num(const Wood* wood)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//アイテムが木の道路なら
	if (tool.item_number == 1)
	{

		//木の所持数が1以上なら
		if (wood->item_num >= 1)
		{

			//Ｂボタンが押されたら
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				tool.wood_road_num++;
				tool.wood_sub_flag = true;
			}
		}
	}
}

//木と岩の所持数を増やした後にフラグを戻す
void Sub_Num(void)
{
	//岩の所持数をマイナス1するフラグを元に戻す
	if (tool.rock_sub_flag == true)
	{
		tool.rock_sub_flag = false;
	}
	//木の所持数をマイナス1するフラグを元に戻す
	if (tool.wood_sub_flag == true)
	{
		tool.wood_sub_flag = false;
	}
}

//ステージ切り替え時の値リセット
void Tool_Reset(void)
{
	tool.item_number = ePickaxe;
	tool.road_num = 0;
	tool.wood_road_num = 0;
	tool.rock_sub_flag = false;
	tool.wood_sub_flag = false;
	tool.stage_number = 0;		//今だけ
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			tool.road_flag[i][j] = false;
			tool.wood_road_flag[i][j] = false;
			tool.road_img_array[i][j] = -1;
		}
	}
	Stage_Init();
	Road_Imghandle_Init(GetStage());
}

//道画像ハンドル初期化
void Road_Imghandle_Init(const CreateStage*stage)
{
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			if (stage->array[i][j]==4)
			{
				tool.road_img_array[i][j] = tool_img.road_beside;
			}
		}
	}
}

//ステージごとのの基準初期化
void Stage_Init(void)
{
	if (tool.stage_number == 0)
	{
		tool.base_x = 3;
		tool.base_y = 3;
		tool.old_base_array[2][3] = 1;
		tool.stage_array_exceed_x = 12;
		tool.stage_array_exceed_y = 7;
		tool.stage_array_below_x = -1;
		tool.stage_array_below_y = -1;
	}
}

//配列の基準変更
void Base_Chenge(void)
{
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			if (tool.old_base_array[i][j] > 0)
			{
				tool.old_base_array[i][j]++;
				tool.old_base_array[tool.base_x][tool.base_y] = 1;
			}
		}
	}
}

//道画像更新
void Road_Imghandle_Update(const CreateStage*stage)
{
	///******************************前に置いた道が左***********************************///
	if (tool.base_x - 1 > ARRAY_BELOW_LIMIT_X)
	{
		if (tool.old_base_array[tool.base_x - 1][tool.base_y] == 1)
		{

			/********************二つ前の道*********************/

			//二つ前に置いた道が左上なら
			if (tool.base_x - 1 > ARRAY_BELOW_LIMIT_X && tool.base_y - 1 > ARRAY_BELOW_LIMIT_Y)
			{
				if (tool.old_base_array[tool.base_x - 1][tool.base_y - 1] == 2)
				{
					//前に置いた道の画像ハンドル変更(下右
					tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.road_Btmright;
				}
			}
			//二つ前に置いた道が左下なら
			if (tool.base_x - 1 > ARRAY_BELOW_LIMIT_X && tool.base_y + 1 < ARRAY_EXCEED_LIMIT_Y)
			{
				if (tool.old_base_array[tool.base_x - 1][tool.base_y + 1] == 2)
				{
					//前に置いた道の画像ハンドル変更(上右
					tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.road_Topright;
				}
			}

			/***************************************************/


			/********************置いた道***********************/

			//置いた道の画像ハンドル代入
			//ゴールが上
			if (stage->array[tool.base_x][tool.base_y - 1] == 7)
			{
				tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Rtop;
			}

			//ゴールが下
			else if (stage->array[tool.base_x][tool.base_y + 1] == 7)
			{
				tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Rbottom;
			}

			else
			{
				tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_beside;
			}

			/***************************************************/
		}
	}
	///*********************************************************************************///
	





	
	///******************************前に置いた道が右***********************************///
	if (tool.base_x + 1 < ARRAY_EXCEED_LIMIT_X)
	{
		if (tool.old_base_array[tool.base_x + 1][tool.base_y] == 1)
		{

			/********************二つ前の道*********************/

			//二つ前に置いた道が右上なら
			if (tool.base_x + 1 < ARRAY_EXCEED_LIMIT_X && tool.base_y - 1 > ARRAY_BELOW_LIMIT_Y)
			{
				if (tool.old_base_array[tool.base_x + 1][tool.base_y - 1] == 2)
				{
					//前に置いた道の画像ハンドル変更(右上
					tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.road_Rtop;
				}
			}
			//二つ前に置いた道が左下なら
			if (tool.base_x + 1 < ARRAY_EXCEED_LIMIT_X && tool.base_y + 1 < ARRAY_EXCEED_LIMIT_Y)
			{
				if (tool.old_base_array[tool.base_x + 1][tool.base_y + 1] == 2)
				{
					//前に置いた道の画像ハンドル変更(右下
					tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.road_Rbottom;
				}
			}

			/***************************************************/


			/********************置いた道***********************/

			//置いた道の画像ハンドル代入
			//ゴールが上
			if (stage->array[tool.base_x][tool.base_y - 1] == 7)
			{
				tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Btmright;
			}

			//ゴールが下
			else if (stage->array[tool.base_x][tool.base_y + 1] == 7)
			{
				tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Topright;
			}

			else
			{
				tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_beside;
			}

			/***************************************************/

		}
	}
	///*********************************************************************************///






	///******************************前に置いた道が上***********************************///
	if (tool.base_y - 1 > ARRAY_BELOW_LIMIT_Y)
	{
		if (tool.old_base_array[tool.base_x][tool.base_y - 1] == 1)
		{

			/********************二つ前の道*********************/

			//二つ前に置いた道が左上なら
			if (tool.base_x - 1 > ARRAY_BELOW_LIMIT_X && tool.base_y - 1 > ARRAY_BELOW_LIMIT_Y)
			{
				if (tool.old_base_array[tool.base_x - 1][tool.base_y - 1] == 2)
				{
					//前に置いた道の画像ハンドル変更(右下
					tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.road_Rbottom;
				}
			}
			//二つ前に置いた道が右上なら
			if (tool.base_x + 1< ARRAY_EXCEED_LIMIT_X&& tool.base_y - 1> ARRAY_BELOW_LIMIT_Y)
			{
				if (tool.old_base_array[tool.base_x + 1][tool.base_y - 1] == 2)
				{
					//前に置いた道の画像ハンドル変更(上右
					tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.road_Topright;
				}
			}

			/***************************************************/


			/********************置いた道***********************/

			//置いた道の画像ハンドル代入
			//ゴールが右
			if (stage->array[tool.base_x + 1][tool.base_y] == 7)
			{
				tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Btmright;
			}

			//ゴールが左
			else if (stage->array[tool.base_x - 1][tool.base_y] == 7)
			{
				tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Rtop;
			}

			else
			{
				tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_vertical;
			}

			/***************************************************/

		}
	}
	///*********************************************************************************///






	///******************************前に置いた道が下***********************************///
	if (tool.base_y + 1< ARRAY_EXCEED_LIMIT_Y)
	{
		if (tool.old_base_array[tool.base_x][tool.base_y + 1] == 1)
		{

			/********************二つ前の道*********************/

			//二つ前に置いた道が左下なら
			if (tool.base_x - 1 > ARRAY_BELOW_LIMIT_X && tool.base_y + 1 < ARRAY_EXCEED_LIMIT_Y)
			{
				if (tool.old_base_array[tool.base_x - 1][tool.base_y + 1] == 2)
				{
					//前に置いた道の画像ハンドル変更(右上
					tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.road_Rtop;
				}
			}
			//二つ前に置いた道が右下なら
			if (tool.base_x + 1 < ARRAY_EXCEED_LIMIT_X && tool.base_y + 1 < ARRAY_EXCEED_LIMIT_Y)
			{
				if (tool.old_base_array[tool.base_x + 1][tool.base_y + 1] == 2)
				{
					//前に置いた道の画像ハンドル変更(下右
					tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.road_Btmright;
				}
			}

			/***************************************************/

			/********************置いた道***********************/

			//置いた道の画像ハンドル代入
			//ゴールが右
			if (stage->array[tool.base_x + 1][tool.base_y] == 7)
			{
				tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Topright;
			}

			//ゴールが左
			else if (stage->array[tool.base_x - 1][tool.base_y] == 7)
			{
				tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Rbottom;
			}

			else
			{
				tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_vertical;
			}

			/***************************************************/

		}
	}
	///********************************************************************************///
}

//道の設置可能位置
void Poosible_Prace(const CreateStage* stage)

{
	//ゴールではないなら
	if ((stage->array[tool.base_x + 1][tool.base_y] != 7 || stage->array[tool.base_x - 1][tool.base_y] != 7) ||
		(stage->array[tool.base_x][tool.base_y + 1] != 7 || stage->array[tool.base_x][tool.base_y - 1] != 7))
	{
		//アイテムが道なら
		if (tool.item_number == 0)
		{
			//道を一個以上持っているなら
			if (tool.road_num > 0)
			{

				//右が空
				if (tool.base_x + 1 < tool.stage_array_exceed_x && stage->array[tool.base_x + 1][tool.base_y] == 0)
				{
					DrawRotaGraphF(MAP_TROUT_LENGTH * (tool.base_x + 1) + 200, MAP_TROUT_LENGTH * tool.base_y + 120, 1.0, 0.0, tool_img.possible_beside, TRUE);
				}
				//左が空
				if (tool.base_x - 1 > tool.stage_array_below_x && stage->array[tool.base_x - 1][tool.base_y] == 0)
				{
					DrawRotaGraphF(MAP_TROUT_LENGTH * (tool.base_x - 1) + 200, MAP_TROUT_LENGTH * tool.base_y + 120, 1.0, 0.0, tool_img.possible_beside, TRUE);
				}
				//上が空
				if (tool.base_y - 1 > ARRAY_BELOW_LIMIT_Y && stage->array[tool.base_x][tool.base_y - 1] == 0)
				{
					DrawRotaGraphF(MAP_TROUT_LENGTH * tool.base_x + 200, MAP_TROUT_LENGTH * (tool.base_y - 1) + 120, 1.0, 0.0, tool_img.possible_vertical, TRUE);
				}
				//下が空
				if (tool.base_y + 1 < ARRAY_EXCEED_LIMIT_Y && stage->array[tool.base_x][tool.base_y + 1] == 0)
				{
					DrawRotaGraphF(MAP_TROUT_LENGTH * tool.base_x + 200, MAP_TROUT_LENGTH * (tool.base_y + 1) + 120, 1.0, 0.0, tool_img.possible_vertical, TRUE);
				}
			}
		}
		//アイテムが木の道なら
		else if (tool.item_number == 1)
		{
			//木の道を一個以上持っているなら
			if (tool.wood_road_num > 0)
			{
				//右が湖
				if (tool.base_x + 1 < tool.stage_array_exceed_x && stage->array[tool.base_x + 1][tool.base_y] == 6)
				{
					DrawRotaGraphF(MAP_TROUT_LENGTH * (tool.base_x + 1) + 200, MAP_TROUT_LENGTH * tool.base_y + 120, 0.5, 0.0, tool_img.possible_wood_road, TRUE);
				}
				//左が湖
				if (tool.base_x - 1 > tool.stage_array_below_x  && stage->array[tool.base_x - 1][tool.base_y] == 6)
				{
					DrawRotaGraphF(MAP_TROUT_LENGTH * (tool.base_x - 1) + 200, MAP_TROUT_LENGTH * tool.base_y + 120, 0.5, 0.0, tool_img.possible_wood_road, TRUE);
				}
				//上が湖
				if (tool.base_y - 1 > tool.stage_array_below_x && stage->array[tool.base_x][tool.base_y - 1] == 6)
				{
					DrawRotaGraphF(MAP_TROUT_LENGTH * tool.base_x + 200, MAP_TROUT_LENGTH * (tool.base_y - 1) + 120, 0.5, 0.0, tool_img.possible_wood_road, TRUE);
				}
				//下が湖
				if (tool.base_y + 1 < tool.stage_array_below_y && stage->array[tool.base_x][tool.base_y + 1] == 6)
				{
					DrawRotaGraphF(MAP_TROUT_LENGTH * tool.base_x + 200, MAP_TROUT_LENGTH * (tool.base_y + 1) + 120, 0.5, 0.0, tool_img.possible_wood_road, TRUE);
				}
			}
		}
	}
}