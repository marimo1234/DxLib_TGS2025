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

struct Mole
{
	bool start;
	int image[4];
	int image_num;
	int animation;
	int image_count;
};

struct Lake
{
	int image;
};

void ObstacleManagerInit(void);
void ObstacleManagerUpdate(void);
void ObstacleManagerDraw(void);
const Obstacle * GetObstacle(void);
const Mole* GetMole(void);
const Lake* GetLake(void);

void MoleRandomDirection(void);
void MoleReset(void);
