﻿#include "DxLib.h"
#include "stdbool.h"
#include "Tool.h"
#include "../Utility/InputManager.h"
#include "../Utility/PadInputManager.h"
#include "../Scene/InGame/InGameScene.h"
#include "../Object/WoodRock.h"
#include "../Object/Cursor.h"
#include "../Object/map.h"
#include "../Object/car.h"
#include "../Object/Goal.h"
#include "../Object/Obstacle.h"

#define ITEM_SELECT_BASE_X		(880)		//アイテムの基準(x)
#define ITEM_SELECT_BASE_Y		(680)		//アイテムの基準(y)	//680,40
#define MAP_TROUT_LENGTH		(80)		//マップの配列の間隔
#define ARRAY_EXCEED_LIMIT_X	(12)		//配列要素を超過した値(x
#define ARRAY_BELOW_LIMIT_X		(-1)		//配列要素を下回った値(x
#define ARRAY_EXCEED_LIMIT_Y	(7)			//配列要素を超過した値(y
#define ARRAY_BELOW_LIMIT_Y		(-1)		//配列要素を下回った値(y

bool tool_start;			//ゲームスタート

int abcd;

Tool tool;
Tool_Img tool_img;
Tool_SE tool_se;

void Tool_Start(const InGame* ingame, const Goal* goal, const GameOver* gameover, const Car* car);
void const Road_Add_Num(const Rock* rock,const Car*car);
void const WoodRoad_Add_Num(const Wood* wood,const Car*car);
void Put_Road(const Cursor*cursor,const CreateStage* stage,const Mole*mole, const Car* car);
void Put_Wood_Road(const Cursor* cursor, const CreateStage* stage,const Car *car);
void Put_Road_Process(bool* flag, int* sub_num, int array[][7],int array_x, int array_y, int base_x, int base_y,int sound,int val);
void Road_Imghandle_Init(int x1, int y1, int x2, int y2, int x3, int y3);
void Road_Imghandle_Update(const CreateStage* stage);
void Item_Frame_Draw(const Car*car);
void Move_ItemSelect(const Car*car);
void Possible_Prace(const CreateStage* stage,const Car*car);
void Stage_Init(const CreateStage*stage);
void Now_Base_State(const CreateStage* stage);
void Old_Position_Left(const CreateStage* stage);
void Old_Position_Right(const CreateStage* stage);
void Old_Position_Top(const CreateStage* stage);
void Old_Position_Bottom(const CreateStage* stage);
bool Check_Outside_Array(int x, int y, int val);
bool Check_Outside_Array2(int x, int y, const CreateStage* stage, int val);
void Tool_Reset(const CreateStage*stage, const InGame* ingame);
void Put_Road_Animation(int x, int y);
void Put_WoodRoad_Animation(int x, int y);
void RB_Draw(const Car*car);
void LB_Draw(const Car*car);
void Road_Add_Animation(const Car*car);
void WoodRoad_Add_Animation(const Car*car);

void Play_Sound_Tool(int sound,int volume);
void Play_Sound_Tool2(int sound,int volume);


//変数初期化
void ToolInit(void) 
{
	//初期化//
	tool.frameselect_x = ITEM_SELECT_BASE_X+80*3;
	tool.frameselect_y = ITEM_SELECT_BASE_Y;
	tool.item_frame_x = ITEM_SELECT_BASE_X;
	tool.item_frame_y = ITEM_SELECT_BASE_Y;
	tool.item_number = ePickaxe;
	tool.old_position_direction = eLP;
	tool.now_base_state = eBlank;
	tool.road_num = 0;
	tool.wood_road_num = 0;
	tool_start = false;
	tool.menu_flag = false;
	tool.mitibiki_flag = false;
	tool.rock_sub_flag = false;
	tool.wood_sub_flag = false;
	tool.rock_add_flag = false;
	tool.wood_add_flag = false;
	tool.stage_number = 0;
	tool.stage_array_exceed_x = 0;
	tool.stage_array_exceed_y = 0;
	tool.stage_array_below_x = -1;
	tool.stage_array_below_y = -1;

	tool_img.item_frame_ex_rate = 1.0f;
	tool_img.pickaxe_ex_rate = 0.4f;
	tool_img.ax_ex_rate = 0.8f;
	tool_img.woodroad_ex_rate = 0.6f;
	tool_img.road_ex_rate = 0.6f;
	tool_img.road_num_ex_rate = 1.0f;
	tool_img.woodroad_num_ex_rate = 1.0f;

	//アニメーション関係
	tool.put_road_fps = 0;
	tool.put_woodroad_fps = 0;
	tool.possible_fps = 0;

	tool.put_woodroad_flag = false;
	tool.put_road_flag = false;


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
	Stage_Init(GetStage());
}

//音源、画像初期化
void ToolResourceInit(void)
{
	/**********サウンド***********/
	//アイテムセレクトSE
	tool_se.select_se = LoadSoundMem("Resource/Sounds/item_select_se2.mp3");
	//道や木の橋等を増やすときのSE
	tool_se.make_road = LoadSoundMem("Resource/Sounds/make_road.mp3");
	tool_se.make_woodroad = LoadSoundMem("Resource/Sounds/make_woodroad.mp3");

	tool_se.wood_road = LoadSoundMem("Resource/Sounds/wood_road.mp3");

	tool_se.road = LoadSoundMem("Resource/Sounds/put_road_se.mp3");

	tool_se.swing = LoadSoundMem("Resource/Sounds/swing.mp3");

	//******画像読み込み******//
	//アイテム枠
	tool_img.itemframe = LoadGraph("Resource/images/item_frame.png");
	//R,Lトリガー
	tool_img.rb[0] = LoadGraph("Resource/images/RB.png");
	tool_img.rb[1] = LoadGraph("Resource/images/RB_right.png");
	tool_img.lb[0] = LoadGraph("Resource/images/LB.png");
	tool_img.lb[1] = LoadGraph("Resource/images/LB_right.png");


	//ピッケル
	tool_img.pickaxe = LoadGraph("Resource/images/pickaxe.png");
	//木の道
	tool_img.wood_road_img = LoadGraph("Resource/images/Log.png");
	tool_img.wood_road_vertical = LoadGraph("Resource/images/wooodroad_vertical.png");
	tool_img.wood_road_beside = LoadGraph("Resource/images/wooodroad_beside.png");
	tool_img.wood_road_Topright = LoadGraph("Resource/images/woodroad_TR.png");
	tool_img.wood_road_Btmright = LoadGraph("Resource/images/woodroad_BR.png");
	tool_img.wood_road_Rbottom = LoadGraph("Resource/images/woodroad_RB.png");
	tool_img.wood_road_Rtop = LoadGraph("Resource/images/woodroad_RTop.png");

	//斧
	tool_img.ax = LoadGraph("Resource/images/ax2.0.png");
	//選択枠(アイテム)
	tool_img.item_select = LoadGraph("Resource/images/frameselect.png");
	//選択枠の内側(アイテム)
	tool_img.item_select_inner = LoadGraph("Resource/images/item_frame_inner.png");
	//道
	tool_img.road_vertical = LoadGraph("Resource/images/RoadVertical.png");
	tool_img.road_beside = LoadGraph("Resource/images/RoadBeside.png");
	tool_img.road_Topright = LoadGraph("Resource/images/RoadTopRight.png");
	tool_img.road_Btmright = LoadGraph("Resource/images/RoadBottomRight.png");
	tool_img.road_Rbottom = LoadGraph("Resource/images/RoadRightBottom.png");
	tool_img.road_Rtop = LoadGraph("Resource/images/RoadRightTop.png");

	//透過させた道
	tool_img.possible_roadB = LoadGraph("Resource/images/Possible_Beside.png");
	tool_img.possible_roadV = LoadGraph("Resource/images/Possible_Vertical.png");
	tool_img.possible_wood_roadB = LoadGraph("Resource/images/Possible_wood_roadB.png");
	tool_img.possible_wood_roadV = LoadGraph("Resource/images/Possible_wood_roadV.png");
	//道を置いた時のアニメーション
	tool_img.put_road[0] = LoadGraph("Resource/images/dust1.png");
	tool_img.put_road[1] = LoadGraph("Resource/images/dust2.png");
	tool_img.put_road[2] = LoadGraph("Resource/images/dust3.png");
	//木の道を置いた時のアニメーション
	tool_img.put_woodroad[0] = LoadGraph("Resource/images/put1.png");
	tool_img.put_woodroad[1] = LoadGraph("Resource/images/put2.png");
	//道が増えた時のアニメーション
	LoadDivGraph("Resource/images/make_effect.png", 7, 7, 1, 60, 60, tool_img.make_animation);
	LoadDivGraph("Resource/images/make_effect2.png", 7, 7, 1, 60, 60, tool_img.make_animation2);
}

//更新
void ToolManagerUpdate(void)
{
	Tool_Start(GetInGame(),GetGoal(),GetGameOver(),GetCar());

	//ゲームスタートがtrueなら
	if (tool_start == true&& tool.menu_flag == false&&tool.mitibiki_flag==false)
	{
		Sub_Num();
		Add_Road_Num();
		Road_FLAG_OFF();
		Move_ItemSelect(GetCar());
		Road_Add_Num(GetRock(),GetCar());
		WoodRoad_Add_Num(GetWood(),GetCar());
		Put_Road(GetCursor1(),GetStage(),GetMole(), GetCar());
		Put_Wood_Road(GetCursor1(), GetStage(),GetCar());
	}
	else if (tool_start == false && tool.menu_flag == false && tool.mitibiki_flag == false)
	{
		Tool_Reset(GetStage(), GetInGame());
	}
}

//描画
void ToolDraw(void)
{

	//アイテム欄
	Item_Frame_Draw(GetCar());

	//R,Lトリガー
	RB_Draw(GetCar());
	LB_Draw(GetCar());

	//数アニメーション
	Road_Add_Animation(GetCar());
	WoodRoad_Add_Animation(GetCar());

	//アニメーション
	if (tool.put_road_flag == true)
	{
		Put_Road_Animation(tool.base_x, tool.base_y);
	}
	if (tool.put_woodroad_flag == true)
	{
		Put_WoodRoad_Animation(tool.base_x, tool.base_y);
	}

	//設置可能位置表示
	Possible_Prace(GetStage(), GetCar());
}

//アイテムセレクトの動き
void Move_ItemSelect(const Car*car)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	
	//ゴールとゲームオーバーじゃないじゃら
	if (car->goal_flag == false && car->direction != eStop)
	{

		//ＲＢが押されたら右にずれていく
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_RIGHT_SHOULDER) == ePadInputState::ePress)
		{
			switch (tool.item_number)
			{
			case eRoad:
				tool.possible_fps = 0;		//点滅fpsリセット
				tool.item_number = eWoodRoad;
				Play_Sound_Tool(tool_se.select_se, 100);
				break;
			case eWoodRoad:
				tool.item_number = eAx;
				Play_Sound_Tool(tool_se.select_se, 100);
				break;
			case eAx:
				tool.item_number = ePickaxe;
				Play_Sound_Tool(tool_se.select_se, 100);
				break;
			case ePickaxe:
				tool.possible_fps = 0;		//点滅fpsリセット
				tool.item_number = eRoad;
				Play_Sound_Tool(tool_se.select_se, 100);
				break;
			/*case eHammer:
				tool.item_number = eRoad;
				Play_Sound_Tool(tool_se.select_se, 100);
				break;*/
			}
		}

		//ＬＢが押されたら左にずれていく
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_LEFT_SHOULDER) == ePadInputState::ePress)
		{
			switch (tool.item_number)
			{
			case eRoad:
				tool.item_number = ePickaxe;
				Play_Sound_Tool(tool_se.select_se, 100);
				break;
			case eWoodRoad:
				tool.possible_fps = 0;		//点滅fpsリセット
				tool.item_number = eRoad;
				Play_Sound_Tool(tool_se.select_se, 100);
				break;
			case eAx:
				tool.possible_fps = 0;		//点滅fpsリセット
				tool.item_number = eWoodRoad;
				Play_Sound_Tool(tool_se.select_se, 100);
				break;
			case ePickaxe:
				tool.item_number = eAx;
				Play_Sound_Tool(tool_se.select_se, 100);
				break;
			/*case eHammer:
				tool.item_number = eAx;
				Play_Sound_Tool(tool_se.select_se, 100);
				break;*/
			}
		}
		//x座標変更
		tool.frameselect_x = ITEM_SELECT_BASE_X + (tool.item_number * 80);
	}
}

//アイテム欄描画
void Item_Frame_Draw(const Car*car)
{
	//アイテム枠
	tool.item_frame_x = ITEM_SELECT_BASE_X;
	
	//アイテム
	switch (tool.item_number)
	{
	case ePickaxe:
		tool_img.pickaxe_ex_rate += 0.15f;
		break;
	case eAx:
		tool_img.ax_ex_rate += 0.3f;
		break;
	case eWoodRoad:
		tool_img.woodroad_ex_rate += 0.2f;
		tool_img.woodroad_num_ex_rate += 0.2f;
		break;
	case eRoad:
		tool_img.road_ex_rate += 0.2f;
		tool_img.road_num_ex_rate += 0.2f;
		break;
	}
	if (tool_start == true && car->direction != eStop && car->goal_flag == false)
	{
		for (int i = 0; i < 4; i++)
		{
			DrawRotaGraph(tool.item_frame_x, tool.item_frame_y, tool_img.item_frame_ex_rate, 0.0, tool_img.itemframe, TRUE);
			tool.item_frame_x += 80;
		}

		//選択枠の内側
		DrawRotaGraph(tool.frameselect_x, tool.frameselect_y, 1.0, 0.0, tool_img.item_select_inner, TRUE);
		//つるはしの描画（アイテム枠）
		DrawRotaGraph(ITEM_SELECT_BASE_X + 80 * 3, ITEM_SELECT_BASE_Y, tool_img.pickaxe_ex_rate, 0.0, tool_img.pickaxe, TRUE);
		//斧の描画（アイテム枠）
		DrawRotaGraph(ITEM_SELECT_BASE_X + 80 * 2, ITEM_SELECT_BASE_Y, tool_img.ax_ex_rate, 0.0, tool_img.ax, TRUE);
		//木の道の描画（アイテム枠）
		DrawRotaGraph(ITEM_SELECT_BASE_X + 80 * 1, ITEM_SELECT_BASE_Y, tool_img.woodroad_ex_rate, 0.0, tool_img.wood_road_img, TRUE);
		//道路の描画（アイテム枠）
		DrawRotaGraph(ITEM_SELECT_BASE_X, ITEM_SELECT_BASE_Y, tool_img.road_ex_rate, 0.0, tool_img.road_vertical, TRUE);

		//道路の所持数
		if (tool.road_num>99)
		{
			DrawExtendFormatString(ITEM_SELECT_BASE_X - 10, ITEM_SELECT_BASE_Y + 10, tool_img.road_num_ex_rate, tool_img.road_num_ex_rate, GetColor(0, 0, 0), "99+");
		}
		else
		{
			DrawExtendFormatString(ITEM_SELECT_BASE_X - 10, ITEM_SELECT_BASE_Y + 10, tool_img.road_num_ex_rate, tool_img.road_num_ex_rate, GetColor(0, 0, 0), "×%d", tool.road_num);
		}
		
		//木の道の所持数
		if (tool.wood_road_num > 99)
		{
			DrawExtendFormatString(ITEM_SELECT_BASE_X + 70, ITEM_SELECT_BASE_Y + 10, tool_img.woodroad_num_ex_rate, tool_img.woodroad_num_ex_rate, GetColor(0, 0, 0), "99+");
		}
		else
		{
			DrawExtendFormatString(ITEM_SELECT_BASE_X + 70, ITEM_SELECT_BASE_Y + 10, tool_img.woodroad_num_ex_rate, tool_img.woodroad_num_ex_rate, GetColor(0, 0, 0), "×%d", tool.wood_road_num);
		}
		

		//選択枠
		DrawRotaGraph(tool.frameselect_x, tool.frameselect_y, 1.0, 0.0, tool_img.item_select, TRUE);
	}
	switch (tool.item_number)
	{
	case ePickaxe:
		tool_img.pickaxe_ex_rate -= 0.15;
		break;
	case eAx:
		tool_img.ax_ex_rate -= 0.3;
		break;
	case eWoodRoad:
		tool_img.woodroad_ex_rate -= 0.2f;
		tool_img.woodroad_num_ex_rate -= 0.2f;
		break;
	case eRoad:
		tool_img.road_ex_rate -= 0.2f;
		tool_img.road_num_ex_rate -= 0.2f;
		break;
	}
}

//RB描画
void RB_Draw(const Car* car)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	if (tool_start == true && car->direction != eStop && car->goal_flag == false)
	{
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_RIGHT_SHOULDER) == ePadInputState::eHold
			&& tool.menu_flag == false)
		{
			DrawRotaGraph(ITEM_SELECT_BASE_X + 330, ITEM_SELECT_BASE_Y, 0.15, 0.0, tool_img.rb[0], TRUE);
		}
		else
		{
			DrawRotaGraph(ITEM_SELECT_BASE_X + 330, ITEM_SELECT_BASE_Y, 0.15, 0.0, tool_img.rb[1], TRUE);
		}
	}
}

//LB描画
void LB_Draw(const Car* car)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	if ( tool_start == true  && car->direction != eStop && car->goal_flag == false)
	{
		if(pad_input->GetButtonInputState(XINPUT_BUTTON_LEFT_SHOULDER) == ePadInputState::eHold
			&& tool.menu_flag == false)
		{
			DrawRotaGraph(ITEM_SELECT_BASE_X - 90, ITEM_SELECT_BASE_Y, 0.15, 0.0, tool_img.lb[0], TRUE);
		}
	else
	{
		if (tool_start == true)
		{
			DrawRotaGraph(ITEM_SELECT_BASE_X - 90, ITEM_SELECT_BASE_Y, 0.15, 0.0, tool_img.lb[1], TRUE);
		}
	}
	}
}

//道を置く
void Put_Road(const Cursor* cursor,const CreateStage*stage,const Mole*mole,const Car*car)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	
	//Aボタンが押されたら
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{

		//アイテムが道路なら
		if (tool.item_number == eRoad&& car->direction != eStop)
		{

			//道路の数が0より多いなら
			if (tool.road_num > 0 && mole->put_rock_flag[cursor->array_x][cursor->array_y] == false)
			{

				if (car->goal_flag == false)
				{

					//右の時,カーソルの位置のマップの配列の中身が0なら
					if ((cursor->array_x == tool.base_x + 1 && cursor->array_y == tool.base_y) &&
						(stage->array[tool.base_x + 1][tool.base_y] == 0))
					{
						Put_Road_Process(&tool.put_road_flag, &tool.road_num, tool.road_flag, tool.base_x + 1, tool.base_y, 1, 0, tool_se.road, 110);
					}

					//左の時,カーソルの位置のマップの配列の中身が0なら
					else if ((cursor->array_x == tool.base_x - 1 && cursor->array_y == tool.base_y) &&
						(stage->array[tool.base_x - 1][tool.base_y] == 0))
					{
						Put_Road_Process(&tool.put_road_flag, &tool.road_num, tool.road_flag,tool.base_x - 1, tool.base_y, -1, 0, tool_se.road,110);
					}

					//上の時,カーソルの位置のマップの配列の中身が0なら
					else if ((cursor->array_x == tool.base_x && cursor->array_y == tool.base_y - 1) &&
						(stage->array[tool.base_x][tool.base_y - 1] == 0))
					{
						Put_Road_Process(&tool.put_road_flag, &tool.road_num, tool.road_flag,tool.base_x, tool.base_y - 1, 0, -1, tool_se.road,110);
					}

					//下の時,カーソルの位置のマップの配列の中身が0なら
					else if ((cursor->array_x == tool.base_x && cursor->array_y == tool.base_y + 1) &&
						(stage->array[tool.base_x][tool.base_y + 1] == 0))
					{
						Put_Road_Process(&tool.put_road_flag, &tool.road_num, tool.road_flag,tool.base_x, tool.base_y + 1, 0, 1, tool_se.road,110);
					}
				}
			}
		}
	}
}

//木の道を置く
void Put_Wood_Road(const Cursor* cursor, const CreateStage* stage,const Car*car)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	//Aボタンが押されたら
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{

		//アイテムが木の道路なら
		if (tool.item_number == eWoodRoad)
		{

			//木の道路の数が0より多いなら
			if (tool.wood_road_num > 0 && car->direction != eStop)
			{
				if (car->goal_flag == false)
				{
					//右の時,カーソルの位置のマップの配列の中身が6なら
					if ((cursor->array_x == tool.base_x + 1 && cursor->array_y == tool.base_y) &&
						stage->array[tool.base_x + 1][tool.base_y] == 6)
					{
						Put_Road_Process(&tool.put_woodroad_flag, &tool.wood_road_num, tool.wood_road_flag, tool.base_x + 1, tool.base_y, 1, 0, tool_se.wood_road, 100);
					}

					//左の時,カーソルの位置のマップの配列の中身が0なら
					else if ((cursor->array_x == tool.base_x - 1 && cursor->array_y == tool.base_y) &&
						stage->array[tool.base_x - 1][tool.base_y] == 6)
					{
						Put_Road_Process(&tool.put_woodroad_flag, &tool.wood_road_num, tool.wood_road_flag, tool.base_x - 1, tool.base_y, -1, 0, tool_se.wood_road, 100);
					}

					//上の時,カーソルの位置のマップの配列の中身が0なら
					else if ((cursor->array_x == tool.base_x && cursor->array_y == tool.base_y - 1) &&
						stage->array[tool.base_x][tool.base_y - 1] == 6)
					{
						Put_Road_Process(&tool.put_woodroad_flag, &tool.wood_road_num, tool.wood_road_flag, tool.base_x, tool.base_y - 1, 0, -1, tool_se.wood_road, 100);
					}

					//下の時,カーソルの位置のマップの配列の中身が0なら
					else if ((cursor->array_x == tool.base_x && cursor->array_y == tool.base_y + 1) &&
						stage->array[tool.base_x][tool.base_y + 1] == 6)
					{
						Put_Road_Process(&tool.put_woodroad_flag, &tool.wood_road_num, tool.wood_road_flag, tool.base_x, tool.base_y + 1, 0, 1, tool_se.wood_road, 100);
					}
				}
			}
		}
	}
}

//置いた時の処理関数
void Put_Road_Process(bool* flag, int* sub_num,  int array[][7], int array_x, int array_y, int base_x, int base_y, int sound, int val)
{
	*flag = true;
	(*sub_num)--;
	array[array_x][array_y] = true;
	tool.possible_fps = 0;
	Base_Chenge();
	tool.base_x += base_x;
	tool.base_y += base_y;
	Road_Imghandle_Update(GetStage());
	Play_Sound_Tool(sound, val);
}

//道と木の道のフラグをFALSEにする
void Road_FLAG_OFF(void)
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
void Tool_Start(const InGame* ingame, const Goal* goal, const GameOver* gameover, const Car* car)
{
	//TRUEならtoolもTRUEに
	if (ingame->start == true&& ingame->menu_flag == false && ingame->mitibiki_flag == false)
	{
		tool_start = true;
	}

	//そうでなければFALSEに
	else if(ingame->start == false && ingame->menu_flag == false&&ingame->mitibiki_flag==false)
	{
		tool_start = false;
	}	

	tool.menu_flag = ingame->menu_flag;
	tool.mitibiki_flag = ingame->mitibiki_flag;
}

//構造体Toolの値渡し
const Tool* Get_Tool(void)
{
	return &tool;
}

//構造体Tool_Imgの値渡し
const Tool_Img* Get_Tool_Img(void)
{
	return &tool_img;
}

//道の数を増やす
void const Road_Add_Num(const Rock* rock, const Car* car)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//岩の所持数が1以上なら
	if (rock->item_num >= 1)
	{
		//ゴールとゲームオーバーじゃないじゃら
		if (car->goal_flag == false && car->direction != eStop)
		{
			tool.road_num++;
			tool.rock_sub_flag = true;
			Play_Sound_Tool2(tool_se.make_road, 100);

			for (int i = 0; i < 6; i++)
			{
				if (i == 0&&tool.road_add_Acount[0]==0)
				{
					tool_img.make_rx[i] = GetRand(400) % (900 - 860 + 1) + 860;
					tool_img.make_ry[i] = 650;
					tool.road_add_Acount[i]++;
					break;
				}
				else if (i != 0 && tool.road_add_Acount[i] == 0)
				{
					tool_img.make_rx[i] = GetRand(400) % (900 - 860 + 1) + 860;
					tool_img.make_ry[i] = 650;
					tool.road_add_Acount[i]++;
					break;
				}
			}
		}
	}
}

//道が増えた時の+1を描画する
void Road_Add_Animation(const Car*car)
{
	if (tool_start == true && car->direction != eStop && car->goal_flag == false)
	{
		for (int i = 0; i < 6; i++)
		{

			if (tool.road_add_Acount[i] > 69)
			{
				tool.road_add_Acount[i] = 0;
				continue;
			}
			if (tool.road_add_Acount[i] > 0)
			{
				tool_img.makeR_Anum[i] = tool.road_add_Acount[i] / 10;
				DrawRotaGraph(tool_img.make_rx[i], tool_img.make_ry[i] - tool.road_add_Acount[i], 0.8, 0.0, tool_img.make_animation2[tool_img.makeR_Anum[i]], TRUE);
				tool.road_add_Acount[i]++;
			}
		}
	}
}

//木の道の数を増やす
void const WoodRoad_Add_Num(const Wood* wood, const Car* car)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//木の所持数が1以上なら
	if (wood->item_num >= 1)
	{
		//ゴールとゲームオーバーじゃないじゃら
		if (car->goal_flag == false && car->direction != eStop)
		{
			////Ｂボタンが押されたら

			tool.wood_road_num++;
			tool.wood_sub_flag = true;
			Play_Sound_Tool2(tool_se.make_woodroad, 100); // 木の道を作ったときの音

			for (int i = 0; i < 6; i++)
			{
				if (i == 0 && tool.woodroad_add_Acount[0] == 0)
				{
					tool_img.make_wrx[i] = GetRand(400) % (980 - 940 + 1) + 940;
					tool_img.make_wry[i] = 650;
					tool.woodroad_add_Acount[i]++;
					break;
				}
				else if (i != 0 && tool.woodroad_add_Acount[i] == 0)
				{
					tool_img.make_wrx[i] = GetRand(400) % (980 - 940 + 1) + 940;
					tool_img.make_wry[i] = 650;
					tool.woodroad_add_Acount[i]++;
					break;
				}
				else
				{
					continue;
				}
			}
		}
	}
}

//木の道が増えた時の+1を描画する
void WoodRoad_Add_Animation(const Car*car)
{
	if (tool_start == true && car->direction != eStop && car->goal_flag == false)
	{
		for (int i = 0; i < 6; i++)
		{

			if (tool.woodroad_add_Acount[i] > 69)
			{
				tool.woodroad_add_Acount[i] = 0;
				continue;
			}
			if (tool.woodroad_add_Acount[i] > 0)
			{
				tool_img.makeWR_Anum[i] = tool.woodroad_add_Acount[i] / 10;
				DrawRotaGraph(tool_img.make_wrx[i], tool_img.make_wry[i] - tool.woodroad_add_Acount[i], 0.8, 0.0, tool_img.make_animation[tool_img.makeWR_Anum[i]], TRUE);
				tool.woodroad_add_Acount[i]++;
			}
		}
	}
}

//道の所持数を増やした後にフラグを戻す
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

//木と岩の所持数を増やした後にフラグを戻す
void Add_Road_Num(void)
{
	//岩の所持数をプラス1するフラグを元に戻す
	if (tool.rock_add_flag == true)
	{
		tool.rock_add_flag = false;
	}
	//木の所持数をプラス1するフラグを元に戻す
	if (tool.wood_add_flag == true)
	{
		tool.wood_add_flag = false;
	}
}

//ステージ切り替え時の値リセット
void Tool_Reset(const CreateStage*stage,const InGame*ingame)
{
	tool.frameselect_x = ITEM_SELECT_BASE_X + 80 * 3;
	tool.frameselect_y = ITEM_SELECT_BASE_Y;
	tool.item_number = ePickaxe;
	tool.road_num = 0;
	tool.wood_road_num = 0;
	tool.menu_flag = false;
	tool.mitibiki_flag = false;
	tool.rock_sub_flag = false;
	tool.wood_sub_flag = false;
	tool.rock_add_flag = false;
	tool.wood_add_flag = false;
	tool.stage_number=ingame->stage_num;			//ステージ切り替えができるまで
	tool.put_road_fps = 0;
	tool_img.item_frame_ex_rate = 1.0;
	tool_img.pickaxe_ex_rate = 0.4;
	tool_img.ax_ex_rate = 0.8;
	tool_img.woodroad_ex_rate = 0.6;
	tool_img.road_ex_rate = 0.6;
	tool_img.road_num_ex_rate = 1.0;
	tool_img.woodroad_num_ex_rate = 1.0;
	for (int i = 0; i < 6; i++)
	{
		tool_img.make_rx[i] = 0;
		tool_img.make_ry[i] = 0;
		tool.road_add_Acount[i] = 0;
		tool_img.makeR_Anum[i] = 0;
		tool_img.make_wrx[i] = 0;
		tool_img.make_wry[i] = 0;
		tool.woodroad_add_Acount[i] = 0;
		tool_img.makeWR_Anum[i] = 0;
	}
	
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			tool.road_flag[i][j] = false;
			tool.wood_road_flag[i][j] = false;
			tool.old_base_array[i][j] = 0;
		}
	}
	Stage_Init(GetStage());
}

//道画像ハンドル初期化
void Road_Imghandle_Init(int x1,int y1,int x2,int y2,int x3,int y3)
{
	
	tool.road_img_array[x1][y1] = tool_img.road_beside;
	tool.road_img_array[x2][y2] = tool_img.road_beside;
	tool.road_img_array[x3][y3] = tool_img.road_beside;
}

//ステージごとの基準初期化
void Stage_Init(const CreateStage*stage)
{
	switch (tool.stage_number)
	{
	case eOne:
		tool.base_x = 3;
		tool.base_y = 4;
		tool.old_base_array[2][4] = 1;
		tool.old_base_array[1][4] = 2;
		tool.stage_array_exceed_x = 12;
		tool.stage_array_exceed_y = 7;
		Road_Imghandle_Init(3, 4, 2, 4, 1, 4);
		break;
	case eTwo:
		tool.base_x = 3;
		tool.base_y = 3;
		tool.old_base_array[2][3] = 1;
		tool.old_base_array[1][3] = 2;
		tool.stage_array_exceed_x = 12;
		tool.stage_array_exceed_y = 7;
		Road_Imghandle_Init(3, 3, 2, 3, 1, 3);
		break;
	case eThree:
		tool.base_x = 3;
		tool.base_y = 3;
		tool.old_base_array[2][3] = 1;
		tool.old_base_array[1][3] = 2;
		tool.stage_array_exceed_x = 12;
		tool.stage_array_exceed_y = 7;
		Road_Imghandle_Init(3, 3, 2, 3, 1, 3);
		break;
	case eFour:
		tool.base_x = 2;
		tool.base_y = 0;
		tool.old_base_array[1][0] = 1;
		tool.old_base_array[0][0] = 2;
		tool.stage_array_exceed_x = 12;
		tool.stage_array_exceed_y = 7;
		Road_Imghandle_Init(2, 0, 1, 0, 0, 0);
		break;
	case eFive:
		tool.base_x = 3;
		tool.base_y = 3;
		tool.old_base_array[2][3] = 1;
		tool.old_base_array[1][3] = 2;
		tool.stage_array_exceed_x = 12;
		tool.stage_array_exceed_y = 7;
		Road_Imghandle_Init(3, 3, 2, 3, 1, 3);
		break;
	case eSix:
		tool.base_x = 2;
		tool.base_y = 6;
		tool.old_base_array[1][6] = 1;
		tool.old_base_array[2][6] = 2;
		tool.stage_array_exceed_x = 12;
		tool.stage_array_exceed_y = 7;
		Road_Imghandle_Init(0, 6, 1, 6, 2, 6);
		break;
	}
	
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			tool.stage_begin_array[i][j] = stage->array[i][j];
		}
	}
}

//道の配列の基準変更
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
	Search_Old_Position();
	Now_Base_State(GetStage());
	switch (tool.old_position_direction)
	{
		//**********前に置いた位置が左**********//
	case eLP:
		Old_Position_Left(GetStage());
		break;
		//**************************************//



		//**********前に置いた位置が右**********//
	case eRP:
		Old_Position_Right(GetStage());
		break;
		//**************************************//



		//**********前に置いた位置が上**********//
	case eTP:
		Old_Position_Top(GetStage());
		break;
		//**************************************//



		//**********前に置いた位置が下**********//
	case eBP:
		Old_Position_Bottom(GetStage());
		break;
		//**************************************//
	}
		
}

//前置いたところがどの方向か
void Search_Old_Position(void)
{
	if (tool.base_x - 1 > ARRAY_BELOW_LIMIT_X && tool.old_base_array[tool.base_x - 1][tool.base_y] == 1)
	{
		tool.old_position_direction = eLP;
	}
	else if (tool.base_x + 1 < ARRAY_EXCEED_LIMIT_X && tool.old_base_array[tool.base_x + 1][tool.base_y] == 1)
	{
		tool.old_position_direction = eRP;
	}
	else if (tool.base_y - 1 > ARRAY_BELOW_LIMIT_Y && tool.old_base_array[tool.base_x][tool.base_y - 1] == 1)
	{
		tool.old_position_direction = eTP;
	}
	else if (tool.base_y + 1 < ARRAY_EXCEED_LIMIT_Y && tool.old_base_array[tool.base_x][tool.base_y + 1] == 1)
	{
		tool.old_position_direction = eBP;
	}
}

//今の位置が道か木の道か
void Now_Base_State(const CreateStage*stage)
{
	if (stage->array[tool.base_x][tool.base_y] == 0)
	{
		tool.now_base_state = eBlank;
	}
	else if (stage->array[tool.base_x][tool.base_y] == 6)
	{
		tool.now_base_state = eLake;
	}
}

//前の位置が左の処理
void Old_Position_Left(const CreateStage* stage)
{
	switch (tool.now_base_state)
	{
	/***********************************************************************************************************/
	case eBlank:			//今の位置が空白

		//ゴールが上
		if (Check_Outside_Array2(tool.base_x, tool.base_y - 1, GetStage(), 7))
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Rtop;
			if (stage->array[tool.base_x - 1][tool.base_y] == 4)
			{
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.road_beside;
			}
			else
			{
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.wood_road_beside;
			}
		}
		//ゴールが下
		else if (Check_Outside_Array2(tool.base_x, tool.base_y + 1, GetStage(), 7))
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Rbottom;
			if (stage->array[tool.base_x - 1][tool.base_y] == 4)
			{
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.road_beside;
			}
			else
			{
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.wood_road_beside;
			}
		}
		//左だけ
		else
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_beside;
			if (stage->array[tool.base_x - 1][tool.base_y] == 4)
			{
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.road_beside;
			}
			else
			{
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.wood_road_beside;
			}
		}

		//二つ前左上
		if (Check_Outside_Array(tool.base_x - 1, tool.base_y - 1, 2))
		{
			if (stage->array[tool.base_x - 1][tool.base_y] == 4)
			{
				//前に置いた道の画像ハンドル変更(下右
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.road_Btmright;
			}
			else
			{
				//前に置いた道の画像ハンドル変更(下右
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.wood_road_Btmright;
			}
		}
		//二つ前左下
		else if (Check_Outside_Array(tool.base_x - 1, tool.base_y + 1, 2))
		{
			if (stage->array[tool.base_x - 1][tool.base_y] == 4)
			{
				//前に置いた道の画像ハンドル変更(上右
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.road_Topright;
			}
			else
			{
				//前に置いた道の画像ハンドル変更(上右
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.wood_road_Topright;
			}
		}
		break;
	/***********************************************************************************************************/



	/***********************************************************************************************************/
	case eLake:			//今の位置が湖
		
		//ゴールが上
		if (Check_Outside_Array2(tool.base_x, tool.base_y - 1, GetStage(), 7))
		{
			
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.wood_road_Rtop;
			if (stage->array[tool.base_x - 1][tool.base_y] == 4)
			{
				
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.road_beside;
			}
			else
			{
				
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.wood_road_beside;
			}
		}
		//ゴールが下
		else if (Check_Outside_Array2(tool.base_x, tool.base_y + 1, GetStage(), 7))
		{

			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.wood_road_Rbottom;
			if (stage->array[tool.base_x - 1][tool.base_y] == 4)
			{
				
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.road_beside;
			}
			else
			{
				
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.wood_road_beside;
			}
		}
		//左だけ
		else
		{	
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.wood_road_beside;
			if (stage->array[tool.base_x - 1][tool.base_y] == 4)
			{
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.road_beside;
			}
			else
			{
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.wood_road_beside;
			}
		}

		//二つ前左上
		if (Check_Outside_Array(tool.base_x - 1, tool.base_y - 1, 2))
		{
			if (stage->array[tool.base_x - 1][tool.base_y] == 4)
			{
				
				//前に置いた道の画像ハンドル変更(下右
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.road_Btmright;
			}
			else
			{
				
				//前に置いた道の画像ハンドル変更(下右
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.wood_road_Btmright;
			}
		}
		//二つ前左下
		else if (Check_Outside_Array(tool.base_x - 1, tool.base_y + 1, 2))
		{
			if (stage->array[tool.base_x - 1][tool.base_y] == 4)
			{
				
				//前に置いた道の画像ハンドル変更(上右
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.road_Topright;
			}
			else
			{
				
				//前に置いた道の画像ハンドル変更(上右
				tool.road_img_array[tool.base_x - 1][tool.base_y] = tool_img.wood_road_Topright;
			}
		}
		break;
	/***********************************************************************************************************/
	}
}

//前の位置が右の処理
void Old_Position_Right(const CreateStage* stage)
{
	switch (tool.now_base_state)
	{
	/***********************************************************************************************************/
	case eBlank:			//今の位置が空白

		//ゴールが上
		if (Check_Outside_Array2(tool.base_x, tool.base_y - 1, GetStage(), 7))
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Btmright;
			if (stage->array[tool.base_x + 1][tool.base_y] == 4)
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.road_beside;
			}
			else
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.wood_road_beside;
			}
		}
		//ゴールが下
		else if (Check_Outside_Array2(tool.base_x, tool.base_y + 1, GetStage(), 7))
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Topright;
			if (stage->array[tool.base_x + 1][tool.base_y] == 4)
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.road_beside;
			}
			else
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.wood_road_beside;
			}
		}
		//右だけ
		else
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_beside;
			if (stage->array[tool.base_x + 1][tool.base_y] == 4)
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.road_beside;
			}
			else
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.wood_road_beside;
			}
		}

		//二つ前右上
		if (Check_Outside_Array(tool.base_x + 1, tool.base_y - 1, 2))
		{
			if (stage->array[tool.base_x + 1][tool.base_y] == 4)
			{
				//前に置いた道の画像ハンドル変更(右上
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.road_Rtop;
			}
			else
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.wood_road_Rtop;
			}
		}
		//二つ前右下
		else if (Check_Outside_Array(tool.base_x + 1, tool.base_y + 1, 2))
		{
			if (stage->array[tool.base_x + 1][tool.base_y] == 4)
			{
				//前に置いた道の画像ハンドル変更(右下
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.road_Rbottom;
			}
			else
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.wood_road_Rbottom;
			}
		}
		break;
	/***********************************************************************************************************/



	/***********************************************************************************************************/
	case eLake:				//今の位置が湖

		//ゴールが上
		if (Check_Outside_Array2(tool.base_x, tool.base_y - 1, GetStage(), 7))
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.wood_road_Btmright;
			if (stage->array[tool.base_x + 1][tool.base_y] == 4)
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.road_beside;
			}
			else
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.wood_road_beside;
			}
		}
		//ゴールが下
		else if (Check_Outside_Array2(tool.base_x, tool.base_y + 1, GetStage(), 7))
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.wood_road_Topright;
			if (stage->array[tool.base_x + 1][tool.base_y] == 4)
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.road_beside;
			}
			else
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.wood_road_beside;
			}
		}
		//右だけ
		else
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.wood_road_beside;
			if (stage->array[tool.base_x + 1][tool.base_y] == 4)
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.road_beside;
			}
			else
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.wood_road_beside;
			}
		}

		//二つ前右上
		if (Check_Outside_Array(tool.base_x + 1, tool.base_y - 1, 2))
		{
			if (stage->array[tool.base_x + 1][tool.base_y] == 4)
			{
				//前に置いた道の画像ハンドル変更(右上
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.road_Rtop;
			}
			else
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.wood_road_Rtop;
			}
		}
		//二つ前右下
		else if (Check_Outside_Array(tool.base_x + 1, tool.base_y + 1, 2))
		{
			if (stage->array[tool.base_x + 1][tool.base_y] == 4)
			{
				//前に置いた道の画像ハンドル変更(右下
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.road_Rbottom;
			}
			else
			{
				tool.road_img_array[tool.base_x + 1][tool.base_y] = tool_img.wood_road_Rbottom;
			}
		}
		break;
	/***********************************************************************************************************/
	}
}

//前の位置が上の処理
void Old_Position_Top(const CreateStage* stage)
{
	switch (tool.now_base_state)
	{
	/***********************************************************************************************************/
	case eBlank:			//今の位置が空白

		if (Check_Outside_Array2(tool.base_x+1, tool.base_y, GetStage(), 7))
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Btmright;
			if (stage->array[tool.base_x][tool.base_y - 1] == 4)
			{
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.road_vertical;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.wood_road_vertical;
			}
		}
		//ゴールが左
		else if (Check_Outside_Array2(tool.base_x-1, tool.base_y, GetStage(), 7))
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Rtop;
			if (stage->array[tool.base_x][tool.base_y - 1] == 4)
			{
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.road_vertical;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.wood_road_vertical;
			}
		}
		//上だけ
		else
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_vertical;
			if (stage->array[tool.base_x][tool.base_y - 1] == 4)
			{
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.road_vertical;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.wood_road_vertical;
			}
		}

		//二つ前左上
		if (Check_Outside_Array(tool.base_x - 1, tool.base_y - 1, 2))
		{
			if (stage->array[tool.base_x][tool.base_y - 1] == 4)
			{
				//前に置いた道の画像ハンドル変更(右下
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.road_Rbottom;
			}
			else
			{
				//前に置いた道の画像ハンドル変更(右下
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.wood_road_Rbottom;
			}
		}
		//二つ前右上
		else if (Check_Outside_Array(tool.base_x + 1, tool.base_y - 1, 2))
		{
			if (stage->array[tool.base_x][tool.base_y - 1] == 4)
			{
				//前に置いた道の画像ハンドル変更(上右
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.road_Topright;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.wood_road_Topright;
			}
		}
		break;
	/***********************************************************************************************************/


	/***********************************************************************************************************/
	case eLake:				//今の位置が湖
		if (Check_Outside_Array2(tool.base_x + 1, tool.base_y, GetStage(), 7))
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.wood_road_Btmright;
			if (stage->array[tool.base_x][tool.base_y - 1] == 4)
			{
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.road_vertical;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.wood_road_vertical;
			}
		}
		//ゴールが左
		else if (Check_Outside_Array2(tool.base_x-1, tool.base_y, GetStage(), 7))
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.wood_road_Rtop;
			if (stage->array[tool.base_x][tool.base_y - 1] == 4)
			{
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.road_vertical;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.wood_road_vertical;
			}
		}
		//上だけ
		else
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.wood_road_vertical;
			if (stage->array[tool.base_x][tool.base_y - 1] == 4)
			{
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.road_vertical;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.wood_road_vertical;
			}
		}

		//二つ前左上
		if (Check_Outside_Array(tool.base_x - 1, tool.base_y - 1, 2))
		{
			if (stage->array[tool.base_x][tool.base_y - 1] == 4)
			{
				//前に置いた道の画像ハンドル変更(右下
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.road_Rbottom;
			}
			else
			{
				//前に置いた道の画像ハンドル変更(右下
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.wood_road_Rbottom;
			}
		}
		//二つ前右上
		else if (Check_Outside_Array(tool.base_x + 1, tool.base_y - 1, 2))
		{
			if (stage->array[tool.base_x][tool.base_y - 1] == 4)
			{
				//前に置いた道の画像ハンドル変更(上右
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.road_Topright;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y - 1] = tool_img.wood_road_Topright;
			}
		}
		break;
	/***********************************************************************************************************/
	}
}

//前の位置が下の処理
void Old_Position_Bottom(const CreateStage* stage)
{
	switch (tool.now_base_state)
	{
		/***********************************************************************************************************/
	case eBlank:			//今の位置が空白

		if (Check_Outside_Array2(tool.base_x+1, tool.base_y, GetStage(), 7))
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Topright;
			if (stage->array[tool.base_x][tool.base_y + 1] == 4)
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.road_vertical;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.wood_road_vertical;
			}
		}
		//ゴールが左
		else if (Check_Outside_Array2(tool.base_x-1, tool.base_y, GetStage(), 7))
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_Rbottom;
			if (stage->array[tool.base_x][tool.base_y + 1] == 4)
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.road_vertical;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.wood_road_vertical;
			}
		}
		//下だけ
		else
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.road_vertical;
			if (stage->array[tool.base_x][tool.base_y + 1] == 4)
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.road_vertical;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.wood_road_vertical;
			}
		}

		//二つ前左下
		if (Check_Outside_Array(tool.base_x - 1, tool.base_y + 1, 2))
		{
			if (stage->array[tool.base_x][tool.base_y + 1] == 4)
			{
				//前に置いた道の画像ハンドル変更(右上
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.road_Rtop;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.wood_road_Rtop;
			}
		}
		//二つ前右下
		else if (Check_Outside_Array(tool.base_x + 1, tool.base_y + 1, 2))
		{
			if (stage->array[tool.base_x][tool.base_y + 1] == 4)
				//前に置いた道の画像ハンドル変更(下右
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.road_Btmright;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.wood_road_Btmright;
			}
		}
		break;
		/***********************************************************************************************************/

		/***********************************************************************************************************/
	case eLake:				//今の位置が湖

		if (Check_Outside_Array2(tool.base_x+1, tool.base_y, GetStage(), 7))
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.wood_road_Topright;
			if (stage->array[tool.base_x][tool.base_y + 1] == 4)
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.road_vertical;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.wood_road_vertical;
			}
		}
		//ゴールが左
		else if (Check_Outside_Array2(tool.base_x-1, tool.base_y, GetStage(), 7))
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.wood_road_Rbottom;
			if (stage->array[tool.base_x][tool.base_y + 1] == 4)
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.road_vertical;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.wood_road_vertical;
			}
		}
		//下だけ
		else
		{
			tool.road_img_array[tool.base_x][tool.base_y] = tool_img.wood_road_vertical;
			if (stage->array[tool.base_x][tool.base_y + 1] == 4)
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.road_vertical;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.wood_road_vertical;
			}
		}

		//二つ前左下
		if (Check_Outside_Array(tool.base_x - 1, tool.base_y + 1, 2))
		{
			if (stage->array[tool.base_x][tool.base_y + 1] == 4)
			{
				//前に置いた道の画像ハンドル変更(右上
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.road_Rtop;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.wood_road_Rtop;
			}
		}
		//二つ前右下
		else if (Check_Outside_Array(tool.base_x + 1, tool.base_y + 1, 2))
		{
			if (stage->array[tool.base_x][tool.base_y + 1] == 4)
			{
				//前に置いた道の画像ハンドル変更(下右
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.road_Btmright;
			}
			else
			{
				tool.road_img_array[tool.base_x][tool.base_y + 1] = tool_img.wood_road_Btmright;
			}
		}
		break;
		/***********************************************************************************************************/
	}
}

//配列の外を見ないように(二つ前描画
bool Check_Outside_Array(int x, int y, int val)
{
	return x < ARRAY_EXCEED_LIMIT_X && x>ARRAY_BELOW_LIMIT_X &&
		y<ARRAY_EXCEED_LIMIT_Y && y > ARRAY_BELOW_LIMIT_Y &&
		tool.old_base_array[x][y] == val;
}

//配列の外を見ないように(ゴール前描画
bool Check_Outside_Array2(int x, int y, const CreateStage*stage, int val)
{
	return x < ARRAY_EXCEED_LIMIT_X && x>ARRAY_BELOW_LIMIT_X &&
		y<ARRAY_EXCEED_LIMIT_Y && y > ARRAY_BELOW_LIMIT_Y &&
		stage->array[x][y] == val;
}

//道の設置可能位置
void Possible_Prace(const CreateStage* stage,const Car*car)

{
	//ゴールではないなら
	if (car->goal_flag==false)
	{
		//アイテムが道なら
		if (tool.item_number == 0 && car->direction != eStop)
		{
			//道を一個以上持っているなら
			if (tool.road_num > 0)
			{
				if (tool.possible_fps < 75)
				{
					//右が空
					if (tool.base_x + 1 < tool.stage_array_exceed_x && stage->array[tool.base_x + 1][tool.base_y] == 0)
					{
						DrawRotaGraphF(MAP_TROUT_LENGTH * (tool.base_x + 1) + 200, MAP_TROUT_LENGTH * tool.base_y + 120,
							1.0, 0.0, tool_img.possible_roadB, TRUE);
					}
					//左が空
					if (tool.base_x - 1 > tool.stage_array_below_x && stage->array[tool.base_x - 1][tool.base_y] == 0)
					{
						DrawRotaGraphF(MAP_TROUT_LENGTH * (tool.base_x - 1) + 200, MAP_TROUT_LENGTH * tool.base_y + 120,
							1.0, 0.0, tool_img.possible_roadB, TRUE);
					}
					//上が空
					if (tool.base_y - 1 > ARRAY_BELOW_LIMIT_Y && stage->array[tool.base_x][tool.base_y - 1] == 0)
					{
						DrawRotaGraphF(MAP_TROUT_LENGTH * tool.base_x + 200, MAP_TROUT_LENGTH * (tool.base_y - 1) + 120,
							1.0, 0.0, tool_img.possible_roadV, TRUE);
					}
					//下が空
					if (tool.base_y + 1 < ARRAY_EXCEED_LIMIT_Y && stage->array[tool.base_x][tool.base_y + 1] == 0)
					{
						DrawRotaGraphF(MAP_TROUT_LENGTH * tool.base_x + 200, MAP_TROUT_LENGTH * (tool.base_y + 1) + 120,
							1.0, 0.0, tool_img.possible_roadV, TRUE);
					}
				}
				tool.possible_fps++;
				//fps値リセット
				if (tool.possible_fps > 100)
				{
					tool.possible_fps = 0;
				}
			}
		}
		//アイテムが木の道なら
		else if (tool.item_number == 1 && car->direction != eStop)
		{
			//木の道を一個以上持っているなら
			if (tool.wood_road_num > 0)
			{
				if (tool.possible_fps < 75)
				{
					//右が湖
					if (tool.base_x + 1 < tool.stage_array_exceed_x && stage->array[tool.base_x + 1][tool.base_y] == 6)
					{
						DrawRotaGraphF(MAP_TROUT_LENGTH * (tool.base_x + 1) + 200, MAP_TROUT_LENGTH * tool.base_y + 120, 1.0, 0.0, tool_img.possible_wood_roadB, TRUE);
					}
					//左が湖
					if (tool.base_x - 1 > tool.stage_array_below_x && stage->array[tool.base_x - 1][tool.base_y] == 6)
					{
						DrawRotaGraphF(MAP_TROUT_LENGTH * (tool.base_x - 1) + 200, MAP_TROUT_LENGTH * tool.base_y + 120, 1.0, 0.0, tool_img.possible_wood_roadB, TRUE);
					}
					//上が湖
					if (tool.base_y - 1 > tool.stage_array_below_x && stage->array[tool.base_x][tool.base_y - 1] == 6)
					{
						DrawRotaGraphF(MAP_TROUT_LENGTH * tool.base_x + 200, MAP_TROUT_LENGTH * (tool.base_y - 1) + 120, 1.0, 0.0, tool_img.possible_wood_roadV, TRUE);
					}
					//下が湖
					if (tool.base_y + 1 < tool.stage_array_exceed_y && stage->array[tool.base_x][tool.base_y + 1] == 6)
					{
						DrawRotaGraphF(MAP_TROUT_LENGTH * tool.base_x + 200, MAP_TROUT_LENGTH * (tool.base_y + 1) + 120, 1.0, 0.0, tool_img.possible_wood_roadV, TRUE);
					}
				}
				tool.possible_fps++;
				//fps値リセット
				if (tool.possible_fps > 100)
				{
					tool.possible_fps = 0;
				}
			}
		}
	}
}

//道を置いた時のアニメーション
void Put_Road_Animation(int x,int y)
{
	tool.put_road_fps++;
	if (tool.put_road_fps < 6)
	{
		DrawRotaGraph(x * 80 + 200, y * 80 + 120, 0.8, 0.0, tool_img.put_road[0], TRUE);
	}
	else if (tool.put_road_fps < 10)
	{
		DrawRotaGraph(x * 80 + 200, y * 80 + 120, 1.4, 5*(3.14/180), tool_img.put_road[1], TRUE);
	}
	else if (tool.put_road_fps < 15)
	{
		DrawRotaGraph(x * 80 + 200, y * 80 + 120, 1.4, 10 * (3.14 / 180), tool_img.put_road[2], TRUE);
	}
	else
	{
		tool.put_road_fps = 0;
		tool.put_road_flag = false;
	}
}

//木の道を置いた時のアニメーション
void Put_WoodRoad_Animation(int x, int y)
{
	tool.put_woodroad_fps++;
	if (tool.put_woodroad_fps < 6)
	{
		DrawRotaGraph(x * 80 + 200, y * 80 + 120, 0.8, 0.0, tool_img.put_woodroad[0], TRUE);
	}
	else if (tool.put_woodroad_fps < 12)
	{
		DrawRotaGraph(x * 80 + 200, y * 80 + 120, 1.2, 0.0, tool_img.put_woodroad[1], TRUE);
	}
	else
	{
		tool.put_woodroad_fps = 0;
		tool.put_woodroad_flag = false;
	}
}

//SE再生(音の重なりあり
void Play_Sound_Tool(int sound,int volume)
{
	ChangeVolumeSoundMem(volume, sound);
	PlaySoundMem(sound, DX_PLAYTYPE_BACK);
}

//SE再生(音の重なりなし
void Play_Sound_Tool2(int sound,int volume)
{
	if (CheckSoundMem(sound) == 0)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);
		ChangeVolumeSoundMem(volume, sound);
	}
}