#pragma once


#include "../Utility/Geometry.h"

enum CarDirection
{
	eUp,
	eDown,
	eRight,
	eStop,
};

struct Car
{
	Vector2D position;
	int animation;
	int image[2];
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
};

void CarInit(void);
void CarManagerUpdate(void);
void CarDraw(void);

const Car* GetCar(void);

void CarReset(void);
void CarMovePosition(void);

