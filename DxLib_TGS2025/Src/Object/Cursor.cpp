﻿#include "Cursor.h"
#include "../Utility/InputManager.h"
#include"../Scene/InGame/InGameScene.h"
#include"../Utility/PadInputManager.h"
#include "../System/System.h"
#include "../Object/Map.h"
#include"../Object/Tool.h"
#include"../Object/WoodRock.h"
#include"../Object/Car.h"
#include"../Object/Goal.h"
#include "DxLib.h"

#define MOVE_ONE_SPACE (80.0f)

Cursor cursor;
int cursor_image;
int cursor_se;
int cursorstart;
int pickaxe_animation_num = 0, pickaxe_animation_count = 0, hammer_animation_count = 0;
int ax_anim_num = 0, ax_anim_count = 0, hammer_anim_num = 0, hammer_anim_count = 0;
int cursor_image1;
int cursor_ax;
int cursor_drill;
int cursor_road;
int cursor_hasi;
static bool is_animating_pickaxe = false;  // ピッケルのアニメーションフラグ
static bool is_animating_ax = false;       // 斧のアニメーションフラグ
static bool is_animating_drill = false;    // ドリルのアニメーションフラグ
static bool is_animating_Hammer = false;    // ハンマーのアニメーションフラグ

void CursorStart(const InGame* ingame, const Goal* goal, const GameOver* gameover, const Car* car);
void GetCarInitPosition(const Car* car);
void GetCursorStageNum(const InGame* ingame);
void CursolButtonMovement(const Tool* tool, const InGame* ingame, const Wood* wood, const Rock* rock);       // 十字キーの移動
void CursorRange_eOne(const InGame* ingame);
void Img_Num_Change(const CreateStage* stage,int map);


//カーソルの初期化
void CursorInit(void)
{
	//初期設定
	cursor.position.x = MOVE_ONE_SPACE * cursor.array_x + 200.0f;			    	//初期位置（Ｘ）
	cursor.position.y = MOVE_ONE_SPACE * cursor.array_y + 120.0f;				//初期位置（Ｙ）
	cursor.box_size.x = 64.0f;				//矩形の大きさ（Ｘ）
	cursor.box_size.y = 128.0f;				//矩形の大きさ（Ｙ）
	cursor.velocity.x = 0.0f;	            //プレイヤーの横移動	
	cursor.velocity.y = 0.0f;				//プレイヤーの縦移動
	cursor.img_count = 0;
	cursor.img_num = 0;
	cursorstart = false;
	cursor.menu_flag = false;
	cursor.operable_flag = false;
	cursor.anim_count = 0;
	cursor.anim_num = 0;
	

	//ステージごとの初期化とステージ番号の取得
	GetCursorStageNum(GetInGame());
	//カーソルの配列番号
	GetCarInitPosition(GetCar());
}

void CursorResourceInit(void)
{
	// カーソル画像の読み込み
	//cursor_image = LoadGraph("Resource/Images/cursor1.png");
	cursor.cursor_anim[0] = LoadGraph("Resource/Images/cursor_anim01.png");
	cursor.cursor_anim[1] = LoadGraph("Resource/Images/cursor_anim02.png");
	cursor.cursor_anim[2] = LoadGraph("Resource/Images/cursor_anim03.png");
	cursor.cursor_anim[3] = LoadGraph("Resource/Images/cursor_anim04.png");
	cursor.cursor_anim[4] = LoadGraph("Resource/Images/cursor_anim05.png");
	cursor.cursor_anim[5] = LoadGraph("Resource/Images/cursor_anim06.png");

	cursor_image1 = LoadGraph("Resource/Images/pickaxe.png");
	cursor_ax = LoadGraph("Resource/Images/ax2.0.png");
	cursor_drill = LoadGraph("Resource/Images/Drill.png");
	cursor_road = LoadGraph("Resource/Images/RoadVertical_cursol.png");
	cursor_hasi = LoadGraph("Resource/Images/Log_cursol.png");
	//カーソル音の読み込み
	cursor_se = LoadSoundMem("Resource/Sounds/cursor_move_se.mp3");

	LoadDivGraph("Resource/Images/impossible.png",6,6,1,160,160, cursor.impossible);
}
//カーソルの更新
void CursorUpdate(void)
{
	FPS_Reset();
	CursorStart(GetInGame(),GetGoal(),GetGameOver(),GetCar());
	
	
	if (cursorstart == true&& cursor.menu_flag == false&& cursor.operable_flag == true)
	{
        CursolButtonMovement(Get_Tool(),GetInGame(),GetWood(),GetRock());

		CursorAnimation(); //アニメーション進行

		// ツルハシのアニメーション
		if (is_animating_pickaxe)
		{
			pickaxe_animation_count++;

			if (pickaxe_animation_count % 14 == 0)
			{
				pickaxe_animation_num++;
				if (pickaxe_animation_num > 1)
				{
					is_animating_pickaxe = false;
					pickaxe_animation_num = 0;
					pickaxe_animation_count = 0;
				}
			}
		}
		// 斧のアニメーション
		if (is_animating_ax)
		{
			ax_anim_count++;
			if (ax_anim_count % 14 == 0)
			{
				ax_anim_num++;
				if (ax_anim_num > 1)
				{
					is_animating_ax = false;
					ax_anim_num = 0;
					ax_anim_count = 0;
				}
			}
		}
		// ハンマーのアニメーション
		if (is_animating_Hammer)
		{
			hammer_anim_count++;
			if (hammer_anim_count % 15 == 0)
			{
				hammer_anim_num++;
				if (hammer_anim_num > 1)
				{
					is_animating_Hammer = false;
					hammer_anim_num = 0;
					hammer_anim_count = 0;
				}
			}
		}
	}
	else if(cursorstart == false && cursor.menu_flag == false)
	{
		CursorReset();
	}
}

//カーソルの描画
void CursorDraw(const Tool*tool)
{
	DrawRotaGraphF(cursor.position.x, cursor.position.y, 1.0, 0.0, cursor.cursor_anim[cursor.anim_num], TRUE);// カーソルの描画
	
	// もしitem_numberがePickaxeなら
	if (tool->item_number == ePickaxe)
	{
		Img_Num_Change(GetStage(),1);

		// ツルハシのアニメーションを動かす
		if (is_animating_pickaxe)
		{
			if (pickaxe_animation_num == 0)
			{
				DrawRotaGraphF(cursor.position.x, cursor.position.y - 40.0, 0.3, 0.0, cursor_image1, TRUE);
			}
			else if (pickaxe_animation_num == 1)
			{
				DrawRotaGraphF(cursor.position.x, cursor.position.y - 40.0, 0.3, 30.0, cursor_image1, TRUE);
			}
		}
		// アニメーションが動いてなければcursor_image1にする
		else
		{
			DrawRotaGraphF(cursor.position.x, cursor.position.y - 40.0, 0.3, 0.0, cursor_image1, TRUE);
		}
	}
	// もしitem_numberがeAxなら
	else if (tool->item_number == eAx) 
	{
		Img_Num_Change(GetStage(),2);

		// 斧のアニメーションを動かす
		if (is_animating_ax)
		{
			if (ax_anim_num == 0)
			{
				DrawRotaGraphF(cursor.position.x, cursor.position.y - 40.0, 0.7, 0.0, cursor_ax, TRUE);
			}
			else if (ax_anim_num == 1)
			{
				DrawRotaGraphF(cursor.position.x, cursor.position.y - 40.0, 0.7, -90.0, cursor_ax, TRUE);
			}
		}
		// アニメーションが動いていなければcursor_axにする
		else
		{
			DrawRotaGraphF(cursor.position.x, cursor.position.y - 40.0, 0.7, 0.0, cursor_ax, TRUE);
		}
	}
	// もしitem_numberがeDrillなら
	else if(tool->item_number==eHammer)
	{
		// ハンマーのアニメーションを動かす
		if (is_animating_Hammer)
		{
			if (hammer_anim_num == 0)
			{
				DrawRotaGraphF(cursor.position.x, cursor.position.y - 40.0, 0.7, 0.0, cursor_drill, TRUE);
			}
			else if (hammer_anim_num == 1)
			{
				DrawRotaGraphF(cursor.position.x, cursor.position.y - 40.0, 0.7,-90.0, cursor_drill, TRUE);
			}
		}
		// アニメーションが動いていなければこれにする
		else
		{
			DrawRotaGraphF(cursor.position.x, cursor.position.y - 40.0, 0.7, 0.0, cursor_drill, TRUE);
		}
	}
	else if (tool->item_number == eRoad)
	{
		DrawRotaGraphF(cursor.position.x, cursor.position.y - 40.0f, 0.5, 0.0, cursor_road, TRUE);
		if (tool->road_num < 10)
		{
			DrawExtendFormatString(cursor.position.x - 10.0f, cursor.position.y - 60.0, 2.8, 2.5, GetColor(0, 0, 0), "%d",
				tool->road_num);
		}
		else if(tool->road_num>99)
		{
			DrawExtendFormatString(cursor.position.x - 25.0f, cursor.position.y - 60.0f, 2.8, 2.5, GetColor(0, 0, 0), "99+");
		}
		else
		{
			DrawExtendFormatString(cursor.position.x - 25.0f, cursor.position.y - 60.0, 2.8, 2.5, GetColor(0, 0, 0), "%d",
				tool->road_num);
		}
		cursor.img_count = 0;
	}
	else if (tool->item_number == eWoodRoad)
	{
		DrawRotaGraphF(cursor.position.x, cursor.position.y - 40.0f, 0.5, 0.0, cursor_hasi, TRUE);
		if (tool->wood_road_num < 10)
		{
			DrawExtendFormatString(cursor.position.x - 10.0f, cursor.position.y - 60.0f, 2.8, 2.5, GetColor(0, 0, 0), "%d",
				tool->wood_road_num);
		}
		else if(tool->wood_road_num > 99)
		{
			DrawExtendFormatString(cursor.position.x - 25.0f, cursor.position.y - 60.0f, 2.8, 2.5, GetColor(0, 0, 0), "99+");
		}
		else
		{
			DrawExtendFormatString(cursor.position.x - 25.0f, cursor.position.y - 60.0f, 2.8, 2.5, GetColor(0, 0, 0), "%d",
				tool->wood_road_num);
		}
		cursor.img_count = 0;
	}
}

void CursorStart(const InGame* ingame , const Goal*goal,const GameOver*gameover,const Car*car)
{
	if (ingame->start == true && ingame->menu_flag == false &&ingame->mitibiki_flag == false)
	{
		cursorstart = true;
		cursor.operable_flag = true;
	}
	else if (ingame->start == false && ingame->menu_flag == false)
	{
		cursorstart = false;
	}

	if (goal->print_flag == true || car->direction==eStop||ingame->mitibiki_flag==true
		|| gameover->image_flag == true||car->goal_flag==true)
	{
		cursor.operable_flag = false;
	}
	cursor.menu_flag = ingame->menu_flag;
}

//構造体Cursor
const Cursor* GetCursor1(void)
{
	return &cursor;
}

void CursolButtonMovement(const Tool* tool,const InGame*ingame,const Wood*wood,const Rock*rock)
{
	//ステージ1のカーソルの範囲設定
	CursorRange_eOne(GetInGame());

		PadInputManager* pad_input = PadInputManager::GetInstance();

		if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::ePress &&
			wood->fps[wood->count_x][wood->count_y] == 0 && rock->fps[rock->count_x][rock->count_y] == 0)
		{

			// 十字ボタンの左を押したとき
			if (cursor.array_x > cursor.array_x_min)
			{
				cursor.array_x--;
				cursor.position.x = MOVE_ONE_SPACE * cursor.array_x + 200.0f;

			}
			else if (cursor.array_x == cursor.array_x_min)
			{
				if (ingame->stage_num != eOne)
				{
					cursor.array_x = cursor.array_x_max;
					cursor.position.x = MOVE_ONE_SPACE * cursor.array_x + 200.0f;

				}
			}

			// 移動のSE（もし使うならここに入れてね）
			/*PlaySoundMem(cursor_se, DX_PLAYTYPE_BACK);*/
		}
		else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress &&
			wood->fps[wood->count_x][wood->count_y] == 0 && rock->fps[rock->count_x][rock->count_y] == 0)
		{
			// 十字ボタンの右を押したとき
			if (cursor.array_x < cursor.array_x_max)
			{
				cursor.array_x++;
				cursor.position.x = MOVE_ONE_SPACE * cursor.array_x+200.0f;
				
			}
			else if (cursor.array_x == cursor.array_x_max)
			{
				if (ingame->stage_num != eOne)
				{
					cursor.array_x = cursor.array_x_min;
					cursor.position.x = MOVE_ONE_SPACE * cursor.array_x + 200.0f;
				}
			}
			// 移動のSE（左とおんなじ音入れてね）
			/*PlaySoundMem(cursor_se, DX_PLAYTYPE_BACK);*/
		}
		else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress &&
			wood->fps[wood->count_x][wood->count_y] == 0 && rock->fps[rock->count_x][rock->count_y] == 0)
		{
			// 十字ボタンの上を押したとき
			if (cursor.array_y > cursor.array_y_min)
			{
				cursor.array_y--;
				cursor.position.y = MOVE_ONE_SPACE*cursor.array_y+120.0f;
				
			}
			else if (cursor.array_y == cursor.array_y_min)
			{
				cursor.array_y = cursor.array_y_max;
				cursor.position.y = MOVE_ONE_SPACE * cursor.array_y + 120.0f;
			}
			// 移動のSE（左とおんなじ音入れてね）
			/*PlaySoundMem(cursor_se, DX_PLAYTYPE_BACK);*/
		}
		else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress &&
			wood->fps[wood->count_x][wood->count_y] == 0 && rock->fps[rock->count_x][rock->count_y] == 0)
		{
			// 十字ボタンの下を押したとき
			if (cursor.array_y < cursor.array_y_max)
			{ 
				cursor.array_y++;
				cursor.position.y = MOVE_ONE_SPACE*cursor.array_y+120.0f;
				
			}
			else if (cursor.array_y == cursor.array_y_max)
			{
				cursor.array_y = cursor.array_y_min;
				cursor.position.y = MOVE_ONE_SPACE * cursor.array_y + 120.0f;
			}
			// 移動のSE（左とおんなじ音入れてね）
			/*PlaySoundMem(cursor_se, DX_PLAYTYPE_BACK);*/
		}
		// もしツルハシなら
		if (tool->item_number == ePickaxe)
		{
			if (!is_animating_pickaxe && pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
			{
				// アニメーション開始
				pickaxe_animation_num = 0;
				pickaxe_animation_count = 0;
				is_animating_pickaxe = true;
			}
		}
		// もし斧なら
		if (tool->item_number == eAx)
		{
			if (!is_animating_ax && pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
			{
				// アニメーション開始
				ax_anim_num = 0;
				ax_anim_count = 0;
				is_animating_ax = true;
			}
		}
		// もしハンマー
		if (tool->item_number == eHammer)
		{
			if (!is_animating_Hammer && pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
			{
				// アニメーション開始
				hammer_anim_num = 0;
				hammer_anim_count = 0;
				is_animating_Hammer = true;
			}
		}
}

void CursorReset(void)
{
	GetCarInitPosition(GetCar());      //カーソルの配列番号

	cursor.position.x = MOVE_ONE_SPACE*cursor.array_x+200.0f;			    	//初期位置（Ｘ）
	cursor.position.y = MOVE_ONE_SPACE * cursor.array_y + 120.0f;				//初期位置（Ｙ）
	cursor.box_size.x = 64.0f;				//矩形の大きさ（Ｘ）
	cursor.box_size.y = 128.0f;				//矩形の大きさ（Ｙ）
	cursor.velocity.x = 0.0f;	            //プレイヤーの横移動	
	cursor.velocity.y = 0.0f;				//プレイヤーの縦移動
	cursor.img_count = 0;
	cursorstart = false;
	cursor.menu_flag = false;
	cursor.operable_flag = false;

	GetCursorStageNum(GetInGame());
	
	
	static bool is_animating_pickaxe = false;  // ピッケルのアニメーションフラグ
	static bool is_animating_ax = false;       // 斧のアニメーションフラグ
	static bool is_animating_Hammer = false;   // ハンマーのアニメーションフラグ
}


void GetCarInitPosition(const Car* car)
{
	cursor.array_x = car->current_x;
	cursor.array_y = car->current_y;
}

void GetCursorStageNum(const InGame* ingame)
{
	switch (ingame->stage_num)
	{
	case eOne:
		cursor.array_x_min = 1;
		cursor.array_x_max = 8;
		cursor.array_y_min = 4;
		cursor.array_y_max = 5;
		break;
	default:
		cursor.array_x_min = 0;
		cursor.array_x_max = 11;
		cursor.array_y_min = 0;
		cursor.array_y_max = 6;
		break;
	}
}

void CursorRange_eOne(const InGame* ingame)
{
	if (ingame->stage_num == eOne)
	{
		if (cursor.array_x > 0 && cursor.array_x < 6)
		{
			cursor.array_y_max = 4;
		}
		else
		{
			cursor.array_y_max = 5;
		}

		if (cursor.array_y == 5)
		{
			cursor.array_x_min = 6;
		}
		else
		{
			cursor.array_x_min = 1;
		}
	}
}

//fpsのリセット
void FPS_Reset(void)
{
	cursor.img_num = cursor.img_count / 6;
	if (cursor.img_count > 108)
	{
		cursor.img_count = 0;
	}
}

//掘れないマークの画像変更
void Img_Num_Change(const CreateStage*stage,int map)
{
	//掘れないマーク表示
	if (stage->array[cursor.array_x][cursor.array_y] == map)
	{
		cursor.img_count++;
		switch (cursor.img_num)
		{
		case 0:
			DrawRotaGraphF(cursor.position.x, cursor.position.y, 0.5, 0.0, cursor.impossible[0], TRUE);
			break;
		case 1:case 18:
			DrawRotaGraphF(cursor.position.x, cursor.position.y, 0.5, 0.0, cursor.impossible[1], TRUE);
			break;
		case 2:case 17:
			DrawRotaGraphF(cursor.position.x, cursor.position.y, 0.5, 0.0, cursor.impossible[2], TRUE);
			break;
		case 3:case 16:
			DrawRotaGraphF(cursor.position.x, cursor.position.y, 0.5, 0.0, cursor.impossible[3], TRUE);
			break;
		case 4:case 15:
			DrawRotaGraphF(cursor.position.x, cursor.position.y, 0.5, 0.0, cursor.impossible[4], TRUE);
			break;
		case 5:case 14:
			DrawRotaGraphF(cursor.position.x, cursor.position.y, 0.5, 0.0, cursor.impossible[5], TRUE);
			break;
		case 6:case 13:
			DrawRotaGraphF(cursor.position.x, cursor.position.y, 0.5, 0.0, cursor.impossible[6], TRUE);
			break;
		case 7:case 12:
			DrawRotaGraphF(cursor.position.x, cursor.position.y, 0.5, 0.0, cursor.impossible[7], TRUE);
			break;
		case 8:case 11:
			DrawRotaGraphF(cursor.position.x, cursor.position.y, 0.5, 0.0, cursor.impossible[8], TRUE);
			break;
		case 9:case 10:
			DrawRotaGraphF(cursor.position.x, cursor.position.y, 0.5, 0.0, cursor.impossible[9], TRUE);
			break;
		default:
			break;
		}
	}
	else
	{
		cursor.img_count = 0;
	}
}

void CursorAnimation(void)
{
	cursor.anim_count++;
	if (cursor.anim_count % 15 == 0 )
	{
		cursor.anim_num++;
	}
	if ( cursor.anim_num > 3 )
	{
		cursor.anim_count = 0;
		cursor.anim_num = 0;
	}
}