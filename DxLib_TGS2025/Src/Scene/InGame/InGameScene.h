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
struct InGame
{
	bool start;
	int stage_num;
	bool next_stage_flg;
};


void InGameSceneInit(void);
eSceneType InGameSceneUpdate(void);
void InGameSceneDraw(void);

const InGame* GetInGame(void);

void GameStart();
void StageChenge(void);
