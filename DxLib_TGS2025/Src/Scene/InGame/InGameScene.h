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
	bool next_stage_flag;
};


//ステージ生成の構造体
struct CreateStage
{
	int stage[12][7];		//ステージ配列
	int stage_beside;		//横
	int stage_vertical;		//縦
	int stage_kinds;		//ステージの種類
	int stage_x;
	int stage_y;
};

void InGameSceneInit(void);
eSceneType InGameSceneUpdate(void);
void InGameSceneDraw(void);

const InGame* GetInGame(void);

void GameStart();
void StageChange(void);
void StageRoad(void);
void StageCreate(void);
//void StageChange(const Goal* goal);