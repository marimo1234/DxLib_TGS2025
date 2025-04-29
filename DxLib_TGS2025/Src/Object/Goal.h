#pragma once

#include "../Utility/Geometry.h"

struct Goal
{
	Vector2D position;
	bool flag;
	bool start;
	int image;
	int flag_image;
};

void GoalInit(void);
void GoalUpdate(void);
void GoalDraw(void);

const Goal* GetGoal(void);