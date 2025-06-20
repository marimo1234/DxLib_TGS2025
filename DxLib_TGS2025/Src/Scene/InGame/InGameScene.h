﻿#pragma once

#include "../SceneType.h"

//何ステージかの判断
enum eStage
{
	eOne,
	eTwo,
	eThree,
	eFour,
	eFive,
	eSix,
};

//ゲームのスタートとステージナンバーの構造体
struct InGame
{
	bool start;
	int stage_num;
	bool next_stage_flag;
	bool manual_open;
	int manual_image;
	int space;
	int back;
	bool menu_flag;
	int menu_num;
	int menu_image;
	int menu_char_image[7];
	int menu_cursor;
	float menu_cursor_x;
    float menu_cursor_y;
	float char_extrate[7];

	bool goalmenu_flag;
	int goalmenu_num;
	int goalmenu_image;
	float goalmenu_cursor_x;
	float goalmenu_cursor_y;

	bool goalselect_flag;

	bool menu_manual_flag;
    int  menu_manual_image;

	int start_button_image;

	bool gameover_se_flag;

	int tutorial_log;
	int tutorial_log_num;
	int mitibikikun;
	bool mitibiki_flag;
	int tutorial_achievements;
	int tutorial_controol_up;
	int tutorial_controol_left;
	int tutorial_controol_right;
	int tutorial_controol_down;
	int tutoriallog_select;
};

struct InGame_Sound
{
	int bgm;
	int gameover;
	int clear;
	int pose;
	int select_move;
	int decision;
	
};

void InGameSceneInit(void);
eSceneType InGameSceneUpdate(void);
void InGameSceneDraw(void);
void InGameResourceInit(void);
bool IsInGameInit();

const InGame* GetInGame(void);

void GameStart();
void StageChange(void);

void ChangeCharExtrate(void);
void GoalSelectFlagReset(void);
void MenuDraw(void);
void GoalSelectMenuDraw(void);
void Play_InGameBgm(void);
void Stop_InGameBgm(void);


//void StageChange(const Goal* goal);