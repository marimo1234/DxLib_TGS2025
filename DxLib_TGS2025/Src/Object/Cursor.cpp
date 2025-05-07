#include "Cursor.h"
#include "../Utility/InputManager.h"
#include"../Scene/InGame/InGameScene.h"
#include"../Utility/PadInputManager.h"
#include "../System/System.h"
#include "../Object/Map.h"
#include "DxLib.h"

#define CURSOR_ARRAY_X_MAX (11)
#define CURSOR_ARRAY_X_MIN (0)
#define CURSOR_ARRAY_Y_MAX (6)
#define CURSOR_ARRAY_Y_MIN (0)



//////////////////////////////////////
//颯馬が変えた内容
/*
　PlayerからCursorに名前全部変えた

　DrawGraphからDrawRotaGraphFに変えた
　DrawGraphは左上が（0，0)だけどDrawRotaGraphFは中心が（0.0）だから初期位置も変えた
 　　　　　　　　　　　　　　　　　　　　　 ↑座標の変数がFloat型だからF入ってる 
  
  GetCursorって名前の関数は開発者？が定義してるっぽいから
  GetCursor1って名前にしてる

*/
//////////////////////////////////////

Cursor cursor;
int cursor_image;
static int numx = 0;
static int numy = 0;
static int move_wait_time = 0;
int aif = 0;
int cursorstart;


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

	//アニメーションの設定
	//animation_count = 0;
	//animation_num = 0;

	//初期画像の設定
	//player.image = run_animation[animation_num];
}

//カーソルの更新
void CursorUpdate(void)
{
	CursolButtonMovement();
	CursorStart(GetInGame());
}

//カーソルの描画
void CursorDraw(void)
{
	DrawRotaGraphF(cursor.position.x, cursor.position.y,1.0,0.0 ,cursor_image, TRUE);
	DrawFormatString(100, 100, GetColor(255, 255, 255), "%d %d ",numx,numy );
	DrawFormatString(150, 150, GetColor(255, 255, 255), "%d %d ",cursor.array_x, cursor.array_y);
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

void CursolButtonMovement()
{

	


	if (cursorstart == TRUE)
	{
		PadInputManager* pad_input = PadInputManager::GetInstance();

		if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::ePress)
		{
			aif++;
			//// 十字ボタンの左を押したとき
			//if (numx > -1)
			//{
			//	// レーンを1つ左にする
			//	numx--;


			//	// 左移動
			//	cursor.velocity.x = -80.0f;

			//	// 移動のSE（もし使うならここに入れてね）

			//}

			if (cursor.array_x > CURSOR_ARRAY_X_MIN)
				{
			cursor.velocity.x = -80.0f;
			cursor.array_x--;
				}
		}
		else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
		{
			//// 十字ボタンの右を押したとき
			//if (numx < 1)
			//{
			//	// レーンを１つ右にする
			//	numx++;

			//	// 右移動
			//	cursor.velocity.x = 80.0f;

			//	// 移動のSE（左とおんなじ音入れてね）
			//}
			if (cursor.array_x < CURSOR_ARRAY_X_MAX)
			{
				cursor.velocity.x = 80.0f;
				cursor.array_x++;
			}
		}
		else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
		{
			/*if (numy < 1)
			{
				numy++;
				cursor.velocity.y = -80.0f;
			}*/
			if (cursor.array_y > CURSOR_ARRAY_Y_MIN)
			{
				cursor.velocity.y = -80.0f;
				cursor.array_y--;
			}
		}
		else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
		{
			/*if (numy > -1)
			{
				numy--;
				cursor.velocity.y = 80.0f;
			}*/
			if (cursor.array_y < CURSOR_ARRAY_Y_MAX)
			{
				cursor.velocity.y = 80.0f;
				cursor.array_y++;
			}
		}
		else
		{
			// 移動速度を0に戻す
			cursor.velocity.x = 0.0f;
			cursor.velocity.y = 0.0f;
		}
	}
	// カーソル移動
	cursor.position.x += cursor.velocity.x;
	cursor.position.y += cursor.velocity.y;


}

// カーソルがいるレーンを取得する


