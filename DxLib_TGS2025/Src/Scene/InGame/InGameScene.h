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
	int manual_open;
	int manual_image;
	int space;
	int back;
	bool menu_flag;
	int menu_num;
	int menu_image;
	int menu_char_image[5];
	int menu_cursor;
	float menu_cursor_x;
    float menu_cursor_y;
};


void InGameSceneInit(void);
eSceneType InGameSceneUpdate(void);
void InGameSceneDraw(void);

const InGame* GetInGame(void);

void GameStart();
void StageChange(void);
void InGameMenu(void);
//void StageChange(const Goal* goal);