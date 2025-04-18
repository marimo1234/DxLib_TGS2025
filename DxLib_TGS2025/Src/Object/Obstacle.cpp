#include "Obstacle.h"
#include "Player.h"
#include "DxLib.h"
#include <math.h>

#define ITEM_NUM	(9)		//アイテムの要素

void ObstacleAnimationControl(const Player* player);

Obstacle obstacle[D_OBSTACLE_MAX];
int obstacle_images[7];
int item_images[1];

//障害物の初期化
void ObstacleManagerInit(void)
{
	//スライムの画像読み込み
	/*LoadDivGraph("Resource/Images/slime.png", D_OBS_ANIM_MAX, D_OBS_ANIM_MAX, 1, 64, 64, obstacle_images);
	LoadDivGraph("Resource/Images/item.png", 1, 1, 1, 1152, 648, item_images);*/
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
const Obstacle* GetObstacle(int num)
{
	if (0 <= num && num < D_OBSTACLE_MAX)
	{
		return &obstacle[num];
	}

	return obstacle;
}

//障害物のスポーンが有効か
void ObstacleAnimationControl(const Player* player)
{
	
}
