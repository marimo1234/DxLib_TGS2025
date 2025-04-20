#pragma once

enum eWoodRockState // Hit数の列挙
{
	eHit0,
	eHit1,
	eHit2,
	eHit3,
};

void WoodRockInit(void);
void WoodRockUpdate(void);
void WoodRockDraw(void);

void WoodAnimation(void);//木のアニメーション