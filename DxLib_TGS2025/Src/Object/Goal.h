#pragma once

#include "../Utility/Geometry.h"

struct Goal
{
	Vector2D position;
	bool flag;
	bool start;
	bool menu_flag;
	int print_image;
	int flag_image;
	bool print_flag;
	int count;
	int print_count;
	int rand_handle;
	float firework_x[3];
	int firework_count;
	int firework_num[3];
	float add_y[3];
	float firework_rate[3];

	int gameover_image;
	int whiteback_image;
	int blackback_image;
	int firework_image[12];
	int firework_image2[12];
	int firework_image3[12];
};

void GoalInit(void);
void GoalUpdate(void);
void GoalDraw(void);
void GoalReset(void);
void GoalResourceInit(void);


const Goal* GetGoal(void);