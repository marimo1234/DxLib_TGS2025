#include "Obstacle.h"
#include "Player.h"
#include "DxLib.h"
#include <math.h>

#define ITEM_NUM	(9)		//�A�C�e���̗v�f

void ObstacleAnimationControl(const Player* player);

Obstacle obstacle[D_OBSTACLE_MAX];
int obstacle_images[7];
int item_images[1];

//��Q���̏�����
void ObstacleManagerInit(void)
{
	//�X���C���̉摜�ǂݍ���
	/*LoadDivGraph("Resource/Images/slime.png", D_OBS_ANIM_MAX, D_OBS_ANIM_MAX, 1, 64, 64, obstacle_images);
	LoadDivGraph("Resource/Images/item.png", 1, 1, 1, 1152, 648, item_images);*/
}

//��Q���̍X�V
void ObstacleManagerUpdate(void)
{
	
}

//��Q���̕`��
void ObstacleManagerDraw(void)
{
	printf("����ɂ���\n");
}

//�\����Obstacle
const Obstacle* GetObstacle(int num)
{
	if (0 <= num && num < D_OBSTACLE_MAX)
	{
		return &obstacle[num];
	}

	return obstacle;
}

//��Q���̃X�|�[�����L����
void ObstacleAnimationControl(const Player* player)
{
	
}
