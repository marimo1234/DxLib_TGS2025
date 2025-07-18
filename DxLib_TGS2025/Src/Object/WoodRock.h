#pragma once

#include "../Utility/Geometry.h"

#define WOODROCK_MAX (80)


enum eWoodRockState // Hit数の列挙
{
	eHit0,
	eHit1,
	eHit2,
	eHit3,
	eHitEnd
};

struct Wood
{
	float position_x[12][7];
	float position_y[12][7];
	int item_num;
	int image[4];
	int animation[12][7];
	int hit_count[12][7];
	bool hit_flag[12][7];
	int count_x;
	int count_y;
	bool delete_flag[12][7];

	

	bool move_flag[12][7];
	int move_count[12][7];
	float add_y[12][7];

	int fps[12][7];

	int effect_image[5];
	bool effect_flag;
	int effect_num;
	int effect_count;
	int break_wood;
	int add_anim_x[12][7];
	int sway_anim[12][7];

	int put_effect_image[7];
	bool put_effect_flag[12][7];
	int put_effect_num[12][7];
	int put_effect_count[12][7];
};

struct Rock
{
	float position_x[12][7];
	float position_y[12][7];
	int item_num;
	int image[4];
	int itemnum_bg_image;
	int animation[12][7];
	int hit_count[12][7];
	bool hit_flag[12][7];
	int count_x;
	int count_y;
	bool delete_flag[12][7];

	bool move_flag[12][7];
	int move_count[12][7];
	float add_y[12][7];

	int fps[12][7];

	int effect_image[5];
	bool effect_flag;
	int effect_num;
	int effect_count;
	int break_rock;

	int put_effect_image[7];
	bool put_effect_flag[12][7];
	int put_effect_num[12][7];
	int put_effect_count[12][7];
};

struct WoodRock_SE
{
	int swing;
};

void WoodRockInit(void);
void WoodRockUpdate(void);
void WoodRockDraw(void);
void WoodRockResourceInit(void);

void WoodAnimation(int x,int y);//木のアニメーション
void RockAnimation(int x, int y);//岩のアニメーション

const Wood* GetWood(void);
const Rock* GetRock(void);

void WoodRockItemCount(void);

void WoodRockReset(void);
void WoodMove(int x, int y);
void RockMove(int x, int y);
void WR_Delete_Flag(void);
void WoodEffect(int x, int y);
void RockEffect(int x, int y);
void WoodRockEffectDraw(void);
void PutRockEffect(int x, int y);
void SwayWoodAnim(int x, int y);




