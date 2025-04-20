#include "DxLib.h"
#include "WoodRock.h"
#include "../Utility/InputManager.h"

int wood_image[4] = {};
int rock_image[4] = {};
int wood_animation;
int rock_animation;
int wood_hitcount;
int rock_hitcount;

//������
void WoodRockInit(void)
{
	//Hit���̏�����
	wood_hitcount = eHit0;
	rock_hitcount = eHit0;

	//�摜�̈ꖇ�ڂ̏�����
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

//�X�V
void WoodRockUpdate(void)
{
	//�؂̃A�j���[�V����
	WoodAnimation();
	RockAnimation();
}

//�`�揈��
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

//A�L�[����������؂̕`�悷��摜��ς���
//��XHit�����񐔂Ŗ؂̕`�悷��摜��ς���悤�ɂ���
void WoodAnimation(void)
{
		switch (wood_hitcount)
		{
		case eHit0:// Hit��0
			wood_animation = wood_image[0];
			if (GetKeyInputState(KEY_INPUT_A) == ePress)
			{
				wood_hitcount = eHit1;
			}
			break;

		case eHit1:// Hit��1
			wood_animation = wood_image[1];
			if (GetKeyInputState(KEY_INPUT_A) == ePress)
			{
				wood_hitcount = eHit2;
			}
			
			break;

		case eHit2:// Hit��2
			wood_animation = wood_image[2];
			if (GetKeyInputState(KEY_INPUT_A) == ePress)
			{
				wood_hitcount = eHit3;
			}
			break;

		case eHit3:// Hit��3
			wood_animation = wood_image[3];
			if (GetKeyInputState(KEY_INPUT_A) == ePress)
			{
				wood_hitcount = eHit0;     //���������[�v����悤�ɂ��Ă���
			}
			break;
		}
	
}

void RockAnimation(void)
{
	switch (rock_hitcount)
	{
	case eHit0:// Hit��0
		rock_animation = rock_image[0];
		if (GetKeyInputState(KEY_INPUT_A) == ePress)
		{
			rock_hitcount = eHit1;
		}
		break;

	case eHit1:// Hit��1
		rock_animation = rock_image[1];
		if (GetKeyInputState(KEY_INPUT_A) == ePress)
		{
			rock_hitcount = eHit2;
		}

		break;

	case eHit2:// Hit��2
		rock_animation = rock_image[2];
		if (GetKeyInputState(KEY_INPUT_A) == ePress)
		{
			rock_hitcount = eHit3;
		}
		break;

	case eHit3:// Hit��3
		rock_animation = rock_image[3];
		if (GetKeyInputState(KEY_INPUT_A) == ePress)
		{
			rock_hitcount = eHit0;     //���������[�v����悤�ɂ��Ă���
		}
		break;
	}

}