#pragma once


#include "../Utility/Geometry.h"

struct Car
{
	Vector2D position;
	int animation;
	int image[2];
	bool start;
	int x;
	int y;

};

void CarInit(void);
void CarManagerUpdate(void);
void CarDraw(void);

const Car* GetCar(void);

void CarReset(void);

