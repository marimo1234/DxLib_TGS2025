#include "DxLib.h"
#include "WoodRock.h"
#include "../Utility/InputManager.h"
#include"../Utility/PadInputManager.h"

int wood_image[4] = {};
int rock_image[4] = {};
int wood_animation;
int rock_animation;
int wood_hitcount;
int rock_hitcount;
int woodrock_start;

WoodRock woodrock;

//初期化
void WoodRockInit(void)
{
	woodrock.item_number = 0;

	//Hit数の初期化
	wood_hitcount = eHit0;
	rock_hitcount = eHit0;

	//画像の一枚目の初期化
	wood_animation = wood_image[0];
	wood_animation = wood_image[0];

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
     WoodRockStart(GetStart());
	/* ItemSlotCheck(Get_Tool());*/

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
	DrawRotaGraph(660, 280, 1.0, 0.0, wood_animation, TRUE);
	DrawRotaGraph(580, 280, 1.0, 0.0, rock_animation, TRUE);
	ItemSlotCheck(Get_Tool());
}

//Aキーを押したら木の描画する画像を変える
//後々Hitした回数で木の描画する画像を変えるようにする
void WoodAnimation(void)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
		switch (wood_hitcount)
		{
		case eHit0:// Hit数0
			wood_animation = wood_image[0];
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
			{
				wood_hitcount = eHit1;
			}
			break;

		case eHit1:// Hit数1
			wood_animation = wood_image[1];
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
			{
				wood_hitcount = eHit2;
			}
			
			break;

		case eHit2:// Hit数2
			wood_animation = wood_image[2];
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
			{
				wood_hitcount = eHit3;
			}
			break;

		case eHit3:// Hit数3
			wood_animation = wood_image[3];
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
			{
				wood_hitcount = eHit0;     //今だけループするようにしている
				
			}
			break;
		}
	
}

void RockAnimation(void)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	switch (rock_hitcount)
	{
	case eHit0:// Hit数0
		rock_animation = rock_image[0];
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
		{
			rock_hitcount = eHit1;
		}
		break;

	case eHit1:// Hit数1
		rock_animation = rock_image[1];
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
		{
			rock_hitcount = eHit2;
		}

		break;

	case eHit2:// Hit数2
		rock_animation = rock_image[2];
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
		{
			rock_hitcount = eHit3;
		}
		break;

	case eHit3:// Hit数3
		rock_animation = rock_image[3];
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
		{
			rock_hitcount = eHit0;     //今だけループするようにしている
			woodrock.item_number++;    //HIT数が3になった時、アイテム化した物の数を+1する
		}
		break;
	}

}

const WoodRock* GetWoodRock(void)
{
	return &woodrock;
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
