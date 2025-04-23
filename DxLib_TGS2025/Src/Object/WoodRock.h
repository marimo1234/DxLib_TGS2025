#pragma once

#include "../Utility/Geometry.h"
#include"../Scene/InGame/InGameScene.h"

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
};

struct Rock
{
	Vector2D position;
	int item_num;
};

void WoodRockInit(void);
void WoodRockUpdate(void);
void WoodRockDraw(void);

void WoodAnimation(void);//木のアニメーション
void RockAnimation(void);//岩のアニメーション

const Wood* GetWood(void);
const Rock* GetRock(void);

void WoodRockStart(const Start* start);
