#include "DxLib.h"
#include "car.h"
#include "../Utility/InputManager.h"


int car_x = 0;
int car_y = 0;
int car_animation;
int car_image[2] = {};
int car_direction = 0;

void CarInit(void)
{
	car_x = 540;
	car_y = 390;
	car_direction = 0;

	car_image[0] = LoadGraph("Resource/images/left_car.png");
	car_image[1] = LoadGraph("Resource/images/front_car.png");
}

void CarManagerUpdate(void)
{
	//Œü‚«‚ğí‚É0‚É‚·‚é
	car_direction = 0;

	//‰E
	if (GetKeyInputState(KEY_INPUT_D) == eHold)
	{
		car_direction = 1;
	}

	//ã
	if (GetKeyInputState(KEY_INPUT_W) == eHold)
	{
		car_direction = 2;
	}

	//‰º
	if (GetKeyInputState(KEY_INPUT_S) == eHold)
	{
		car_direction = 3;
	}

	//Ô‚ÌŒü‚«‚Æ‰æ‘œ‚Ì•ªŠò
	switch (car_direction)
	{
	case 1:
		car_x++;
		car_animation = car_image[0];
		break;
	case 2:
		car_y--;
		car_animation = car_image[1];
		break;
	case 3:
		car_y++;
		car_animation = car_image[1];
		break;
	default:
		car_animation = car_image[0];
		break;
	}

	
}

void CarDraw(void)
{
	DrawRotaGraph(car_x, car_y, 1.0, 0.0, car_animation, TRUE);
}