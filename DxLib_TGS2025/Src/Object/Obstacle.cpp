#include "Obstacle.h"
#include "DxLib.h"
#include "WoodRock.h"
#include "../Utility/InputManager.h"
#include"../Utility/PadInputManager.h"
#include "../Object/Tool.h"
#include "../Object/Map.h"
#include "../Object/Cursor.h"
#include "../Object/Car.h"
#include "../Object/Goal.h"
#include"../Scene/InGame/InGameScene.h"

#include <math.h>

#define OBSTACLE_TROUT_LENGTH (80)

void ObstacleAnimationControl(const Cursor* cursor);

Obstacle obstacle[D_OBSTACLE_MAX];
Mole mole;
Lake lake;

//	モグラの処理スタート
void MoleStart(const InGame* ingame, const Goal* goal, const GameOver* gameover, const Car* car);
//　岩を置くフラグ
void MolePutRockFlag(const CreateStage* stage);
// 岩を置く警告
void MolePutWarnDraw(const CreateStage* stage);
//　ランダムに向く方向を決める
void MoleRandomDirection(const CreateStage* stage);
//　初期化
void MoleInit(const CreateStage* stage);
//　ステージ番号の取得と置ける範囲の指定
void GetMoleStageNum(const InGame* ingame);


int obstacle_images[7];
int item_images[1];

//障害物の初期化
void ObstacleManagerInit(void)
{
	//モグラの初期化
	MoleInit(GetStage());
	//ステージ番号の取得と置ける範囲の指定
	GetMoleStageNum(GetInGame());

	mole.start = false;
	mole.menu_flag = false;
	mole.operable_flag = false;
	mole.warn_flag = false;

}

void ObstacleManagerResourceInit(void)
{
	LoadDivGraph("Resource/images/mole_animation.png", 4, 4, 1, 80, 80, mole.image);
	LoadDivGraph("Resource/images/mole_animation1.png", 4, 4, 1, 80, 80, mole.rock1_image);
	LoadDivGraph("Resource/images/mole_animation2.png", 4, 4, 1, 80, 80, mole.rock2_image);

	mole.warn_image = LoadGraph("Resource/images/mole_warn_color.png");

	lake.image = LoadGraph("Resource/images/lake.png");
}
//障害物の更新
void ObstacleManagerUpdate(void)
{

	MoleStart(GetInGame(),GetGoal(),GetGameOver(),GetCar());
	
	if (mole.start == true && mole.menu_flag == false && mole.operable_flag == true)
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
	if (mole.warn_flag == true && mole.operable_flag == true)
	{
		MolePutWarnDraw(GetStage());
	}
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
void MoleStart(const InGame* ingame, const Goal* goal, const GameOver* gameover, const Car* car)
{
	if (ingame->start == true&& ingame->menu_flag == false && ingame->mitibiki_flag ==false)
	{
		mole.start = true;
		mole.operable_flag = true;
	}
	else if(ingame->start == false && ingame->menu_flag == false)
	{
		mole.start = false;
	}

	if (car->direction == eStop || car->goal_flag == true||ingame->mitibiki_flag==true||
		goal->print_flag == true || gameover->image_flag == true )
	{
		mole.operable_flag = false;
	}
	mole.menu_flag = ingame->menu_flag;

}

//モグラの向きをランダムで変える
void MoleRandomDirection(const CreateStage* stage)
{
	mole.image_count++;

	//　ランダム方向に向く
	if (mole.image_count == 120)
	{
		for (int i = 0; i < stage->mole_count; i++)
		{
			mole.image_num[stage->mole_x[i]][stage->mole_y[i]] = GetRand(3);//ランダム方向を格納
			mole.animation[stage->mole_x[i]][stage->mole_y[i]] = mole.image[mole.image_num[stage->mole_x[i]][stage->mole_y[i]]];
			mole.warn_flag = true;// マスを赤くする警告
		}

	}
	//　手を挙げるアニメーション
	if (mole.image_count / 60 > 2)
	{
		for (int i = 0; i < stage->mole_count; i++)
		{
			mole.animation[stage->mole_x[i]][stage->mole_y[i]] = mole.rock1_image[mole.image_num[stage->mole_x[i]][stage->mole_y[i]]];
		}
	}
	//　岩を持つアニメーション
	if (mole.image_count / 60 > 3)
	{
		for (int i = 0; i < stage->mole_count; i++)
		{
			mole.animation[stage->mole_x[i]][stage->mole_y[i]] = mole.rock2_image[mole.image_num[stage->mole_x[i]][stage->mole_y[i]]];
		}
	}
	// アニメーションを戻して岩を置く
	if (mole.image_count / 60 > 4)
	{
		MolePutFlagReset();
		for (int i = 0; i < stage->mole_count; i++)
		{
			mole.animation[stage->mole_x[i]][stage->mole_y[i]] = mole.image[mole.image_num[stage->mole_x[i]][stage->mole_y[i]]];
			mole.warn_flag = false;// マスを赤くする警告
		}
		MolePutRockFlag(GetStage());
		mole.image_count = 0;

	}
}

//モグラのリセット
void MoleReset(void)
{
	mole.start = false;
	mole.menu_flag = false;
	mole.operable_flag = false;
	mole.warn_flag = false;
	mole.image_count = 0;

	MoleInit(GetStage());
	GetMoleStageNum(GetInGame());
}

//　石を置くフラグのリセット
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

//　岩を置くフラグ
void MolePutRockFlag(const CreateStage* stage)
{
	for (int i = 0; i < stage->mole_count; i++)
	{

		switch (mole.image_num[stage->mole_x[i]][stage->mole_y[i]])
		{
		case 0://　下
			if (stage->mole_y[i] != mole.rock_y_max && stage->array[stage->mole_x[i]][stage->mole_y[i] + 1] == 0)
			{
				mole.put_rock_flag[stage->mole_x[i]][stage->mole_y[i] + 1] = true;
			}
			break;
		case 1://　上
			if (stage->mole_y[i] != mole.rock_y_min && stage->array[stage->mole_x[i]][stage->mole_y[i] - 1] == 0)
			{
				mole.put_rock_flag[stage->mole_x[i]][stage->mole_y[i] - 1] = true;
			}
			break;
		case 2://　左
			if (stage->mole_x[i] != mole.rock_x_min && stage->array[stage->mole_x[i] - 1][stage->mole_y[i]] == 0)
			{
				mole.put_rock_flag[stage->mole_x[i] - 1][stage->mole_y[i]] = true;
			}
			break;
		case 3://　右
			if (stage->mole_x[i] != mole.rock_x_max && stage->array[stage->mole_x[i] + 1][stage->mole_y[i]] == 0)
			{
				mole.put_rock_flag[stage->mole_x[i] + 1][stage->mole_y[i]] = true;
			}
			break;
		default:
			break;
		}

	}

}

void MolePutWarnDraw(const CreateStage* stage)
{

	for (int i = 0; i < stage->mole_count; i++)
	{
		switch (mole.image_num[stage->mole_x[i]][stage->mole_y[i]])
		{
		case 0://　下
			if (stage->mole_y[i] != mole.rock_y_max && stage->array[stage->mole_x[i]][stage->mole_y[i] + 1] == 0)
			{
				DrawRotaGraph(stage->mole_x[i] * OBSTACLE_TROUT_LENGTH + 200, (stage->mole_y[i] + 1) * OBSTACLE_TROUT_LENGTH + 120, 1.0, 0.0, mole.warn_image, TRUE);
			}
			break;
		case 1://　上
			if (stage->mole_y[i] != mole.rock_y_min && stage->array[stage->mole_x[i]][stage->mole_y[i] - 1] == 0)
			{
				DrawRotaGraph(stage->mole_x[i] * OBSTACLE_TROUT_LENGTH + 200, (stage->mole_y[i] - 1) * OBSTACLE_TROUT_LENGTH + 120, 1.0, 0.0, mole.warn_image, TRUE);
			}
			break;
		case 2://　左
			if (stage->mole_x[i] != mole.rock_x_min && stage->array[stage->mole_x[i] - 1][stage->mole_y[i]] == 0)
			{
				DrawRotaGraph((stage->mole_x[i] - 1) * OBSTACLE_TROUT_LENGTH + 200, stage->mole_y[i] * OBSTACLE_TROUT_LENGTH + 120, 1.0, 0.0, mole.warn_image, TRUE);
			}
			break;
		case 3://　右
			if (stage->mole_x[i] != mole.rock_x_max && stage->array[stage->mole_x[i] + 1][stage->mole_y[i]] == 0)
			{
				DrawRotaGraph((stage->mole_x[i] + 1) * OBSTACLE_TROUT_LENGTH + 200, stage->mole_y[i] * OBSTACLE_TROUT_LENGTH + 120, 1.0, 0.0, mole.warn_image, TRUE);
			}
			break;
		default:
			break;
		}
	}
}

//　モグラ変数の初期化
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

//ステージ番号の取得と置ける範囲の指定
void GetMoleStageNum(const InGame* ingame)
{
	switch (ingame->stage_num)
	{
	case eOne:
		mole.rock_x_min = 1;
		mole.rock_x_max = 9;
		mole.rock_y_min = 3;
		mole.rock_y_max = 4;
		break;
	default:
		mole.rock_x_min = 0;
		mole.rock_x_max = 11;
		mole.rock_y_min = 0;
		mole.rock_y_max = 6;
		break;
	}
}
