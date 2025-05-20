#include "Obstacle.h"
#include "DxLib.h"
#include "WoodRock.h"
#include "../Utility/InputManager.h"
#include"../Utility/PadInputManager.h"
#include "../Object/Tool.h"
#include "../Object/Map.h"
#include "../Object/Cursor.h"
#include"../Scene/InGame/InGameScene.h"

#include <math.h>

#define ITEM_NUM	(9)		//アイテムの要素

void ObstacleAnimationControl(const Cursor* cursor);

Obstacle obstacle[D_OBSTACLE_MAX];
Mole mole;
Lake lake;

void MoleStart(const InGame* ingame);

int obstacle_images[7];
int item_images[1];

//障害物の初期化
void ObstacleManagerInit(void)
{

	for (int i = 0; i < 3; i++)
	{
		mole.image[i] = -1;
	}

	mole.image_num = 0;
	mole.image_count = 0;
	mole.image[0] = LoadGraph("Resource/images/mole_down.png");
	mole.image[1] = LoadGraph("Resource/images/mole_up.png");
	mole.image[2] = LoadGraph("Resource/images/mole_left.png");
	mole.image[3] = LoadGraph("Resource/images/mole_right.png");
	lake.image = LoadGraph("Resource/images/lake.png");

	mole.start = false;
	mole.animation = mole.image[mole.image_num];

}

//障害物の更新
void ObstacleManagerUpdate(void)
{

	MoleStart(GetInGame());
	/*MoleRandomDirection();*/

	
	if (mole.start == true)
	{
		MoleRandomDirection();
	}
	else
	{
		MoleReset();
	}
}

//障害物の描画
void ObstacleManagerDraw(void)
{
	DrawFormatString(200, 200, GetColor(255, 255, 255), "%d %d ", mole.image_count, mole.image_num);
}

//構造体Obstacle
const Obstacle* GetObstacle(void)
{
	return obstacle;
}

const Mole* GetMole(void)
{
	return &mole;
}

const Lake* GetLake(void)
{
	return&lake;
}

//障害物のスポーンが有効か
void ObstacleAnimationControl(const Cursor* cursor)
{
	
}

//処理をスタートするフラグ
void MoleStart(const InGame* ingame)
{
	if (ingame->start == true)
	{
		mole.start = true;
	}
	else
	{
		mole.start = false;
	}

}

void MoleRandomDirection(void)
{
	mole.image_count++;

	if (mole.image_count > 120)
	{
		mole.image_num = GetRand(3);
		mole.image_count = 0;
	}
	mole.animation = mole.image[mole.image_num];

}

void MoleReset(void)
{


	mole.image_num = 0;
	mole.image_count = 0;

	mole.start = false;
	mole.animation = mole.image[0];

}
