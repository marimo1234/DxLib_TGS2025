#include "InGameScene.h"
#include "../../Utility/InputManager.h"
#include "../../Object/Player.h"
#include "../../Object/Obstacle.h"
#include "../Result/ResultScene.h"
#include "DxLib.h"

#include <math.h>
#include <stdlib.h>

#define D_SCROOL_SPEED		(200.0f)

void HitCheck(const Player* player, const Obstacle* obstacle, int index);
void PlayBgm(void);


float scrool_x;			//���X�N���[��
int Before_Hit[10];		//�O�̓����蔻��
int Now_Hit[10];		//���̓����蔻��

void InGameSceneInit(void)
{
	PlayBgm();

	//�v���C���[�̏�����
	PlayerInit();
	//��Q���̏�����
	ObstacleManagerInit();

	scrool_x = 0.0f;
}

eSceneType InGameSceneUpdate()
{
	//�v���C���[�̍X�V
	PlayerUpdate();
	//��Q���̍X�V
	ObstacleManagerUpdate();

	//�v���C���[���ړ������������w�i�����炷
	scrool_x -= GetPlayer()->velocity.x;
	if (scrool_x <= -1280.0f)
	{
		scrool_x += 1280.0f;
	}

	/*�����蔻��̌v�Z�i�v���C���[�Ə�Q���j*/
	for (int i = 0; i < D_OBSTACLE_MAX; i++)
	{
		HitCheck(GetPlayer(), GetObstacle(i), i);
	}

	if (GetKeyInputState(KEY_INPUT_SPACE) == ePress)
	{
		return eResult;	//�C���Q�[����ʂ�
	}

	return eInGame;
}

void InGameSceneDraw(void)
{
	//�w�i�摜�̕`��
	/*DrawGraphF(scrool_x, 0, , TRUE);
	DrawGraphF(1280.0f + scrool_x, 0, , TRUE);*/
	DrawFormatString(100, 100, GetColor(255, 255, 255), "�X�y�[�X�Ń��U���g��ʂ�");

	//��Q���̕`��
	ObstacleManagerDraw();

	//�v���C���[�̕`��
	PlayerDraw();
}


//��`���m�̓����蔻��̌v�Z����
void HitCheck(const Player* player, const Obstacle* obstacle, int index)
{
	if (obstacle->is_active == TRUE)
	{
		float dx = fabsf(player->position.x - obstacle->position.x);
		float dy = fabsf(player->position.y - obstacle->position.y);

		float bx = (player->box_size.x + obstacle->box_size.x) * 0.5f;
		float by = (player->box_size.y + obstacle->box_size.y) * 0.5f;

		if ((dx < bx) && (dy < by))
		{
			
		}
		else
		{
			
		}
	}
}

//�C���Q�[��BGM�Đ�
void PlayBgm(void)
{
	/*PlaySoundMem(, DX_PLAYTYPE_LOOP);*/
}

