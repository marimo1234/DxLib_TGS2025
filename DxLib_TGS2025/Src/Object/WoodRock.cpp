#include "DxLib.h"
#include "WoodRock.h"
#include "../Utility/InputManager.h"
#include"../Utility/PadInputManager.h"
#include "../Object/Tool.h"
#include "../Object/Cursor.h"
#include"../Scene/InGame/InGameScene.h"


int woodrock_start;

Wood wood;
Rock rock;

void ItemSlotCheck(const Tool* tool);
void CursorWoodRockCheck(const Cursor* cursor);

void WoodHitCheck(const Tool* tool, const Cursor* cursor);
void RockHitCheck(const Tool* tool, const Cursor* cursor);

void WoodRockStart(const InGame* ingame);



//初期化
void WoodRockInit(void)
{
	//hitフラグの初期化
	wood.hit_flg = false;
	rock.hit_flg = false;

	//初期位置の設定
	wood.position.x = 615.0f;
	wood.position.y = 305.0f;
	rock.position.x = 540.0f;
	rock.position.y = 305.0f;

	//画像変数の初期化
	for (int i = 0; i < 3; i++)
	{
		wood.image[i] = -1;
		rock.image[i] = -1;
	}
	
	//採ったアイテムの数の初期化
	rock.item_num = 0;

	//Hit数の初期化
	wood.hit_count = eHit0;
	rock.hit_count = eHit0;

	//画像の読み込み
	wood.image[0] = LoadGraph("Resource/images/Wood0.png");
	wood.image[1] = LoadGraph("Resource/images/Wood1.png");
	wood.image[2] = LoadGraph("Resource/images/Wood2.png");
	wood.image[3] = LoadGraph("Resource/images/Wood3.png");

	rock.image[0] = LoadGraph("Resource/images/Rock0.png");
	rock.image[1] = LoadGraph("Resource/images/Rock1.png");
	rock.image[2] = LoadGraph("Resource/images/Rock2.png");
	rock.image[3] = LoadGraph("Resource/images/Rock3.png");

	//画像の一枚目の初期化
	wood.animation = wood.image[0];
	rock.animation = rock.image[0];
}

//更新
void WoodRockUpdate(void)
{
	//ゲームのスタートを受け取る
	WoodRockStart(GetInGame());

	//ツールとカーソルとのHitチェック
	WoodHitCheck(Get_Tool(), GetCursor1());
	RockHitCheck(Get_Tool(), GetCursor1());


	//スタートがtrueになったなら
	if (woodrock_start == true)
	{
		//木,岩のアニメーション
		WoodAnimation();
		RockAnimation();
	}

}

//描画処理
void WoodRockDraw(void)
{
	//画像の描画
	DrawRotaGraphF(wood.position.x, wood.position.y, 1.0, 0.0, wood.animation, TRUE);
	DrawRotaGraphF(rock.position.x, rock.position.y, 1.0, 0.0, rock.animation, TRUE);

	//どのツールを持っているかを受け取る
	ItemSlotCheck(Get_Tool());
	//カーソルの座標を受け取る
	CursorWoodRockCheck(GetCursor1());
	//アイテム化した木と岩の数の描画
	WoodRockItemCount();

}

//木のアニメーション
void WoodAnimation(void)
{
	switch (wood.hit_count)
	{
	case eHit0:// Hit数0
		wood.animation = wood.image[0];
		if (wood.hit_flg == true)
		{
			wood.hit_count = eHit1;
			wood.hit_flg = false;//hitフラグをfalseにする

		}
		break;

	case eHit1:// Hit数1
		wood.animation = wood.image[1];
		if (wood.hit_flg == true)
		{
			wood.hit_count = eHit2;
			wood.hit_flg = false;//hitフラグをfalseにする
		}

		break;

	case eHit2:// Hit数2
		wood.animation = wood.image[2];
		if (wood.hit_flg == true)
		{
			wood.hit_count = eHit3;
			wood.hit_flg = false;   //hitフラグをfalseにする
		}
		break;

	case eHit3:// Hit数3
		wood.animation = wood.image[3];
		if (wood.hit_flg == true)
		{
			wood.hit_count = eHit0;     // 今だけループするようにしている
			wood.hit_flg = false;   // hitフラグをfalseにする
			wood.item_num++;     //　HIT数が3になった時、アイテム化した物の数を+1する
		}
		break;
	}

}
//岩のアニメーション
void RockAnimation(void)
{

	switch (rock.hit_count)
	{
	case eHit0:// Hit数0
		rock.animation = rock.image[0];
		if (rock.hit_flg == true)
		{
			rock.hit_count = eHit1;
			rock.hit_flg = false;//hitフラグをfalseにする
		}
		break;

	case eHit1:// Hit数1
		rock.animation = rock.image[1];
		if (rock.hit_flg == true)
		{
			rock.hit_count = eHit2;
			rock.hit_flg = false;//hitフラグをfalseにする
		}

		break;

	case eHit2:// Hit数2
		rock.animation = rock.image[2];
		if (rock.hit_flg == true)
		{
			rock.hit_count = eHit3;
			rock.hit_flg = false;//hitフラグをfalseにする
		}
		break;

	case eHit3:// Hit数3
		rock.animation = rock.image[3];
		if (rock.hit_flg == true)
		{
			rock.hit_count = eHit0;//今だけループするようにしている
			rock.hit_flg = false;//hitフラグをfalseにする
			rock.item_num++;//HIT数が3になった時、アイテム化した物の数を+1する
		}
		break;
	}

}

const Wood* GetWood(void)
{
	return &wood;
}

const Rock* GetRock(void)
{
	return &rock;
}


void WoodRockStart(const InGame* ingame)
{
	if (ingame->start == true)
	{
		woodrock_start = true;
	}

}

void ItemSlotCheck(const Tool* tool)
{
	DrawFormatString(200, 100, GetColor(255, 255, 255), "%d", tool->item_number);
}

void CursorWoodRockCheck(const Cursor* cursor)
{
	DrawFormatString(300, 100, GetColor(255, 255, 255), "%f    %f", cursor->position.x, cursor->position.y);
}


void WoodHitCheck(const Tool* tool, const Cursor* cursor)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//木とカ―ソルのX座標とY座標が一致していたら
	if (wood.position.x == cursor->position.x && wood.position.y == cursor->position.y)
	{
		//ツールがオノになっていたら
		if (tool->item_number == eAx)
		{
			//Aボタンが押されたなら
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
			{
				//Hitフラグをtrueにする
				wood.hit_flg = true;
			}
		}
	}
}

void RockHitCheck(const Tool* tool, const Cursor* cursor)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//岩とカ―ソルのX座標とY座標が一致していたら
	if (rock.position.x == cursor->position.x && rock.position.y == cursor->position.y)
	{
		//ツールがぴっけるになっていたら
		if (tool->item_number == ePickaxe)
		{
			//Aボタンが押されたなら
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
			{
				//Hitフラグをtrueにする
				rock.hit_flg = true;
			}
		}
	}
}

void WoodRockItemCount(void)
{
	DrawRotaGraphF(950, 70, 1.0, 0.0, wood.image[3], TRUE);
	DrawExtendFormatString(1000, 75, 2.0, 2.0, GetColor(255, 255, 255), "%d", wood.item_num);
	DrawRotaGraphF(1060, 70, 1.0, 0.0, rock.image[3], TRUE);
	DrawExtendFormatString(1110, 75, 2.0, 2.0, GetColor(255, 255, 255), "%d", rock.item_num);
}