#pragma once

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

	int cnt;
	int num_img[6];
	int num_idx;
	int start_img;
	int start_cnt;

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
	int tutoriallog_selectA;
	int itemtutorial1;
	int itemtutorial2;
	int itemtutorial3;
	int itemtutorial4;

	int tutorial_log1;
	int tutorial_log2;
	int tutorial_log3;
	int tutorial_log4;
	int tutorial_log5;
	int tutorial_log6;
	int tutorial_log7;
	int tutorial_log8;
	int tutorial_log9;
	int tutorial_log10;
	int tutorial_log11;
	int tutorial_log12;
	int itemtutorial_num = 1;
	int brakestoneanimetion1;
	int brakestoneanimetion2;
	int brakestoneanimetion3;
	int brakestoneanimetion4;
	int brakestoneanimetion5;
	int brakestoneanimetion6;
	int brakestoneanimetion7;
	int brakestoneanimetioncount = 0;
	int makeroda1;
	int makeroda2;
	int makerodacount = 0;
	int putroda1;
	int putroda2;
	int putrodacount = 0;
	int brakewood1;
	int brakewood2;
	int brakewood3;
	int brakewood4;
	int brakewood5;
	int brakewood6;
	int brakewoodcount = 0;
	int putbridge1;
	int putbridgecount = 0;
	int menuanimationflag;
	int woodtutorial = false;
	int woodrodamake1;
	int woodrodamake2;
	int woodrodamakeswitch = false;
	int madewoodswitch = false;
	int itembaraxcount;
	int itembarwoodroadcount;
	int itembarbridgecount;
	int tutorial_count;
	int itembarcoment1;
	int itembarcoment2;
	int itembarcoment3;
	int itembarcoment4;
	int itemcoment_switch = false;
	int itembarcomentswitch = false;
	int warntutorial;
	int warntutorial_flag=true;
	int warntutorial_flag_public = false;
};

struct InGame_Sound
{
	int bgm;
	int gameover;
	int clear;
	int pose;
	int select_move;
	int decision;
	int count;
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

//カウントダウン
void InGameStartCount(void);
//カウントダウンアニメーション
void InGameCountAnim(void);
//カウントダウン後のスタートテキストの描画
void StartTextDraw(void);



//void StageChange(const Goal* goal);
