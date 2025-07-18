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
 
//enum eMoleDirection
//{
//	eMoleUp,
//	eMoleDown,
//	eMoleRight,
//	eMoleLeft,
//};

struct Mole
{
	bool start;
	bool menu_flag;
	bool operable_flag;
	int image[4];
	int rock1_image[4];
	int rock2_image[4];
	int wood_image[4];
	int image_num[12][7];
	int animation[12][7];
	int image_count;
	bool put_rock_flag[12][7];

	int warn_image;
	bool warn_flag;


	int rock_x_max;
	int rock_x_min;
	int rock_y_min;
	int rock_y_max;
	
};

struct Lake
{
	int image;
};

void ObstacleManagerInit(void);
void ObstacleManagerUpdate(void);
void ObstacleManagerDraw(void);
void ObstacleManagerResourceInit(void);
const Obstacle * GetObstacle(void);
const Mole* GetMole(void);
const Lake* GetLake(void);


void MoleReset(void);
void MolePutFlagReset(void);
