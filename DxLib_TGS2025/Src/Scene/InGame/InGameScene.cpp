#include "InGameScene.h"
#include "../../Utility/InputManager.h"
#include "../../Object/Player.h"
#include "../../Object/Obstacle.h"
#include "../Result/ResultScene.h"
#include "../../Utility/PadInputManager.h"
#include "../../Object/car.h"
#include "../../Object/WoodRock.h"
#include "../../Object/map.h"
#include "../../Object/Tool.h"
#include "DxLib.h"

#include <math.h>
#include <stdlib.h>

#define D_SCROOL_SPEED		(200.0f)

void HitCheck(const Player* player, const Obstacle* obstacle, int index);
void PlayBgm(void);

int Before_Hit[10];		//�O�̓����蔻��
int Now_Hit[10];		//���̓����蔻��
int stage;

void InGameSceneInit(void)
{
	PlayBgm();

	//�}�b�v�̏�����
	MapInit();
	//��Q���̏�����
	ObstacleManagerInit();
	//�؊�̏�����
	WoodRockInit();
	//�c�[���̏�����
	ToolInit();
	//�Ԃ̏�����
	CarInit();
	//�v���C���[�̏�����
	PlayerInit();

}

eSceneType InGameSceneUpdate()
{
	//�}�b�v�̍X�V
	MapUpdate();
	//��Q���̍X�V
	ObstacleManagerUpdate();
	//�؊�̍X�V
	WoodRockUpdate();
	//�c�[���̍X�V
	ToolManagerUpdate();
	//�Ԃ̍X�V
	CarManagerUpdate();
	//�v���C���[�̍X�V
	PlayerUpdate();





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
	DrawFormatString(50, 10, GetColor(255, 255, 255), "�X�y�[�X�Ń��U���g��ʂ�");

	//�}�b�v�̕`��
	MapDraw(stage);

	//��Q���̕`��
	ObstacleManagerDraw();

	//�؊�̕`��
	WoodRockDraw();

	//�c�[���̕`��
	ToolDraw();

	//�Ԃ̕`��
	CarDraw();

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

