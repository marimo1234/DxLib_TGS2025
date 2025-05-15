#pragma once


#include "../Utility/Geometry.h"

enum CarDirection
{
	eUp,
	eDown,
	eRight,
	eLeft,
	eStop,
};

struct Car
{
	Vector2D position;
	Vector2D velocity;
	int animation;
	int image[4];
	bool start;
	int x;
	int y;
	int direction;
	int current_x;
	int current_y;
	int next_x[84];
	int next_y[84];
	int road_count;
	int next_count;
	int old_direction;
	bool goal_flag;
	int gameover;
	bool gameover_image;
	int goal;
	int goalprint;
	
};

void CarInit(void);
void CarManagerUpdate(void);
void CarDraw(void);

const Car* GetCar(void);

void CarReset(void);
void CarMovePosition(void);

