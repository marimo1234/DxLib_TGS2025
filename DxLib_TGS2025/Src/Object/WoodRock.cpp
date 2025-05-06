#include "DxLib.h"
#include "WoodRock.h"
#include "../Utility/InputManager.h"
#include"../Utility/PadInputManager.h"
#include "../Object/Tool.h"
#include "../Object/Cursor.h"
#include "../Object/Map.h"
#include"../Scene/InGame/InGameScene.h"

#include <math.h>



int woodrock_start;

Wood wood;
Rock rock;

void ItemSlotCheck(const Tool* tool);
void CursorWoodRockCheck(const Cursor* cursor);

void WoodHitCheck(const Tool* tool, const Cursor* cursor, const CreateStage* stage);
void RockHitCheck(const Tool* tool, const Cursor* cursor, const CreateStage* stage);

void WoodRockStart(const InGame* ingame);
void WoodRockSub(const Tool* tool);


//初期化
void WoodRockInit(void)
{
	//ヒットフラグ、ヒット数、アニメーションの初期化
	for (int i = 0; i < WOODROCK_MAX; i++)
	{
		wood.hit_flag[i] = false;
		wood.hit_count[i] = eHit0;
		wood.animation[i] = wood.image[0];

		rock.hit_flag[i] = false;
		rock.hit_count[i] = eHit0;
		rock.animation[i] = rock.image[0];
	}

	//木、岩の数変数
	wood.count = 0;
	rock.count = 0;

	//画像変数の初期化
	for (int i = 0; i < 3; i++)
	{
		wood.image[i] = -1;
		rock.image[i] = -1;
	}
	
	//採ったアイテムの数の初期化
	wood.item_num = 0;
	rock.item_num = 0;

	//画像の読み込み
	wood.image[0] = LoadGraph("Resource/images/Wood0.png");
	wood.image[1] = LoadGraph("Resource/images/Wood1.png");
	wood.image[2] = LoadGraph("Resource/images/Wood2.png");
	wood.image[3] = LoadGraph("Resource/images/Wood3.png");

	rock.image[0] = LoadGraph("Resource/images/Rock0.png");
	rock.image[1] = LoadGraph("Resource/images/Rock1.png");
	rock.image[2] = LoadGraph("Resource/images/Rock2.png");
	rock.image[3] = LoadGraph("Resource/images/Rock3.png");

	
}

//更新
void WoodRockUpdate(void)
{
	//ゲームのスタートを受け取る
	WoodRockStart(GetInGame());

	//スタートがtrueになったなら
	if (woodrock_start == true)
	{  
		//木,岩のアニメーション
		WoodAnimation();
		RockAnimation();

		//ツールとカーソルとのHitチェック
		WoodHitCheck(Get_Tool(), GetCursor1(),GetStage());
		RockHitCheck(Get_Tool(), GetCursor1(),GetStage());

		//道路を作ったらアイテム化した数が減る
		WoodRockSub(Get_Tool());
	}
	else
	{
		//初期化
		WoodRockReset();
	}


}

//描画処理
void WoodRockDraw(void)
{
	//画像の描画
	/*DrawRotaGraphF(wood.position.x, wood.position.y, 1.0, 0.0, wood.animation, TRUE);*/
	/*DrawRotaGraphF(rock.position.x, rock.position.y, 1.0, 0.0, rock.animation, TRUE);*/

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
	switch (wood.hit_count[wood.count])
	{
	case eHit0:// Hit数0
		wood.animation[wood.count] = wood.image[0];
		if (wood.hit_flag[wood.count] == true)
		{
			wood.hit_count[wood.count] = eHit1;
			wood.hit_flag[wood.count] = false;//hitフラグをfalseにする

		}
		break;

	case eHit1:// Hit数1
		wood.animation[wood.count] = wood.image[1];
		if (wood.hit_flag[wood.count] == true)
		{
			wood.hit_count[wood.count] = eHit2;
			wood.hit_flag[wood.count] = false;//hitフラグをfalseにする
		}

		break;

	case eHit2:// Hit数2
		wood.animation[wood.count] = wood.image[2];
		if (wood.hit_flag[wood.count] == true)
		{
			wood.item_num++;     //　HIT数が3になった時、アイテム化した物の数を+1する
			wood.hit_count[wood.count] = eHit3;
			wood.hit_flag[wood.count] = false;   //hitフラグをfalseにする
		}
		break;

	case eHit3:// Hit数3
		wood.animation[wood.count] = wood.image[3];
		WoodMove();
		break;
	}

}
//岩のアニメーション
void RockAnimation(void)
{

	switch (rock.hit_count[rock.count])
	{
	case eHit0:// Hit数0
		rock.animation[rock.count] = rock.image[0];
		if (rock.hit_flag[rock.count] == true)
		{
			rock.hit_count[rock.count] = eHit1;
			rock.hit_flag[rock.count] = false;//hitフラグをfalseにする
		}
		break;

	case eHit1:// Hit数1
		rock.animation[rock.count] = rock.image[1];
		if (rock.hit_flag[rock.count] == true)
		{
			rock.hit_count[rock.count] = eHit2;
			rock.hit_flag[rock.count] = false;//hitフラグをfalseにする
		}

		break;

	case eHit2:// Hit数2
		rock.animation[rock.count] = rock.image[2];
		if (rock.hit_flag[rock.count] == true)
		{
			rock.item_num++;//HIT数が3になった時、アイテム化した物の数を+1する
			rock.hit_count[rock.count] = eHit3;
			rock.hit_flag[rock.count] = false;//hitフラグをfalseにする
		}
		break;

	case eHit3:// Hit数3
		rock.animation[rock.count] = rock.image[3];
		RockMove();
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
	else
	{
		woodrock_start = false;
	}

}

void WoodRockSub (const Tool*tool)
{
	if (tool->rock_sub_flag == true)
	{
		rock.item_num--;
	}
	if (tool->wood_sub_flag == true)
	{
		wood.item_num--;
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


void WoodHitCheck(const Tool* tool, const Cursor* cursor, const CreateStage* stage)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//カーソルの配列番号が木だったら
	if (stage->array[cursor->array_x][cursor->array_y] == 1);
	{

		for (int i = 0; i < WOODROCK_MAX; i++)
		{
			//カーソルと木の配列番号が一致したら
			if (cursor->array_x == stage->wood_x[i] && cursor->array_y == stage->wood_y[i])
			{
				wood.count = i;
				//ツールがオノになっていたら
				if (tool->item_number == eAx)
				{
					//Aボタンが押されたなら
					if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
					{
						//Hitフラグをtrueにする
						wood.hit_flag[wood.count] = true;
					}
				}
			}
		}


	}
}

void RockHitCheck(const Tool* tool, const Cursor* cursor, const CreateStage* stage)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//カーソルの配列番号が木だったら
	if (stage->array[cursor->array_x][cursor->array_y] == 1);
	{

		for (int i = 0; i < WOODROCK_MAX; i++)
		{
			//カーソルと岩の配列番号が一致したら
			if (cursor->array_x == stage->rock_x[i] && cursor->array_y == stage->rock_y[i])
			{
				rock.count = i;
				//ツールがつるはしになっていたら
				if (tool->item_number == ePickaxe)
				{
					//Aボタンが押されたなら
					if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
					{
						//Hitフラグをtrueにする
						rock.hit_flag[rock.count] = true;
					}
				}
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

void WoodRockReset(void)
{

	///アイテム数の初期化
	wood.item_num = 0;
	rock.item_num = 0;

	for (int i = 0; i < WOODROCK_MAX; i++)
	{
		wood.hit_flag[i] = false;
		wood.hit_count[i] = eHit0;
		wood.animation[i] = wood.image[0];

		rock.hit_flag[i] = false;
		rock.hit_count[i] = eHit0;
		rock.animation[i] = rock.image[0];
	}
}

void WoodMove(void)
{
	float dx = fabsf(wood.position.x - 950.0f); // X座標の差
	float dy = fabsf(wood.position.y - 70.0f); // Y座標の差
	float da = dy / dx;//傾き

	if (wood.position.x <= 950.0f)
	{
		wood.position.x += 2.0f;
	}
	if (wood.position.y >= 70.0f)
	{
		wood.position.y += -2.0f*da; //上向きがマイナス方向だから－つけてます
	}

}

void RockMove(void)
{
	float dx = fabsf(rock.position.x - 1060.0f); // X座標の差
	float dy = fabsf(rock.position.y - 70.0f); // Y座標の差
	float da = dy / dx;//傾き

	if (rock.position.x <= 1060.0f)
	{
		rock.position.x += 2.0f;
	}
	if (rock.position.y >= 70.0f)
	{
		rock.position.y += -2.0f * da; //上向きがマイナス方向だから－つけてます
	}

}