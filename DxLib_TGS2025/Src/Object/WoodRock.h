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

struct WoodRock
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

	int effect_image[6];
	bool effect_flag;
	int effect_num;
	int effect_count;
	int break_se;
	int add_anim_x[12][7];
	int sway_anim[12][7];

	int put_effect_image[7];
	bool put_effect_flag[12][7];
	int put_effect_num[12][7];
	int put_effect_count[12][7];
};

struct WoodRock_SE
{
	int swing;
};

enum WoodRockType { TYPE_WOOD, TYPE_ROCK };

void WoodRockInit(void);
void WoodRockUpdate(void);
void WoodRockDraw(void);
void WoodRockResourceInit(void);

// ヒット状態
void WoodRockHitState(WoodRock* wr, int x, int y);
void WoodRockHit(WoodRock* wr, int x, int y, int imgidx, int next_state);
void WoodRockHit3(WoodRock* wr, int x, int y);

const WoodRock* GetWood(void);
const WoodRock* GetRock(void);

void WoodRockReset(void);
void WoodMove(int x, int y);
void RockMove(int x, int y);
void WR_Delete_Flag(void);
void WoodEffect(int x, int y);
void RockEffect(int x, int y);
void PutRockEffect(int x, int y);
void PutWoodEffect(int x, int y);
void WoodRockEffectDraw(void);
void SwayWoodAnim(int x, int y);
void SwayRockAnim(int x, int y);











