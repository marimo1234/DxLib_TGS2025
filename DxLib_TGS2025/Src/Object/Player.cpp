#include "Player.h"
#include "../Utility/InputManager.h"
#include"../Utility/PadInputManager.h"
#include "../System/System.h"
#include "DxLib.h"

#define		D_RUN_ANIM_MAX		(8)			//画像の分割数
#define		D_GROUND_POS		(550.0f)	//地面
#define     D_DEFAULT_SPEED		(5.0f)		//速さ

Player player;
int run_animation[D_RUN_ANIM_MAX];		//走る画像のハンドル
int animation_count;					//フレームカウント
int animation_num;						//フレームカウントの要素
int situation_count = 0;				//プレイヤーの状態

void PlayerRun(void);
void PlayerAnimationControl(void);

//プレイヤーの初期化
void PlayerInit(void)
{
	//初期設定
	player = {};
	player.position.x = 120.0f;				//初期位置（Ｘ）
	player.position.y = 490.0f;				//初期位置（Ｙ）
	player.box_size.x = 64.0f;				//矩形の大きさ（Ｘ）
	player.box_size.y = 128.0f;				//矩形の大きさ（Ｙ）
	player.velocity.x = D_DEFAULT_SPEED;	//プレイヤーの横移動	
	player.velocity.y = 0.0f;				//プレイヤーの縦移動

	// カーソルがぞうの読み込み
	LoadDivGraph("Resource/Images/cursol.png", D_RUN_ANIM_MAX, D_RUN_ANIM_MAX, 1, 128, 128, run_animation);

	//アニメーションの設定
	animation_count = 0;
	animation_num = 0;

	//初期画像の設定
	player.image = run_animation[animation_num];
}

//プレイヤーの更新
void PlayerUpdate(void)
{
	//走る処理
	PlayerRun();
	//アニメーション制御
	PlayerAnimationControl();
}

//プレイヤーの描画
void PlayerDraw(void)
{
	
}

//構造体Player
const Player* GetPlayer(void)
{
	return &player;
}

//プレイヤーが走る速さ
void PlayerRun(void)
{
	
}




//画像の切り替えの制御
void PlayerAnimationControl(void)
{
	animation_count++;
	//5フレーム経過したか
	if (animation_count > 5)
	{
		//次の画像番号を設定
		animation_count = 0;
		animation_num = ++animation_num % D_RUN_ANIM_MAX;
	}

	//描画画像を指定する
	player.image = run_animation[animation_num];
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



		}
	}
}
