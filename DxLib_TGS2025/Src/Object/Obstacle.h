#pragma once

#include "../Utility/Geometry.h"

#define		D_OBSTACLE_MAX	(10)
#define		D_OBS_ANIM_MAX	(7)


struct Obstacle
{
	int is_active;			//有効フラグ
	int image;				//画像
	Position2D position;	//位置情報
	Size2D box_size;		//矩形の大きさ
};

struct Hole
{
	int image;
};

void ObstacleManagerInit(void);
void ObstacleManagerUpdate(void);
void ObstacleManagerDraw(void);
const Obstacle * GetObstacle(void);
const Hole* GetHole(void);
