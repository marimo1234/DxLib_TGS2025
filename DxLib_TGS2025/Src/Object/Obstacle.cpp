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

#define PUT_ROCK_Y_MIN (0)
#define PUT_ROCK_Y_MAX (6)
#define PUT_ROCK_X_MIN (0)
#define PUT_ROCK_X_MAX (11)

void ObstacleAnimationControl(const Cursor* cursor);

Obstacle obstacle[D_OBSTACLE_MAX];
Mole mole;
Lake lake;

void MoleStart(const InGame* ingame);
void MolePutRockFlag(const CreateStage* stage);
void MoleRandomDirection(const CreateStage* stage);
void MoleInit(const CreateStage* stage);

int obstacle_images[7];
int item_images[1];

//障害物の初期化
void ObstacleManagerInit(void)
{

	for (int i = 0; i < 3; i++)
	{
		mole.image[i] = -1;
	}

	MoleInit(GetStage());
	
	mole.image[0] = LoadGraph("Resource/images/mole_down.png");
	mole.image[1] = LoadGraph("Resource/images/mole_up.png");
	mole.image[2] = LoadGraph("Resource/images/mole_left.png");
	mole.image[3] = LoadGraph("Resource/images/mole_right.png");
	lake.image = LoadGraph("Resource/images/lake.png");

	mole.start = false;
	mole.menu_flag = false;
}

//障害物の更新
void ObstacleManagerUpdate(void)
{

	MoleStart(GetInGame());
	
	if (mole.start == true&&mole.menu_flag==false)
	{
		//石を置くフラグ
		MolePutFlagReset();        //trueにする関数より前に置けば1フレーム後にfalseになってくれるかも（検証中）
		//モグラの向きをランダムで変える
		MoleRandomDirection(GetStage());
		
	}
	else if(mole.start == false && mole.menu_flag == false)
	{
		MoleReset();
	}
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
	if (ingame->start == true&& ingame->menu_flag == false)
	{
		mole.start = true;
	}
	else if(ingame->start == false && ingame->menu_flag == false)
	{
		mole.start = false;
	}
	mole.menu_flag = ingame->menu_flag;

}

//モグラの向きをランダムで変える
void MoleRandomDirection(const CreateStage* stage)
{
	mole.image_count++;

	if (mole.image_count / 60 > 4)
	{
		for (int i = 0; i < stage->mole_count; i++)
		{
			MolePutFlagReset();
			mole.image_num[stage->mole_x[i]][stage->mole_y[i]] = GetRand(3);
			mole.animation[stage->mole_x[i]][stage->mole_y[i]] = mole.image[mole.image_num[stage->mole_x[i]][stage->mole_y[i]]];

			MolePutRockFlag(GetStage());

			mole.image_count = 0;

		}
	}
}

//モグラのリセット
void MoleReset(void)
{
	mole.start = false;
	mole.menu_flag = false;
	mole.image_count = 0;

	MoleInit(GetStage());
	
}

//石を置くフラグのリセット
void MolePutFlagReset(void)
{
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			if (mole.put_rock_flag[i][j] == true)
			{
				mole.put_rock_flag[i][j] = false;
			}
		}
	}
}

//石を置く条件
//最初の方向のマスがtrueになるのをどうにかしないといけない
void MolePutRockFlag(const CreateStage* stage)
{
	for (int i = 0; i < stage->mole_count; i++)
	{

		switch (mole.image_num[stage->mole_x[i]][stage->mole_y[i]])
		{
		case 0:
			if (stage->mole_y[i] != PUT_ROCK_Y_MAX && stage->array[stage->mole_x[i]][stage->mole_y[i] + 1] == 0)
			{
				mole.put_rock_flag[stage->mole_x[i]][stage->mole_y[i] + 1] = true;
			}
			break;
		case 1:
			if (stage->mole_y[i] != PUT_ROCK_Y_MIN && stage->array[stage->mole_x[i]][stage->mole_y[i] - 1] == 0)
			{
				mole.put_rock_flag[stage->mole_x[i]][stage->mole_y[i] - 1] = true;
			}
			break;
		case 2:
			if (stage->mole_x[i] != PUT_ROCK_X_MIN && stage->array[stage->mole_x[i] - 1][stage->mole_y[i]] == 0)
			{
				mole.put_rock_flag[stage->mole_x[i] - 1][stage->mole_y[i]] = true;
			}
			break;
		case 3:
			if (stage->mole_x[i] != PUT_ROCK_X_MAX && stage->array[stage->mole_x[i] + 1][stage->mole_y[i]] == 0)
			{
				mole.put_rock_flag[stage->mole_x[i] + 1][stage->mole_y[i]] = true;
			}
			break;
		default:
			break;
		}

	}

}

void MoleInit(const CreateStage* stage)
{
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			if (stage->array[i][j] == 3)
			{
				mole.image_num[i][j] = 0;
				mole.animation[i][j] = mole.image[mole.image_num[i][j]];
			}
			else
			{
				mole.image_num[i][j] = -1;
				mole.animation[i][j] = -1;
			}
			mole.put_rock_flag[i][j] = false;
		}
	}
}


