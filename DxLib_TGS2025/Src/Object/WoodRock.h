#pragma once

#include "../Utility/Geometry.h"

#define WOODROCK_MAX (80)


enum eWoodRockState // Hit数の列挙
{
	eHit0,
	eHit1,
	eHit2,
	eHit3,
};

struct Wood
{
	Vector2D position;
	int item_num;
	int image[4];
	int animation[12][7];
	int hit_count[12][7];
	bool hit_flag[12][7];
	int count_x;
	int count_y;
	bool delete_flag[12][7];
	bool move_flag;

};

struct Rock
{
	Vector2D position;
	int item_num;
	int image[4];
	int animation[12][7];
	int hit_count[12][7];
	bool hit_flag[12][7];
	int count_x;
	int count_y;
	bool delete_flag[12][7];
	bool move_flag;
	
};


void WoodRockInit(void);
void WoodRockUpdate(void);
void WoodRockDraw(void);

void WoodAnimation(void);//木のアニメーション
void RockAnimation(void);//岩のアニメーション

const Wood* GetWood(void);
const Rock* GetRock(void);

void WoodRockItemCount(void);

void WoodRockReset(void);
void WoodMove(void);
void RockMove(void);
void WR_Delete_Flag(void);



