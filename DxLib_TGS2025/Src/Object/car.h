#pragma once


#include "../Utility/Geometry.h"

struct Car
{
	Vector2D position;
	int animation;
	int image[2];
	bool start;

};

void CarInit(void);
void CarManagerUpdate(void);
void CarDraw(void);

const Car* GetCar(void);

