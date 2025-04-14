#pragma once

#include "../Utility/Geometry.h"

#define		D_OBSTACLE_MAX	(10)
#define		D_OBS_ANIM_MAX	(7)


struct Obstacle
{
	int is_active;			//�L���t���O
	int image;				//�摜
	Position2D position;	//�ʒu���
	Size2D box_size;		//��`�̑傫��
};

void ObstacleManagerInit(void);
void ObstacleManagerUpdate(void);
void ObstacleManagerDraw(void);
const Obstacle * GetObstacle(int num);
