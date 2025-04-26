#pragma once

struct Goal
{
	bool flag;
	bool start;
	int image;
};

void GoalInit(void);
void GoalUpdate(void);
void GoalDraw(void);

const Goal* GetGoal(void);