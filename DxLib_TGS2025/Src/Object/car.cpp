#include "DxLib.h"
#include "car.h"

int car_image[2] = {};

void CarInit(void)
{
	car_image[0] = LoadGraph("Resource/images/left_car.png");
	car_image[1] = LoadGraph("Resource/images/front_car.png");
}

void CarManagerUpdate(void)
{

}

void CarDraw(void)
{
	DrawRotaGraph(300, 300, 1.0, 0.0, car_image[0], TRUE);
	DrawRotaGraph(380, 300, 1.0, 0.0, car_image[1], TRUE);
}