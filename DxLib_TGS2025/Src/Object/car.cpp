#include "DxLib.h"
#include "car.h"
#include "../Utility/InputManager.h"
#include"../Scene/InGame/InGameScene.h"
#include"../Object/map.h"


//int car_direction = 0;

int x=0;
int y=0;
void CarStart(const InGame* ingame);
void CarStartPotion(const CreateStage* create);

Car car;

void CarStartPotion(const CreateStage* create)
{
	car.position.x = create->beside * 106;
	car.position.y = create->vertical * 102;
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
	CarStart(GetInGame());

	if (car.start == true)
	{
		car.animation = car.image[0];
		car.position.x += 0.05;

		if (car.position.x > 690.2f)
		{
			car.position.x = 540.0f;
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
	car.position.x = 540.0f;
	car.position.y = 380.0f;
}