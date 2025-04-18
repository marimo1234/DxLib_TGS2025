#include "DxLib.h"
#include "car.h"
#include "../Utility/InputManager.h"


int car_x = 0;
int car_y = 0;
int car_animation;
int car_image[2] = {};
int car_direction = 0;
int i;

void CarInit(void)
{
	i = 1;
	car_x = 80;
	car_y = 80;
	car_direction = 0;

	car_image[0] = LoadGraph("Resource/images/left_car.png");
	car_image[1] = LoadGraph("Resource/images/front_car.png");
}

void CarManagerUpdate(void)
{
	

	if (car_x != 80 * i)
	{
		car_x++;
		car_animation= car_image[0];
	}
	if (car_x == 80 * i && car_y != 80 * i)
	{
		car_y++;
		car_animation = car_image[1];
	}
	if (car_x == 80 * i && car_y == 80 * i)
	{
		i++;
	}

	if (car_y > 720)
	{
		car_x = 80;
		car_y = 80;
		i = 1;
	}
	
}

void CarDraw(void)
{
	DrawRotaGraph(car_x, car_y, 1.0, 0.0, car_animation, TRUE);
}