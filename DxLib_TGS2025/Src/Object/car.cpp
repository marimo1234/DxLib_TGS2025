#include "DxLib.h"
#include "car.h"
#include "../Utility/InputManager.h"
#include"../Scene/InGame/InGameScene.h"
#include"../Object/map.h"


//int car_direction = 0;


int detict[12][7];
void CarStart(const InGame* ingame);
void CarDetectPotion(const CreateStage* create);

Car car;

void CarDetectPotion(const CreateStage* create)
{
	
	
	if (create->array[car.x][car.y] == 4)
	{
		DrawFormatString(930, 50, GetColor(255, 255, 255), "%d", create->array[car.x][car.y]);
	}
	if (create->array[car.x][car.y] != 4)
	{
		DrawFormatString(930, 50, GetColor(255, 255, 255), "死んだ" );
		car.start = false;
	}
}

void CarInit(void)
{
	
	car.position.x;
	car.position.y;
	/*car_direction = 0;*/

	car.image[0] = LoadGraph("Resource/images/left_car.png");
	car.image[1] = LoadGraph("Resource/images/front_car.png");

	car.start = false;
}

void CarManagerUpdate(void)
{
	car.x = ((car.position.x-200) / 80) ;
	car.y = car.position.y / 100;
	CarStart(GetInGame());
	

	if (car.start == true)
	{
		car.animation = car.image[0];
		car.position.x += 0.1;

		if (car.position.x > 690.2f)
		{
			car.position.x = 440.0f;
		}

		
	}
	else
	{
		CarReset();
	}

}

void CarDraw(void)
{
		DrawRotaGraph(car.position.x, car.position.y, 1.0, 0.0, car.animation, TRUE);
		DrawFormatString(930, 300, GetColor(255, 255, 255), "%f",car.position.x);
		DrawFormatString(930, 200, GetColor(255, 255, 255), "%f", car.position.y);
		DrawFormatString(930, 100, GetColor(255, 255, 255), "%d", car.x);
		CarDetectPotion(GetStage());
}


//車の処理をスタートするフラグ
void CarStart(const InGame* ingame)
{
	if (ingame->start == true)
	{
		car.start = true;
	}
	else
	{
		car.start = false;
	}
	
}

const Car* GetCar(void)
{
	return &car;
}

void CarReset(void)
{
	car.position.x = 440.0f;
	car.position.y = 360.0f;
}