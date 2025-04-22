#pragma once

#include"../Scene/InGame/InGameScene.h"
#include "../Object/Tool.h"


enum eWoodRockState // Hit数の列挙
{
	eHit0,
	eHit1,
	eHit2,
	eHit3,
};


struct WoodRock
{
	int item_number;
};
void WoodRockInit(void);
void WoodRockUpdate(void);
void WoodRockDraw(void);

void WoodAnimation(void);//木のアニメーション
void RockAnimation(void);//岩のアニメーション

const WoodRock* GetWoodRock(void);
void WoodRockStart(const Start* start);

void ItemSlotCheck(const Tool* tool);
