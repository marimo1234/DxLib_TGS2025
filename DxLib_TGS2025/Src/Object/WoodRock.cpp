#include "DxLib.h"
#include "WoodRock.h"
#include "../Utility/InputManager.h"
#include"../Utility/PadInputManager.h"
#include "../Object/Tool.h"
#include "../Object/Cursor.h"

int wood_image[4] = {};
int rock_image[4] = {};
int wood_animation;
int rock_animation;
int wood_hitcount;
int rock_hitcount;
int woodrock_start;
bool wood_hit_flg; 
bool rock_hit_flg; 

Wood wood;
Rock rock;

void ItemSlotCheck(const Tool* tool);
void CursorWoodRockCheck(const Cursor* cursor);

void WoodHitCheck(const Tool* tool, const Cursor* cursor);
void RockHitCheck(const Tool* tool, const Cursor* cursor);


//初期化
void WoodRockInit(void)
{
	//hitフラグの初期化
	wood_hit_flg = false;
	rock_hit_flg = false;

	wood.position.x = 615.0f;
	wood.position.y = 305.0f;
	rock.position.x = 540.0f;
	rock.position.y = 305.0f;
	//採ったアイテムの数の初期化
	rock.item_num = 0;

	//Hit数の初期化
	wood_hitcount = eHit0;
	rock_hitcount = eHit0;

	//画像の一枚目の初期化
	wood_animation = wood_image[0];
	rock_animation = rock_image[0];

	//画像の読み込み
	wood_image[0] = LoadGraph("Resource/images/Wood0.png");
	wood_image[1] = LoadGraph("Resource/images/Wood1.png");
	wood_image[2] = LoadGraph("Resource/images/Wood2.png");
	wood_image[3] = LoadGraph("Resource/images/Wood3.png");

	rock_image[0] = LoadGraph("Resource/images/Rock0.png");
	rock_image[1] = LoadGraph("Resource/images/Rock1.png");
	rock_image[2] = LoadGraph("Resource/images/Rock2.png");
	rock_image[3] = LoadGraph("Resource/images/Rock3.png");
}

//更新
void WoodRockUpdate(void)
{
	//ゲームのスタートを受け取る
	WoodRockStart(GetStart());
	/* ItemSlotCheck(Get_Tool());*/

	WoodHitCheck(Get_Tool(), GetCursor1());
	RockHitCheck(Get_Tool(), GetCursor1());


	//スタートされたなら
	if (woodrock_start == TRUE)
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
	DrawRotaGraphF(wood.position.x, wood.position.y, 1.0, 0.0, wood_animation, TRUE);
	DrawRotaGraphF(rock.position.x, rock.position.y, 1.0, 0.0, rock_animation, TRUE);

	//どのツールを持っているかを受け取る
	ItemSlotCheck(Get_Tool());
	//カーソルの座標を受け取る
	CursorWoodRockCheck(GetCursor1());

}

//Aキーを押したら木の描画する画像を変える
//後々Hitした回数で木の描画する画像を変えるようにする
void WoodAnimation(void)
{
		switch (wood_hitcount)
		{
		case eHit0:// Hit数0
			wood_animation = wood_image[0];
			if (wood_hit_flg == true)
			{
				wood_hitcount = eHit1;
				wood_hit_flg = false;//hitフラグをfalseにする
				
			}
			break;

		case eHit1:// Hit数1
			wood_animation = wood_image[1];
			if (wood_hit_flg == true)
			{
				wood_hitcount = eHit2;
				wood_hit_flg = false;//hitフラグをfalseにする
			}
			
			break;

		case eHit2:// Hit数2
			wood_animation = wood_image[2];
			if (wood_hit_flg == true)
			{
				wood_hitcount = eHit3;
				wood_hit_flg = false;//hitフラグをfalseにする
			}
			break;

		case eHit3:// Hit数3
			wood_animation = wood_image[3];
			if (wood_hit_flg == true)
		{
				wood_hitcount = eHit0;     //今だけループするようにしている
				wood_hit_flg = false;//hitフラグをfalseにする
				wood.item_num++;//HIT数が3になった時、アイテム化した物の数を+1する
			}
			break;
		}
	
}

void RockAnimation(void)
{

	switch (rock_hitcount)
	{
	case eHit0:// Hit数0
		rock_animation = rock_image[0];
		if (rock_hit_flg == true)
		{
			rock_hitcount = eHit1;
			rock_hit_flg = false;//hitフラグをfalseにする
		}
			break;

	case eHit1:// Hit数1
		rock_animation = rock_image[1];
		if (rock_hit_flg == true)
		{
			rock_hitcount = eHit2;
			rock_hit_flg = false;//hitフラグをfalseにする
		}

		break;

	case eHit2:// Hit数2
		rock_animation = rock_image[2];
		if (rock_hit_flg == true)
		{
			rock_hitcount = eHit3;
			rock_hit_flg = false;//hitフラグをfalseにする
		}
		break;

	case eHit3:// Hit数3
		rock_animation = rock_image[3];
		if (rock_hit_flg == true)
		{
			rock_hitcount = eHit0;//今だけループするようにしている
			rock_hit_flg = false;//hitフラグをfalseにする
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


void WoodRockStart(const Start* start)
{
	if (start->GameStart == TRUE)
	{
		woodrock_start = TRUE;
	}

}

void ItemSlotCheck(const Tool*tool)
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

	//岩とカ―ソルのX座標とY座標が一致していたら
	if (wood.position.x == cursor->position.x && wood.position.y == cursor->position.y)
	{
		//ツールがぴっけるになっていたら
		if (tool->item_number == eAx)
		{
			//Aボタンが押されたなら
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
			{
				wood_hit_flg = true;
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
				rock_hit_flg = true;
			}
		}
	}
}