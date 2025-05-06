#include "Obstacle.h"
#include "Cursor.h"
#include "DxLib.h"
#include <math.h>

#define ITEM_NUM	(9)		//アイテムの要素

void ObstacleAnimationControl(const Cursor* cursor);

Obstacle obstacle[D_OBSTACLE_MAX];
Hole hole;
Lake lake;
int obstacle_images[7];
int item_images[1];

//障害物の初期化
void ObstacleManagerInit(void)
{
	hole.image = LoadGraph("Resource/images/hole.png");
	lake.image = LoadGraph("Resource/images/lake.png");

}

//障害物の更新
void ObstacleManagerUpdate(void)
{
	
}

//障害物の描画
void ObstacleManagerDraw(void)
{
	
}

//構造体Obstacle
const Obstacle* GetObstacle(void)
{
	return obstacle;
}

const Hole* GetHole(void)
{
	return &hole;
}

const Lake* GetLake(void)
{
	return&lake;
}

//障害物のスポーンが有効か
void ObstacleAnimationControl(const Cursor* cursor)
{
	
}
