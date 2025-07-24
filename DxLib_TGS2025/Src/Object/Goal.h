#pragma once

#include "../Utility/Geometry.h"

struct Goal
{
	Vector2D position;
	bool flag;
	bool start;
	bool menu_flag;
	int print_image;
	int flag_image;
	bool print_flag;
	int count;
	int print_count;
	int rand_handle;			//ランダムで受け取る値
	float firework_x[3];		//花火のｘの描画位置
	int firework_count;			//画像番号切り替えカウント
	int firework_num[3];		//花火の画像番号
	int old_num[3];				//1フレーム前の画像番号
	float add_y[3];				//花火のｙ座標の移動
	float firework_rate[3];		//花火の拡大率

	int gameover_image;
	int whiteback_image;
	int blackback_image;
	int firework_image[12];		//花火１つ目の画像
	int firework_image2[12];	//花火２つ目の画像
	int firework_image3[12];	//花火３つ目の画像

	//音
	int firework_se;
};

void GoalInit(void);
void GoalUpdate(void);
void GoalDraw(void);
void GoalReset(void);
void GoalResourceInit(void);


const Goal* GetGoal(void);