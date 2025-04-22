#pragma once

#include "../SceneType.h"

//何ステージかの判断
enum eStage
{
	eOne,
	eTwo,
	eThree,
	eFour,
	eFive
};
//ゲームのスタートとステージナンバーの構造体
struct Start
{
	int GameStart;
	int StageNumber;
};

void StarButton();
const Start* GetStart(void);
void InGameSceneInit(void);
eSceneType InGameSceneUpdate(void);
void InGameSceneDraw(void);