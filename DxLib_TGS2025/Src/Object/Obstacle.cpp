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
void MolePutRock(const CreateStage* stage);

int obstacle_images[7];
int item_images[1];

//障害物の初期化
void ObstacleManagerInit(void)
{

	for (int i = 0; i < 3; i++)
	{
		mole.image[i] = -1;
	}


	for (int j = 0; j < 12; j++)
	{
		for (int i = 0; i < 7; i++)
		{
			mole.image_num[i][j] = 0;
			mole.put_rock_flag[i][j] = false;
			mole.animation[i][j] = mole.image[mole.image_num[i][j]];
		}
	}


	mole.image[0] = LoadGraph("Resource/images/mole_down.png");
	mole.image[1] = LoadGraph("Resource/images/mole_up.png");
	mole.image[2] = LoadGraph("Resource/images/mole_left.png");
	mole.image[3] = LoadGraph("Resource/images/mole_right.png");
	lake.image = LoadGraph("Resource/images/lake.png");

	mole.start = false;
}

//障害物の更新
void ObstacleManagerUpdate(void)
{

	MoleStart(GetInGame());
	/*MoleRandomDirection();*/

	
	if (mole.start == true)
	{
		//石を置くフラグ
		MolePutFlagReset();        //trueにする関数より前に置けば1フレーム後にfalseになってくれるかも（検証中）
		//モグラの向きをランダムで変える
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

//モグラの向きをランダムで変える
void MoleRandomDirection(void)
{
	mole.image_count++;

	if (mole.image_count > 180)
	{
		mole.image_num[0][0] = GetRand(3);
		mole.put_rock_flag[0][0] = true;
		mole.image_count = 0;
		
	}
	mole.animation[0][0] = mole.image[mole.image_num[0][0]];

}

//モグラのリセット
void MoleReset(void)
{
	mole.start = false;
	mole.image_count = 0;


	for (int j = 0; j < 12; j++)
	{
		for (int i = 0; i < 7; i++)
		{
			mole.image_num[i][j] = 0;
			mole.put_rock_flag[i][j] = false;
			mole.animation[i][j] = mole.image[mole.image_num[i][j]];
		}
	}

}

//石を置くフラグのリセット
void MolePutFlagReset(void)
{
	if (mole.put_rock_flag[0][0] == true)
	{
		mole.put_rock_flag[0][0] = false;
	}
}

//石を置く条件
void MolePutRock(const CreateStage* stage)
{
	switch (mole.image_num[0][0])
	{
	case 0:
		break;
	}
}


