#include "Obstacle.h"
#include "Player.h"
#include "DxLib.h"
#include <math.h>

#define ITEM_NUM	(9)		//�A�C�e���̗v�f

void ObstacleAnimationControl(const Player* player);

Obstacle obstacle[D_OBSTACLE_MAX];
int obstacle_images[7];
int item_images[1];
int oanimation_count;
int oanimation_num;

//��Q���̏�����
void ObstacleManagerInit(void)
{
	//�X���C���̉摜�ǂݍ���
	LoadDivGraph("Resource/Images/slime.png", D_OBS_ANIM_MAX, D_OBS_ANIM_MAX, 1, 64, 64, obstacle_images);
	LoadDivGraph("Resource/Images/item.png", 1, 1, 1, 1152, 648, item_images);

	//�A�j���[�V�����̐ݒ�
	oanimation_count = 0;
	oanimation_num = 0;

	//��Q�����P�O��
	for (int i = 0; i < D_OBSTACLE_MAX - 1; i++)
	{
		//�����ݒ�
		//�X���C��
		obstacle[i].is_active = FALSE;							//�L�����
		obstacle[i].position.x = 1280.0f + 130.0f;				//�����ʒu�iX)
		obstacle[i].position.y = 600.0f;						//�����ʒu�iY�j
		obstacle[i].box_size.x = 60.0f;							//��`�̑傫���iX)
		obstacle[i].box_size.y = 60.0f;							//��`�̑傫���iY)
		obstacle[i].image = obstacle_images[oanimation_num];	//�摜�̐؂�ւ�
	}
	//�A�C�e��
	obstacle[ITEM_NUM].is_active = FALSE;
	obstacle[ITEM_NUM].position.x = 1280.0f + 130.0f;
	obstacle[ITEM_NUM].position.y = 300.0f;
	obstacle[ITEM_NUM].box_size.x = 60.0f;
	obstacle[ITEM_NUM].box_size.y = 60.0f;
	obstacle[ITEM_NUM].image = item_images[0];
}

//��Q���̍X�V
void ObstacleManagerUpdate(void)
{
	ObstacleAnimationControl(GetPlayer());

	for (int i = 0; i < D_OBSTACLE_MAX; i++)
	{
		if (obstacle[i].is_active == TRUE)
		{
			obstacle[i].position.x -= GetPlayer()->velocity.x;
			if (obstacle[i].position.x <= -64.0f)
			{
				obstacle[i].is_active = FALSE;
				if (GetRand(1) == 1)
				{
					obstacle[i].position.x = 1280.0f + 130.0f;
				}
				{
					obstacle[i].position.x = 1280.0f + 1000.0f;
				}
			}
		}
	}
}

//��Q���̕`��
void ObstacleManagerDraw(void)
{
	for (int i = 0; i < D_OBSTACLE_MAX - 1; i++)
	{
		if (obstacle[i].is_active == TRUE)
		{
			float enemy_x = obstacle[i].position.x;
			float enemy_y = obstacle[i].position.y;
			int img = obstacle[i].image;
			DrawRotaGraphF(enemy_x, enemy_y, 1.2f, 0.0, img, TRUE);
		}
	}
	if (obstacle[ITEM_NUM].is_active == TRUE)
	{
		float item_x = obstacle[ITEM_NUM].position.x;
		float item_y = obstacle[ITEM_NUM].position.y;
		int img9 = obstacle[ITEM_NUM].image;
		DrawRotaGraphF(item_x, item_y, 0.4f, 0.0, img9, TRUE);
	}
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
	oanimation_count++;
	if (obstacle[0].is_active == FALSE)
	{
		if (GetRand(80) == 0)
		{
			obstacle[0].is_active = TRUE;
		}
	}
	if (obstacle[1].is_active == FALSE)
	{
		if (GetRand(15) == 1)
		{
			obstacle[1].is_active = TRUE;
		}
	}
	if (player->situation != 2)
	{
		if (obstacle[9].is_active == FALSE)
		{
			if (GetRand(100) == 1)
			{
				obstacle[9].is_active = TRUE;
			}
		}
	}
	if (oanimation_count > 5)
	{
		//���̉摜�ԍ���ݒ�
		oanimation_count = 0;
		oanimation_num = ++oanimation_num % D_OBS_ANIM_MAX;
	}
	for (int i = 0; i < D_OBSTACLE_MAX - 1; i++)
	{
		obstacle[i].image = obstacle_images[oanimation_num];
	}
}
