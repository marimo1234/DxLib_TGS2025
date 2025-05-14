#include "Cursor.h"
#include "../Utility/InputManager.h"
#include"../Scene/InGame/InGameScene.h"
#include"../Utility/PadInputManager.h"
#include "../System/System.h"
#include "../Object/Map.h"
#include"../Object/Tool.h"
#include "DxLib.h"

#define CURSOR_ARRAY_X_MAX (11)
#define CURSOR_ARRAY_X_MIN (0)
#define CURSOR_ARRAY_Y_MAX (6)
#define CURSOR_ARRAY_Y_MIN (0)
#define MOVE_ONE_SPACE (80.0f)

Cursor cursor;
int cursor_image;
static int numx = 0;
static int numy = 0;
static int move_wait_time = 0;
int aif = 0;
int cursorstart;
int pickaxe_animation_num = 0, pickaxe_animation_count = 0;
int ax_anim_num = 0, ax_anim_count = 0;
int cursor_image1, cursor_image2;
int cursor_ax;
static bool is_animating_pickaxe = false;  // ピッケルのアニメーションフラグ
static bool is_animating_ax = false;       // 斧のアニメーションフラグ

void CursorStart(const InGame* ingame);


//カーソルの初期化
void CursorInit(void)
{
	//初期設定
	cursor_image = {};
	cursor.position.x = 200.0f;				//初期位置（Ｘ）
	cursor.position.y = 120.0f;				//初期位置（Ｙ）
	cursor.box_size.x = 64.0f;				//矩形の大きさ（Ｘ）
	cursor.box_size.y = 128.0f;				//矩形の大きさ（Ｙ）
	cursor.velocity.x = 0.0f;	            //プレイヤーの横移動	
	cursor.velocity.y = 0.0f;				//プレイヤーの縦移動
	cursorstart = false;

	//これで当たり判定作ってみる
	cursor.array_x = 0;
	cursor.array_y = 0;

	// カーソルがぞうの読み込み
	cursor_image = LoadGraph("Resource/Images/cursol.png");
	cursor_image1 = LoadGraph("Resource/Images/pickaxe1.png");
	cursor_image2 = LoadGraph("Resource/Images/pickaxe2.png");
	cursor_ax = LoadGraph("Resource/Images/ax.png");
}

//カーソルの更新
void CursorUpdate(void)
{
	CursolButtonMovement(Get_Tool());
	CursorStart(GetInGame());
	// ツルハシのアニメーション
	if (is_animating_pickaxe)
	{
		pickaxe_animation_count++;

		if (pickaxe_animation_count % 15 == 0)
		{
			pickaxe_animation_num++;
			if (pickaxe_animation_num > 2)
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
		if (ax_anim_count % 15 == 0)
		{
			ax_anim_num++;
			if (ax_anim_num > 2)
			{
				is_animating_ax = false;
				ax_anim_num = 0;
				ax_anim_count = 0;
			}
		}
	}
}

//カーソルの描画
void CursorDraw(const Tool*tool)
{

	DrawRotaGraphF(cursor.position.x, cursor.position.y,1.0,0.0 ,cursor_image, TRUE);// カーソルの描画
	DrawFormatString(100, 100, GetColor(255, 255, 255), "%d %d ",numx,numy );
	DrawFormatString(150, 150, GetColor(255, 255, 255), "%d %d ",cursor.array_x, cursor.array_y);
	if (tool->item_number == ePickaxe && is_animating_pickaxe) 
	{
		if (pickaxe_animation_num == 0)
		{
			DrawRotaGraphF(cursor.position.x, cursor.position.y - 40.0, 0.5, 0.0, cursor_image1, TRUE);
		}
		else if (pickaxe_animation_num == 1)
		{
			DrawRotaGraphF(cursor.position.x, cursor.position.y - 40.0, 0.5, 0.0, cursor_image2, TRUE);
		}
	}
	else if (tool->item_number == eAx && is_animating_ax) 
	{
		if (ax_anim_num == 0)
		{
			DrawRotaGraphF(cursor.position.x, cursor.position.y - 40.0, 0.5, 0.0, cursor_ax, TRUE);
		}
		else if (ax_anim_num == 1)
		{
			DrawRotaGraphF(cursor.position.x, cursor.position.y - 40.0, 0.5, 0.0, cursor_ax, TRUE);
		}
	}

}

void CursorStart(const InGame* ingame)
{
	if (ingame->start == true)
	{
		cursorstart = true;
	}
}

//構造体Cursor
const Cursor* GetCursor1(void)
{
	return &cursor;
}

void CursolButtonMovement(const Tool* tool)
{
	if (cursorstart == TRUE)
	{
		PadInputManager* pad_input = PadInputManager::GetInstance();

		if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::ePress)
		{
			aif++;
			// 十字ボタンの左を押したとき
			if (cursor.array_x > CURSOR_ARRAY_X_MIN)
			{
				cursor.position.x += -MOVE_ONE_SPACE;
				cursor.array_x--;
			}

			// 移動のSE（もし使うならここに入れてね）
		}
		else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
		{
			// 十字ボタンの右を押したとき
			if (cursor.array_x < CURSOR_ARRAY_X_MAX)
			{
				cursor.position.x += MOVE_ONE_SPACE;
				cursor.array_x++;
			}
			// 移動のSE（左とおんなじ音入れてね）
		}
		else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
		{
			// 十字ボタンの上を押したとき
			if (cursor.array_y > CURSOR_ARRAY_Y_MIN)
			{
				cursor.position.y += -MOVE_ONE_SPACE;
				cursor.array_y--;
			}
			// 移動のSE（左とおんなじ音入れてね）
		}
		else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
		{
			// 十字ボタンの下を押したとき
			if (cursor.array_y < CURSOR_ARRAY_Y_MAX)
			{
				cursor.position.y += MOVE_ONE_SPACE;
				cursor.array_y++;
			}
			// 移動のSE（左とおんなじ音入れてね）
		}
		// もしツルハシなら
		if (tool->item_number == ePickaxe)
		{
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
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
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
			{
				// アニメーション開始
				ax_anim_num = 0;
				ax_anim_count = 0;
				is_animating_ax = true;
			}
		}
	}
}