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
	bool manual_open;
	int manual_image;
	int space;
	int back;
	bool menu_flag;
	int menu_num;
	int menu_image;
	int menu_char_image[6];
	int menu_cursor;
	float menu_cursor_x;
    float menu_cursor_y;
	float char_extrate[6];

	bool goalmenu_flag;
	int goalmenu_num;
	int goalmenu_image;
	float goalmenu_cursor_x;
	float goalmenu_cursor_y;

	bool goalselect_flag;

	bool menu_manual_flag;
    int  menu_manual_image;

	bool gameover_se_flag;

	int tutoria_log;
	int tutoria_log_num;
	int mitibikikun;
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

const InGame* GetInGame(void);

void GameStart();
void StageChange(void);

void ChangeCharExtrate(void);
void GoalSelectFlagReset(void);
void MenuDraw(void);
void GoalSelectMenuDraw(void);
void Play_InGameBgm(void);
void Stop_InGameBgm(void);
void Tutorial(void);

//void StageChange(const Goal* goal);