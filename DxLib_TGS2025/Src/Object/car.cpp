#include "DxLib.h"
#include "car.h"
#include "../Utility/InputManager.h"
#include"../Scene/InGame/InGameScene.h"
#include"../Object/map.h"


int time;
int old_x;
int old_y;

int detict[12][7] = {};
void CarStart(const InGame* ingame);
void CarDetectPosition(void);
void GetNextDestination(const NextDestination* destination);

Car car;
void CarInit(void)
{
	time = 0;
	car.position.x=440.0f;
	car.position.y=360.0f;
	car.direction = eRight;
	car.road_count = 0;
	car.next_count = 1;
	/*car_direction = 0;*/

	car.image[0] = LoadGraph("Resource/images/left_car.png");
	car.image[1] = LoadGraph("Resource/images/front_car.png");

	car.start = false;

	car.current_x = 3;//ステージ①の初期位置
	car.current_y = 3;
	
	//次の目的地の初期化
	for (int i = 0; i < 84; i++)
	{
		car.next_x[i] = -1;
		car.next_y[i] = -1;
	}
}

void CarManagerUpdate(void)
{
	car.x = ((car.position.x-200) / 80) ;
	car.y = ((car.position.y - 120) / 80);
	old_x = car.x;
	old_y = car.y;
	CarStart(GetInGame());
	
	if (car.start == true)
	{
		car.animation = car.image[0];
		CarMovePosition();
	}
	else
	{
		CarReset();
	}

	GetNextDestination(GetDestination());
}

void CarDraw(void)
{
		DrawRotaGraph(car.position.x, car.position.y, 1.0, 0.0, car.animation, TRUE);
		DrawFormatString(930, 300, GetColor(255, 255, 255), "%f",car.position.x);
		DrawFormatString(930, 200, GetColor(255, 255, 255), "%f", car.position.y);
		DrawFormatString(930, 100, GetColor(255, 255, 255), "%d", car.x);
		DrawFormatString(930, 50, GetColor(255, 255, 255), "%d", time);
		DrawFormatString(930, 150, GetColor(255, 255, 255), "%d", car.direction);
		if (time%800==0)
		{
			/*CarDetectPosition();*/
		}
		

		DrawFormatString(300, 350, GetColor(255, 255, 255), "%d\n%d\n%d", car.next_x[car.road_count], car.next_y[car.road_count], car.road_count);
		DrawFormatString(350, 350, GetColor(255, 255, 255), "%d\n%d\n%d", car.current_x, car.current_y, car.next_count);
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

//void CarDetectPosition(const CreateStage* create)
//{
//	DrawFormatString(630, 300, GetColor(255, 255, 255), "%d", create->array[car.x + 1][car.y]);
//	DrawFormatString(630, 200, GetColor(255, 255, 255), "%d", create->array[car.x][car.y - 1]);
//	switch (car.direction)
//	{
//	case eRight:
//		
//		if (create->array[car.x][car.y - 1] == 4)
//		{
//			car.direction = eUp;
//			old_x = car.x;
//			old_y = car.y;
//		}
//		else if (create->array[car.x][car.y + 1] == 4)
//		{
//			car.direction = eDown;
//			old_x = car.x;
//			old_y = car.y;
//		}
//		else if (create->array[car.x + 1][car.y] == 4)
//		{
//			car.direction = eRight;
//			old_x = car.x;
//			old_y = car.y;
//		}
//		else
//		{
//			car.direction = eStop;
//			old_x = car.x;
//			old_y = car.y;
//		}
//		break;
//	case eUp:
//		
//		if (create->array[car.x][car.y - 1] == 4)
//		{
//			car.direction = eUp;
//			old_x = car.x;
//			old_y = car.y;
//		}
//		else if (create->array[car.x + 1][car.y] == 4)
//		{
//			car.direction = eRight;
//			old_x = car.x;
//			old_y = car.y;
//		}
//		else
//		{
//			car.direction = eStop;
//			old_x = car.x;
//			old_y = car.y;
//		}
//		break;
//	case eDown:
//		
//		if (create->array[car.x][car.y + 1] == 4)
//		{
//			car.direction = eDown;
//			old_x = car.x;
//			old_y = car.y;
//		}
//		else if (create->array[car.x + 1][car.y] == 4)
//		{
//			car.direction = eRight;
//			old_x = car.x;
//			old_y = car.y;
//		}
//		else
//		{
//			car.direction = eStop;
//			old_x = car.x;
//			old_y = car.y;
//		}
//	default:
//		break;
//	}
//	detict[car.x][car.y] = create->array[car.x][car.y];
//
//}

void GetNextDestination(const NextDestination* destination)
{
	if (car.next_x[car.road_count] != destination->x || car.next_y[car.road_count] != destination->y)
	{
		++car.road_count;
		car.next_x[car.road_count] = destination->x;
		car.next_y[car.road_count] = destination->y;
	}
}


void CarMovePosition(void)
{
	switch (car.direction)
	{
	case eUp:
		car.position.y -= 0.1f;
		time++;
		if (car.position.y < (car.current_y) * 80.0f + 121.0f)
		{
			CarDetectPosition();
		}
		break;
	case eDown:
		car.position.y += 0.1f;
		time++;
		if (car.position.y > (car.current_y) * 80.0f + 119.0f)
		{
			CarDetectPosition();
		}
		break;
	case eRight:
		car.position.x += 0.1f;
		time++;
		if (car.position.x > (car.current_x) * 80.0f + 199.0f)
		{
			CarDetectPosition();
		}
		break;
	case eStop:
		car.position.x += 0.0f;
		car.position.y += 0.0f;
		time++;
		break;
	default:
		break;
	}
}

void CarDetectPosition(void)
{
	if (car.current_x < car.next_x[car.next_count])//関数化する//↑の条件式にそれぞれ関数を入れる
	{
		car.direction = eRight;
		car.current_x = car.next_x[car.next_count];
		car.current_y = car.next_y[car.next_count];
		car.next_count++;
	}
	else if (car.current_y > car.next_y[car.next_count])
	{
		car.direction = eUp;
		car.current_x = car.next_x[car.next_count];
		car.current_y = car.next_y[car.next_count];
		car.next_count++;
	}
	else if (car.current_y < car.next_y[car.next_count])
	{
		car.direction = eDown;
		car.current_x = car.next_x[car.next_count];
		car.current_y = car.next_y[car.next_count];
		car.next_count++;
	}
	else
	{

	}

}