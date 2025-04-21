#include "Player.h"
#include "../Utility/InputManager.h"
#include"../Utility/PadInputManager.h"
#include "../System/System.h"
#include "DxLib.h"



Player player;
int cursol;
static int move_lane_num = 1;
static int move_wait_time = 0;
int aif = 0;

void PlayerAnimationControl(void);

//プレイヤーの初期化
void PlayerInit(void)
{
	//初期設定
	player = {};
	player.position.x = 575.0f;				//初期位置（Ｘ）
	player.position.y = 340.0f;				//初期位置（Ｙ）
	player.box_size.x = 64.0f;				//矩形の大きさ（Ｘ）
	player.box_size.y = 128.0f;				//矩形の大きさ（Ｙ）
	player.velocity.x = 0.0f;	            //プレイヤーの横移動	
	player.velocity.y = 0.0f;				//プレイヤーの縦移動

	// カーソルがぞうの読み込み
	cursol = LoadGraph("Resource/Images/cursol.png");

	//アニメーションの設定
	//animation_count = 0;
	//animation_num = 0;

	//初期画像の設定
	//player.image = run_animation[animation_num];
}

//プレイヤーの更新
void PlayerUpdate(void)
{
	CursolButtonMovement();

}

//プレイヤーの描画
void PlayerDraw(void)
{
	DrawGraph(player.position.x, player.position.y, cursol, TRUE);
	DrawFormatString(100, 100, GetColor(255, 255, 255), "%d", aif);
}

//構造体Player
const Player* GetPlayer(void)
{
	return &player;
}

void CursolButtonMovement()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

  	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::ePress)
	{
		// 十字ボタンの左を押したとき
		if (move_lane_num > 0)
		{
			// レーンを1つ左にする
			move_lane_num--;

			aif++;
			// 左移動
			player.velocity.x = -75.0f;

			// 移動のSE（もし使うならここに入れてね）
			
		}
	}
	else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
	{
		// 十字ボタンの右を押したとき
		if (move_lane_num < 3)
		{
			// レーンを１つ右にする
			move_lane_num++;

			// 右移動
			player.velocity.x = 75.0f;

			// 移動のSE（左とおんなじ音入れてね）
		}
	}
	else
	{
		// 移動速度を0に戻す
		player.velocity.x = 0.0f;
	}

	// プレイヤー移動
	player.position.x += player.velocity.x;
}

// プレイヤーがいるレーンを取得する


