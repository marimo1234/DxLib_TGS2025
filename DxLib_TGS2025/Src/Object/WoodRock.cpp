#include "DxLib.h"
#include "WoodRock.h"
#include "../Utility/InputManager.h"

int wood_image[4] = {};
int rock_image[4] = {};
int wood_animation;
int rock_animation;
int wood_hitcount;
int rock_hitcount;

//初期化
void WoodRockInit(void)
{
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
	//木のアニメーション
	WoodAnimation();
	RockAnimation();
}

//描画処理
void WoodRockDraw(void)
{

	DrawRotaGraph(660, 280, 1.0, 0.0, wood_animation, TRUE);
	DrawRotaGraph(200, 200, 1.0, 0.0, wood_image[0], TRUE);
	DrawRotaGraph(200, 280, 1.0, 0.0, wood_image[1], TRUE);
	DrawRotaGraph(200, 360, 1.0, 0.0, wood_image[2], TRUE);
	DrawRotaGraph(200, 440, 1.0, 0.0, wood_image[3], TRUE);

	DrawRotaGraph(580, 280, 1.0, 0.0, rock_animation, TRUE);
	DrawRotaGraph(280, 200, 1.0, 0.0, rock_image[0], TRUE);
	DrawRotaGraph(280, 280, 1.0, 0.0, rock_image[1], TRUE);
	DrawRotaGraph(280, 360, 1.0, 0.0, rock_image[2], TRUE);
	DrawRotaGraph(280, 440, 1.0, 0.0, rock_image[3], TRUE);
}

//Aキーを押したら木の描画する画像を変える
//後々Hitした回数で木の描画する画像を変えるようにする
void WoodAnimation(void)
{
		switch (wood_hitcount)
		{
		case eHit0:// Hit数0
			wood_animation = wood_image[0];
			if (GetKeyInputState(KEY_INPUT_A) == ePress)
			{
				wood_hitcount = eHit1;
			}
			break;

		case eHit1:// Hit数1
			wood_animation = wood_image[1];
			if (GetKeyInputState(KEY_INPUT_A) == ePress)
			{
				wood_hitcount = eHit2;
			}
			
			break;

		case eHit2:// Hit数2
			wood_animation = wood_image[2];
			if (GetKeyInputState(KEY_INPUT_A) == ePress)
			{
				wood_hitcount = eHit3;
			}
			break;

		case eHit3:// Hit数3
			wood_animation = wood_image[3];
			if (GetKeyInputState(KEY_INPUT_A) == ePress)
			{
				wood_hitcount = eHit0;     //今だけループするようにしている
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
		if (GetKeyInputState(KEY_INPUT_A) == ePress)
		{
			rock_hitcount = eHit1;
		}
		break;

	case eHit1:// Hit数1
		rock_animation = rock_image[1];
		if (GetKeyInputState(KEY_INPUT_A) == ePress)
		{
			rock_hitcount = eHit2;
		}

		break;

	case eHit2:// Hit数2
		rock_animation = rock_image[2];
		if (GetKeyInputState(KEY_INPUT_A) == ePress)
		{
			rock_hitcount = eHit3;
		}
		break;

	case eHit3:// Hit数3
		rock_animation = rock_image[3];
		if (GetKeyInputState(KEY_INPUT_A) == ePress)
		{
			rock_hitcount = eHit0;     //今だけループするようにしている
		}
		break;
	}

}