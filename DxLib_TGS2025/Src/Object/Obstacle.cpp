#include "Obstacle.h"
#include "Player.h"
#include "DxLib.h"
#include <math.h>

#define ITEM_NUM	(9)		//アイテムの要素

void ObstacleAnimationControl(const Player* player);

Obstacle obstacle[D_OBSTACLE_MAX];
int obstacle_images[7];
int item_images[1];
int oanimation_count;
int oanimation_num;

//障害物の初期化
void ObstacleManagerInit(void)
{
	//スライムの画像読み込み
	LoadDivGraph("Resource/Images/slime.png", D_OBS_ANIM_MAX, D_OBS_ANIM_MAX, 1, 64, 64, obstacle_images);
	LoadDivGraph("Resource/Images/item.png", 1, 1, 1, 1152, 648, item_images);

	//アニメーションの設定
	oanimation_count = 0;
	oanimation_num = 0;

	//障害物を１０個分
	for (int i = 0; i < D_OBSTACLE_MAX - 1; i++)
	{
		//初期設定
		//スライム
		obstacle[i].is_active = FALSE;							//有効状態
		obstacle[i].position.x = 1280.0f + 130.0f;				//初期位置（X)
		obstacle[i].position.y = 600.0f;						//初期位置（Y）
		obstacle[i].box_size.x = 60.0f;							//矩形の大きさ（X)
		obstacle[i].box_size.y = 60.0f;							//矩形の大きさ（Y)
		obstacle[i].image = obstacle_images[oanimation_num];	//画像の切り替え
	}
	//アイテム
	obstacle[ITEM_NUM].is_active = FALSE;
	obstacle[ITEM_NUM].position.x = 1280.0f + 130.0f;
	obstacle[ITEM_NUM].position.y = 300.0f;
	obstacle[ITEM_NUM].box_size.x = 60.0f;
	obstacle[ITEM_NUM].box_size.y = 60.0f;
	obstacle[ITEM_NUM].image = item_images[0];
}

//障害物の更新
void ObstacleManagerUpdate(void)
{
	ObstacleAnimationControl(GetPlayer());

	for (int i = 0; i < D_OBSTACLE_MAX; i++)
	{
		if (obstacle[i].is_active == TRUE)
		{
			obstacle[i].position.x -= GetPlayer()->velocity.x;
			if (obstacle[i].position.x <= -64.0f)
			{
				obstacle[i].is_active = FALSE;
				if (GetRand(1) == 1)
				{
					obstacle[i].position.x = 1280.0f + 130.0f;
				}
				{
					obstacle[i].position.x = 1280.0f + 1000.0f;
				}
			}
		}
	}
}

//障害物の描画
void ObstacleManagerDraw(void)
{
	for (int i = 0; i < D_OBSTACLE_MAX - 1; i++)
	{
		if (obstacle[i].is_active == TRUE)
		{
			float enemy_x = obstacle[i].position.x;
			float enemy_y = obstacle[i].position.y;
			int img = obstacle[i].image;
			DrawRotaGraphF(enemy_x, enemy_y, 1.2f, 0.0, img, TRUE);
		}
	}
	if (obstacle[ITEM_NUM].is_active == TRUE)
	{
		float item_x = obstacle[ITEM_NUM].position.x;
		float item_y = obstacle[ITEM_NUM].position.y;
		int img9 = obstacle[ITEM_NUM].image;
		DrawRotaGraphF(item_x, item_y, 0.4f, 0.0, img9, TRUE);
	}
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
	oanimation_count++;
	if (obstacle[0].is_active == FALSE)
	{
		if (GetRand(80) == 0)
		{
			obstacle[0].is_active = TRUE;
		}
	}
	if (obstacle[1].is_active == FALSE)
	{
		if (GetRand(15) == 1)
		{
			obstacle[1].is_active = TRUE;
		}
	}
	if (player->situation != 2)
	{
		if (obstacle[9].is_active == FALSE)
		{
			if (GetRand(100) == 1)
			{
				obstacle[9].is_active = TRUE;
			}
		}
	}
	if (oanimation_count > 5)
	{
		//次の画像番号を設定
		oanimation_count = 0;
		oanimation_num = ++oanimation_num % D_OBS_ANIM_MAX;
	}
	for (int i = 0; i < D_OBSTACLE_MAX - 1; i++)
	{
		obstacle[i].image = obstacle_images[oanimation_num];
	}
}
