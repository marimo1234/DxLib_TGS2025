#include "Player.h"
#include "../Utility/InputManager.h"
#include "../System/System.h"
#include "DxLib.h"

#define		D_RUN_ANIM_MAX		(8)			//画像の分割数
#define		D_GROUND_POS		(550.0f)	//地面
#define		D_JUMP_POWER		(-20.0f)	//ジャンプの力の大きさ
#define     D_DEFAULT_SPEED		(5.0f)		//速さ

Player player;
int run_animation[D_RUN_ANIM_MAX];		//走る画像のハンドル
int animation_count;					//フレームカウント
int animation_num;						//フレームカウントの要素
int situation_count = 0;				//プレイヤーの状態
int Jump_SE;							//ジャンプSEのハンドル

void PlayerRun(void);
void PlayerJump(void);
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
	player.is_jump = TRUE;					//プレイヤーのジャンプの真偽
	player.situation = 0;					//プレイヤーの状態

	//走っているがぞうの読み込み
	LoadDivGraph("Resource/Images/spr_ninja_run.png", D_RUN_ANIM_MAX, D_RUN_ANIM_MAX, 1, 128, 128, run_animation);

	//seの読み込み
	Jump_SE = LoadSoundMem("Resource/SE/jump.mp3");

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
	//飛ぶ処理
	PlayerJump();
	//アニメーション制御
	PlayerAnimationControl();
}

//プレイヤーの描画
void PlayerDraw(void)
{
	DrawRotaGraphF(player.position.x, player.position.y, 2.0, 0.0, player.image, TRUE);
}

//構造体Player
const Player* GetPlayer(void)
{
	return &player;
}

//プレイヤーが走る速さ
void PlayerRun(void)
{
	//矢印→が押されたら
	if (GetKeyInputState(KEY_INPUT_RIGHT) == eHold)
	{
		//普通
		if (player.situation == 0)
		{
			player.velocity.x = D_DEFAULT_SPEED * 2.5f;
		}
		//アイテム効果
		else if (player.situation == 1)
		{
			player.velocity.x = D_DEFAULT_SPEED * 1.3f;
			situation_count++;
			if (situation_count >= 60)
			{
				player.situation = 0;
				situation_count = 0;
			}
		}
		//スライムに当立った時
		else if (player.situation == 2)
		{
			player.velocity.x = D_DEFAULT_SPEED * 5.0f;
			situation_count++;
			if (situation_count >= 600)
			{
				player.situation = 0;
				situation_count = 0;
			}
		}

	}
	else
		//普通
		if (player.situation == 0)
		{
			player.velocity.x = D_DEFAULT_SPEED;
		}
	//アイテム効果
		else if (player.situation == 1)
		{
			player.velocity.x = D_DEFAULT_SPEED * 0.3f;
			situation_count++;
			if (situation_count >= 60)
			{
				player.situation = 0;
				situation_count = 0;
			}
		}
	//スライムに当立った時
		else if (player.situation == 2)
		{
			player.velocity.x = D_DEFAULT_SPEED * 3.5f;
			situation_count++;
			if (situation_count >= 600)
			{
				player.situation = 0;
				situation_count = 0;
			}
		}
}


void PlayerJump(void)
{
	//疑似的な重力を付与する
	player.velocity.y += 1.0f;

	//SPACEキーが押されたら
	if (GetKeyInputState(KEY_INPUT_SPACE) == ePress)
	{
		//ジャンプ状態じゃなければ
		if (player.is_jump != TRUE)
		{
			//上方向に移動する
			PlaySoundMem(Jump_SE, DX_PLAYTYPE_BACK);
			player.is_jump = TRUE;
			player.velocity.y = D_JUMP_POWER;
		}
	}

	//プレイヤーの位置を移動分だけずらす
	player.position.y += player.velocity.y;

	//地面と接地しているか？
	if (player.position.y >= D_GROUND_POS)
	{
		//走る状態にする
		player.is_jump = FALSE;
		player.position.y = D_GROUND_POS;
		player.velocity.y = 0.0f;
	}
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

//プレイヤーがアイテムかスライムに当たっているのか
void HitAction_Player(int* index)
{
	if (*index == 0 || *index == 1)
	{
		player.situation = 1;
	}
	if (*index == 9)
	{
		player.situation = 2;
	}
}
