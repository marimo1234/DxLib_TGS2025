#include "DxLib.h"
#include "Tool.h"
#include "../Utility/InputManager.h"
#include "../Utility/PadInputManager.h"
#include "../Scene/InGame/InGameScene.h"
#include "../Object/WoodRock.h"
#include "../Object/Cursor.h"
#include "../Object/map.h"


#define PICKAXE_X			(1120)		//つるはし(x)
#define PICKAXE_Y			(680)		//つるはし(y)
#define FRAME_X				(1000)		//枠(x)
#define FRAME_Y				(680)		//枠(y)
#define ROAD_X				(880)		//道路(x)
#define ROAD_Y				(680)		//道路(y)
#define WOODROAD_X			(960)		//木の道路(x)
#define WOODROAD_Y			(680)		//木の道路(y)
#define AX_X				(1040)		//斧(x)
#define AX_Y				(680)		//斧(y)
#define ROAD_NUM_X			(870)		//道路の所持数(x)
#define ROAD_NUM_Y			(690)		//道路の所持数(y)
#define WOODROAD_NUM_X		(950)		//木の道路の所持数(x)
#define WOODROAD_NUM_Y		(690)		//木の道路の所持数(y)
#define ITEM_SELECT_BASE	(1120)		//アイテムセレクトの基準(x)

int tool_start;			//ゲームスタート

Tool tool;
Tool_Img tool_img;

void Tool_Start(const InGame* ingame);
void const Road_Add_Num(const Rock* rock);
void const WoodRoad_Add_Num(const Wood* wood);
void Put_Road_FLAG(const Cursor*cursor,const CreateStage* stage);
void Put_Wood_Road_FLAG(const Cursor* cursor, const CreateStage* stage);


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
	tool.base_x = 4;
	tool.base_y = 3;
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{				
			tool.road_flag[i][j] = false;
			tool.wood_road_flag[i][j] = false;
		}
	}
	//仮
	

	//アイテム枠画像読み込み
	tool_img.itemframe = LoadGraph("Resource/images/item_frame.png");
	//ピッケル画像読み込み
	tool_img.pickaxe=LoadGraph("Resource/images/pickaxe.png");
	//石の地面画像の読み込み
	tool.road_img=LoadGraph("Resource/images/stone_tiles.png");
	//丸太の地面画像の読み込み
	tool.wood_road_img = LoadGraph("Resource/images/Log.png");
	//斧の画像読み込み
	tool_img.ax = LoadGraph("Resource/images/ax.png");
	//選択枠(アイテム)の画像読み込み
	tool_img.item_select = LoadGraph("Resource/images/frameselect.png");

	//仮
	tool_img.road_vertical = LoadGraph("Resource/images/RoadVertical.png");
	tool_img.road_beside = LoadGraph("Resource/images/RoadBeside.png");
	tool_img.road_Rtop = LoadGraph("Resource/images/RoadTopRight.png");
	tool_img.road_Rbottom = LoadGraph("Resource/images/RoadBottomRight.png");
}

//更新
void ToolManagerUpdate(void)
{
	Sub_Num();

	//ゲームスタートがtrueなら
	if (tool_start == true)
	{
		Move_ItemSelect();
		//道路設置
		Put_Road_FLAG(GetCursor1(),GetStage());
		Put_Wood_Road_FLAG(GetCursor1(), GetStage());
	}
	else
	{
		Tool_Reset();
	}

	Tool_Start(GetInGame());
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
	DrawRotaGraph(ROAD_X, ROAD_Y, 0.8, 0.0, tool.road_img, TRUE);
	//丸太の地面の描画（アイテム枠）
	DrawRotaGraph(WOODROAD_X, WOODROAD_Y, 0.4, 0.0, tool.wood_road_img, TRUE);
	//枠選択の描画（アイテム枠）
	DrawRotaGraph(tool.frameselect_x, tool.frameselect_y, 1.0, 0.0, tool_img.item_select, TRUE);
	//道路の所持数
	DrawExtendFormatString(ROAD_NUM_X, ROAD_NUM_Y, 1.5, 1.5, GetColor(255, 255, 255), "×%d", tool.road_num);
	//木の道の所持数
	DrawExtendFormatString(WOODROAD_NUM_X, WOODROAD_NUM_Y, 1.5, 1.5, GetColor(255, 255, 255), "×%d", tool.wood_road_num);

	//仮
}

//アイテムセレクトの
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

				//
				if (((stage->array[tool.base_x + 1][tool.base_y] != 7) && (stage->array[tool.base_x][tool.base_y + 1]) != 7)&&stage->array[tool.base_x][tool.base_y-1]!=7)
				{
					//右の時
					if (cursor->array_x == tool.base_x + 1 && cursor->array_y == tool.base_y)
					{
						//カーソルの位置のマップの配列の中身が0なら
						if ((stage->array[cursor->array_x][cursor->array_y] == 0) ||
							(stage->array[cursor->array_x][cursor->array_y] == 5))
						{
							tool.road_num--;
							tool.road_flag[cursor->array_x][cursor->array_y] = true;
							tool.base_x += 1;
						}
					}
					//上の時
					else if (cursor->array_x == tool.base_x && cursor->array_y == tool.base_y - 1)
					{
						//カーソルの位置のマップの配列の中身が0なら
						if ((stage->array[cursor->array_x][cursor->array_y] == 0) ||
							(stage->array[cursor->array_x][cursor->array_y] == 5))
						{
							tool.road_num--;
							tool.road_flag[cursor->array_x][cursor->array_y] = true;
							tool.base_y -= 1;
						}
					}
					//下の時
					else if (cursor->array_x == tool.base_x && cursor->array_y == tool.base_y + 1)
					{
						//カーソルの位置のマップの配列の中身が0なら
						if ((stage->array[cursor->array_x][cursor->array_y] == 0) ||
							(stage->array[cursor->array_x][cursor->array_y] == 5))
						{
							tool.road_num--;
							tool.road_flag[cursor->array_x][cursor->array_y] = true;
							tool.base_y += 1;
						}
					}
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
						//カーソルの位置のマップの配列の中身が0なら
						if ((stage->array[cursor->array_x][cursor->array_y] == 6) ||
							(stage->array[cursor->array_x][cursor->array_y] == 4))
						{
							tool.wood_road_num--;
							tool.wood_road_flag[cursor->array_x][cursor->array_y] = true;
							tool.base_x += 1;
						}
					}
					//上の時
					else if (cursor->array_x == tool.base_x && cursor->array_y == tool.base_y - 1)
					{
						//カーソルの位置のマップの配列の中身が0なら
						if ((stage->array[cursor->array_x][cursor->array_y] == 6) ||
							(stage->array[cursor->array_x][cursor->array_y] == 4))
						{
							tool.wood_road_num--;
							tool.wood_road_flag[cursor->array_x][cursor->array_y] = true;
							tool.base_y -= 1;
						}
					}
					//下の時
					else if (cursor->array_x == tool.base_x && cursor->array_y == tool.base_y + 1)
					{
						//カーソルの位置のマップの配列の中身が0なら
						if ((stage->array[cursor->array_x][cursor->array_y] == 6) ||
							(stage->array[cursor->array_x][cursor->array_y] == 4))
						{
							tool.wood_road_num--;
							tool.wood_road_flag[cursor->array_x][cursor->array_y] = true;
							tool.base_y += 1;
						}
					}
				}
			}
		}
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
}

//Toolの値渡し
const Tool* Get_Tool(void)
{
	return &tool;
}

//岩の道を増やす
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

//木の道を増やす
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
	tool.road_num = 0;
	tool.wood_road_num = 0;
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			tool.road_flag[i][j] = false;
			tool.wood_road_flag[i][j] = false;
		}
	}
}