#pragma once

#include "../Utility/Geometry.h"

struct Goal
{
	Vector2D position;
	bool flag;
	bool start;
	int print_image;
	int flag_image;
	bool print_flag;
	int count;
};

void GoalInit(void);
void GoalUpdate(void);
void GoalDraw(void);
void GoalReset(void);

const Goal* GetGoal(void);