﻿#include "InGameScene.h"
#include "../../Utility/InputManager.h"
#include "../../Object/Cursor.h"
#include "../../Object/Obstacle.h"
#include "../StageSelect/StageSelectScene.h"
#include "../../Utility/PadInputManager.h"
#include "../../Object/car.h"
#include "../../Object/WoodRock.h"
#include "../../Object/map.h"
#include "../../Object/Tool.h"
#include "../../Object/Goal.h"
#include "DxLib.h"

#include <math.h>
#include <stdlib.h>
#include<stdio.h>

#define D_SCROOL_SPEED		(200.0f)

//確認用変数　後に消します
int atr ;
int btr ;
int animetion_num;
int ingame_init_step = 0;
int is_initialized = false;

//この辺まだ使っていない
//void HitCheck(const Cursor* cursor, const Obstacle* obstacle, int index);
void PlayBgm(void);

InGame ingame;
InGame_Sound sound;

void NextStageFlag(const Goal* goal);
void NextSelectFlag(const Goal* goal);
void GameOverReset(const GameOver* gameover,const Car*car);
void GetStageNumber(const StageSelect* stageselect);
void InGameMenuUpdate(const Goal*goal,const GameOver* gameover);
void Play_Sound_Ingame(int sound, int volume);
void Play_Sound_Ingame2(int sound, int volume);
void TutorialUpdate(void);
void TutorialAchievements(const Cursor* cursor, const Rock* rock, const Wood* wood, const Tool* tool, const CreateStage* stage);
void TutorialDraw(const Goal* goal,const GameOver*gameover);
void TutorialCursor(void);




//初期化
void InGameSceneInit(void)
{
	
	//操作説明の表示
	ingame.manual_open = false;
	ingame.tutorial_log_num = 2;
	//インゲームスタートのフラグ変数
	ingame.start = false;
	//ステージ番号を取得
	GetStageNumber(GetStageSelect());
	/*ingame.stage_num = eOne;*/
	//ステージ次のステージに変更するフラグ
	ingame.next_stage_flag = false;

	ingame.menu_flag = false;
	ingame.menu_num = 0;
	ingame.menu_cursor_x=280.0f;
	ingame.menu_cursor_y = 130.0f;

	ingame.goalmenu_flag = false;
	ingame.goalmenu_num = 0;
	ingame.goalmenu_cursor_x = 280.0f;
	ingame.goalmenu_cursor_y = 300.0f;

	ingame.goalselect_flag = false;

	ingame.menu_manual_flag = false;

	ingame.gameover_se_flag = false;

	ingame.mitibiki_flag = false;
	ingame.tutorial_achievements = 1;

	for (int i = 0; i < 7; i++)
	{
		ingame.char_extrate[i] = 0.7f;
	}
	//確認用変数　後々消します
	atr = 0;
	btr = 1;
		//マップの初期化
		MapInit();
		//障害物の初期化
		ObstacleManagerInit();
		//木岩の初期化
		WoodRockInit();
		//ツールの初期化
		ToolInit();
		//車の初期化
		CarInit();
		//カーソルの初期化
		CursorInit();
		//ゴールの読み込み
		GoalInit();

}

void InGameResourceInit(void)
{
	switch (ingame_init_step)
	{
	case 0:
		//説明の後ろに表示(黒い背景）
		ingame.back = LoadGraph("Resource/images/black_back.png");
		//インゲーム前の画面
		ingame.space = LoadGraph("Resource/images/aida.png");
		//操作説明の画像
		ingame.manual_image = LoadGraph("Resource/images/manual_menu.png");
		ingame.space = LoadGraph("Resource/images/aida.png");
		//白い背景
		ingame.menu_image = LoadGraph("Resource/images/white_back.png");
		//メニューカーソル
		ingame.menu_cursor = LoadGraph("Resource/images/menu_cursor.png");
		//メニューバー画像
		ingame.menu_char_image[0] = LoadGraph("Resource/images/continue.png");
		ingame.menu_char_image[1] = LoadGraph("Resource/images/retry.png");
		ingame.menu_char_image[2] = LoadGraph("Resource/images/manual.png");
		ingame.menu_char_image[3] = LoadGraph("Resource/images/stage_select.png");
		ingame.menu_char_image[4] = LoadGraph("Resource/images/title.png");
		ingame.menu_char_image[5] = LoadGraph("Resource/images/next_stage.png");
		ingame.menu_char_image[6] = LoadGraph("Resource/images/stage_select.png");
		//メニューのマニュアルで使う操作説明画像
		ingame.menu_manual_image = LoadGraph("Resource/images/manual_menu.png");
		//ミチビキ君
		ingame.mitibikikun = LoadGraph("Resource/images/mitibikikunn.png");
		//チュートリアル中のログの選択画像
		ingame.tutoriallog_select = LoadGraph("Resource/images/logselection.png");
		//メニューのボタン
		ingame.start_button_image = LoadGraph("Resource/images/STARTbutton.png");
		//チュートリアル中のコントローラアニメーション
		ingame.tutorial_controol_left = LoadGraph("Resource/images/log4_left.png");
		ingame.tutorial_controol_right = LoadGraph("Resource/images/log4_right.png");
		ingame.tutorial_controol_up = LoadGraph("Resource/images/log4_up.png");
		ingame.tutorial_controol_down = LoadGraph("Resource/images/log4_down.png");
		//BGMの初期化
		PlayBgm();
		break;
	case 1:
		MapResourceInit();
		break;
	case 2:
		ObstacleManagerResourceInit();
		break;
	case 3:
		WoodRockResourceInit();
		break;
	case 4:
		ToolResourceInit();
		break;
	case 5:
		CarResourceInit();
		break;
	case 6:
		CursorResourceInit();
		break;
	case 7:
		GoalResourceInit();
		break;
	case 120:
		is_initialized = true;
		break;
	default:
		break;
	}

	ingame_init_step++;
}

bool IsInGameInit()
{
	return is_initialized;
}

eSceneType InGameSceneUpdate()
{
	//ゴールを受け取ったらステージを変えることを可能にする
	NextStageFlag(GetGoal());
	//ゴールしたなら次のステージへ
	StageChange();
	//マップの更新
	MapUpdate();
	//障害物の更新
	ObstacleManagerUpdate();
	//木岩の更新
	WoodRockUpdate();
	//ツールの更新
	ToolManagerUpdate();
	//車の更新
	CarManagerUpdate();
	//カーソルの更新
	CursorUpdate();
	//ゲームスタート
	GameStart();
	//ゴールの更新
	GoalUpdate();

	//ゲームオーバーになったらリセットします
	GameOverReset(GetGameOver(),GetCar());

	//////////////////////
	TutorialUpdate();
	/////////////////////

	InGameMenuUpdate(GetGoal(),GetGameOver());

	NextSelectFlag(GetGoal());

	ChangeCharExtrate();

	GoalSelectFlagReset();

	TutorialCursor();

	//メニューセレクトの分岐
	PadInputManager* pad_input = PadInputManager::GetInstance();
	if (ingame.mitibiki_flag == false)
	{
		if (ingame.menu_num == 0 &&
			pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress &&
			ingame.menu_flag == true)
		{
			Play_Sound_Ingame(sound.decision, 100);
			ingame.menu_num = 0;
			ingame.menu_flag = false;
		}
		if (ingame.menu_num == 1 &&
			pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress &&
			ingame.menu_flag == true)
		{
			Play_Sound_Ingame(sound.decision, 100);
			ingame.menu_num = 0;
			ingame.start = false;
			ingame.menu_flag = false;
			ingame.tutorial_log_num = 2;
			Stop_InGameBgm();
		}
		if (ingame.menu_num == 2 &&
			pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress &&
			ingame.menu_flag == true && ingame.menu_manual_flag == false)
		{
			Play_Sound_Ingame(sound.decision, 100);
			ingame.menu_manual_flag = true;
		}
		if (ingame.menu_num == 3 &&
			pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress &&
			ingame.menu_flag == true)
		{
			Play_Sound_Ingame(sound.decision, 100);
			Stop_InGameBgm();
			return eStageSelect;	//タイトルに戻る
			ingame.menu_flag = false;
			ingame.menu_num = 0;
		}
		if (ingame.menu_num == 4 &&
			pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress &&
			ingame.menu_flag == true)
		{
			Play_Sound_Ingame(sound.decision, 100);
			Stop_InGameBgm();
			return eTitle;	//タイトルに戻る

			ingame.menu_num = 0;
		}
	}


	//ゴールメニューセレクトの分岐
	if (ingame.goalmenu_num == 0 && ingame.goalmenu_flag == true &&
		pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		Play_Sound_Ingame(sound.decision, 100);
		ingame.goalselect_flag = true;
		ingame.start = false;
		ingame.menu_flag = false;
		ingame.goalmenu_flag = false;
		ingame.goalmenu_num = 0;
		Stop_InGameBgm();
	}
	if (ingame.goalmenu_num == 1 && ingame.goalmenu_flag == true &&
		pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		Play_Sound_Ingame(sound.decision, 100);
		Stop_InGameBgm();
		return eStageSelect;	//タイトルに戻る
		ingame.menu_flag = false;
		ingame.goalmenu_num = 0;
	}

	if (ingame.menu_manual_flag == true && pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
	{
		Play_Sound_Ingame(sound.decision, 100);
		ingame.menu_manual_flag = false;
	}

	return eInGame;
}

void InGameSceneDraw(void)
{
	
	/*DrawFormatString(50, 10, GetColor(255, 255, 255), "スペースでリザルト画面へ");*/

	//マップの描画
	MapDraw();

	//障害物の描画
	ObstacleManagerDraw();

	//木岩の描画
	WoodRockDraw();

	//ツールの描画
	ToolDraw();

	//車の描画
	CarDraw();

	//カーソルの描画
	CursorDraw(Get_Tool());

	//ゴールの描画
	GoalDraw();


	////////////////////
	TutorialDraw(GetGoal(),GetGameOver());
	///////////////////

	//スタートボタン
	DrawRotaGraphF(60.0f, 60.0f, 0.6f, 0.0, ingame.start_button_image, TRUE);

	//atrがgoal.flagを受け取っているかの確認、btrがステージ遷移できるかどうかの確認
	//後々消します
	/*DrawFormatString(300, 300, GetColor(255, 255, 255), "%d %d", atr,btr);*/
	if (ingame.start == false && ingame.manual_open == true ||
		ingame.menu_flag == true && ingame.manual_open == true)
	{
		DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, ingame.manual_image, TRUE);
	}
	if (ingame.start == false && ingame.manual_open == false && ingame.menu_flag == false)
	{
		DrawRotaGraphF(640.0f, 360.0f, 3.0, 0.0, ingame.back, TRUE);
		DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, ingame.space, TRUE);
	}

	//Startボタンが押されたときにだすセレクト画面
	MenuDraw();

	//goalしたときに出すセレクト画面
	GoalSelectMenuDraw();

	

	/////////////////////
	DrawFormatString(150, 150, GetColor(255, 255, 255), "%d %d %d", animetion_num,ingame.tutorial_achievements,ingame.tutorial_achievements);
	////////////////////
	
}
const InGame* GetInGame(void)
{
	return &ingame;
}

//Gameスタート
void GameStart(void)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (ingame.start == false && ingame.menu_flag == false)
	{
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_X) == ePadInputState::ePress&& ingame.manual_open == false)
		{
			ingame.gameover_se_flag = false;
			ingame.start = true;
			ingame.manual_open = false;
			Play_InGameBgm();
		}
	}
	if (ingame.manual_open == false&& ingame.start == false&&ingame.menu_flag == false)
	{
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_Y) == ePadInputState::eRelease)
		{
			ingame.manual_open = true;
		}
	}
	else if (ingame.manual_open == true)
	{
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::eRelease)
		{
			ingame.manual_open = false;
		}
	}
}

//ステージの番号を取得
void GetStageNumber(const StageSelect* stageselect)
{
	ingame.stage_num = stageselect->number;
}

//インゲームsound初期化
void PlayBgm(void)
{
	sound.bgm = LoadSoundMem("Resource/Sounds/main.mp3");
	sound.gameover = LoadSoundMem("Resource/Sounds/GameOver.mp3");
	sound.clear = LoadSoundMem("Resource/Sounds/clear.mp3");
	sound.pose = LoadSoundMem("Resource/Sounds/pose.mp3");
	sound.select_move = LoadSoundMem("Resource/Sounds/select_move.mp3");
	sound.decision = LoadSoundMem("Resource/Sounds/cursor_move_se.mp3");
}

//Goalした後のセレクト画面を出すフラグ
void NextSelectFlag(const Goal* goal)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (goal->flag == true)
	{
		ingame.menu_flag = true;
		ingame.goalmenu_flag = true;
	}

	if (ingame.goalmenu_flag == true)
	{
		if (ingame.stage_num == eSix)
		{
			ingame.goalmenu_num = 1;
			ingame.goalmenu_cursor_y = 240.0f + ingame.goalmenu_num * 130.0f;
		}
		else
		{
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
			{
				Play_Sound_Ingame2(sound.select_move, 100);
				ingame.goalmenu_num--;
				if (ingame.goalmenu_num < 0)
				{
					ingame.goalmenu_num = 1;
				}

				ingame.goalmenu_cursor_y = 300.0f + ingame.goalmenu_num * 130.0f;
			}
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
			{
				Play_Sound_Ingame2(sound.select_move, 100);
				ingame.goalmenu_num++;
				ingame.goalmenu_num = ingame.goalmenu_num % 2;

				ingame.goalmenu_cursor_y = 300.0f + ingame.goalmenu_num * 130.0f;
			}
		}
	}
}
//ステージチェンジを可能にするフラグ
void NextStageFlag(const Goal* goal)
{
	ingame.next_stage_flag = false;

	if (ingame.goalselect_flag == true)
	{
		ingame.next_stage_flag = true;
		atr ++;
		ingame.start = false;
		Stop_InGameBgm();
	}

	
}

void GoalSelectFlagReset(void)
{
	if (ingame.next_stage_flag == true)
	{
		ingame.goalselect_flag = false;
	}
}

//GameOverの時の処理
void GameOverReset(const GameOver* gameover,const Car* car)
{
	if (gameover->flag == true)
	{
		ingame.start = false;
	}
	if (car->direction == eStop)
	{
		if (ingame.gameover_se_flag == false)
		{
			if (car->goal_flag == true)
			{
				Play_Sound_Ingame(sound.clear, 90);
				ingame.gameover_se_flag = true;
			}
			else if(gameover->image_flag == true)
			{
				Play_Sound_Ingame(sound.gameover, 60);
				ingame.gameover_se_flag = true;
			}
		}
		if (CheckSoundMem(sound.bgm) == 1)
		{
			Stop_InGameBgm();
		}
	}
}

//ステージチェンジ処理
void StageChange(void)
{
	switch (ingame.stage_num)
	{
	case eOne:
		if (ingame.next_stage_flag == true)
		{
			ingame.stage_num = eTwo;
			btr++;
		}
		break;
	case eTwo:
		if (ingame.next_stage_flag == true)
		{
			ingame.stage_num = eThree;
			btr++;
		}
		break;
	case eThree:
		if (ingame.next_stage_flag == true)
		{
			ingame.stage_num = eFour;
			btr++;
		}
		break;
	case eFour:
		if (ingame.next_stage_flag == true)
		{
			ingame.stage_num = eFive;
			btr++;
		}
		break;
	case eFive:
		if (ingame.next_stage_flag == true)
		{
			ingame.stage_num = eSix;
			btr++;
		}
		break;
	case eSix:
		if (ingame.next_stage_flag == true)
		{
			ingame.stage_num = eOne;
			btr = 1;
		}
		break;
	default:
		break;
	}
}

//メニュー画面の開始とカーソルの処理
void InGameMenuUpdate(const Goal* goal,const GameOver*gameover)
{

	ingame.menu_cursor_y = 130.0f + ingame.menu_num * 120.0f;

	PadInputManager* pad_input = PadInputManager::GetInstance();

	//Goal,GameOver,Manualが開かれていない時
	if (goal->print_flag == false && gameover->image_flag == false && ingame.manual_open == false &&ingame.mitibiki_flag==false
		&&pad_input->GetButtonInputState(XINPUT_BUTTON_START) == ePadInputState::ePress)
	{
		ingame.menu_flag = true;
	}

	if (ingame.menu_flag == true&& ingame.goalmenu_flag == false
		&& ingame.menu_manual_flag == false&&ingame.mitibiki_flag==false)
	{
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
		{
			Play_Sound_Ingame2(sound.select_move, 100);
			ingame.menu_num--;
			if (ingame.menu_num < 0)
			{
				ingame.menu_num = 4;
			}
		}
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
		{
			Play_Sound_Ingame2(sound.select_move, 100);
			ingame.menu_num++;
			ingame.menu_num = ingame.menu_num % 5;
			
		}
	}
}

//メニュー画面の文字の拡大率処理
void ChangeCharExtrate(void)
{
	for (int i = 0; i < 7; i++)
	{
		ingame.char_extrate[i] = 0.7f;
	}
	ingame.char_extrate[ingame.menu_num] = 0.9f;
	ingame.char_extrate[ingame.goalmenu_num+5] = 0.9f;
}



//メニュー画面の描画
void MenuDraw(void)
{
	if (ingame.menu_flag == true && ingame.goalmenu_flag == false
		&&ingame.menu_manual_flag == false && ingame.mitibiki_flag == false)
	{
		DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, ingame.menu_image, TRUE);
		DrawRotaGraphF(ingame.menu_cursor_x, ingame.menu_cursor_y, 1.0, 0.0, ingame.menu_cursor, TRUE);
		for (int i = 0; i < 5; i++)
		{
			DrawRotaGraphF(640.0f, i * 120.0f + 130.0f, ingame.char_extrate[i], 0.0, ingame.menu_char_image[i], TRUE);
		}
	}

	if (ingame.menu_manual_flag == true)
	{
		DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, ingame.menu_manual_image, TRUE);
	}
	
}

//Goalｎメニュー画面の描画
void GoalSelectMenuDraw(void)
{
	if (ingame.goalmenu_flag == true)
	{
		DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, ingame.menu_image, TRUE);
		DrawRotaGraphF(ingame.goalmenu_cursor_x, ingame.goalmenu_cursor_y, 1.0, 0.0, ingame.menu_cursor, TRUE);
		if (ingame.stage_num == eSix)
		{
			DrawRotaGraphF(640.0f,130.0+240.0f, 0.8, 0.0, ingame.menu_char_image[6], TRUE);
		}
		else
		{
			for (int i = 5; i < 7; i++)
			{
				DrawRotaGraphF(640.0f, (i - 5) * 130.0f + 300.0f, ingame.char_extrate[i], 0.0, ingame.menu_char_image[i], TRUE);
			}
		}
	}
}

//BGMを再生
void Play_InGameBgm(void)
{
	PlaySoundMem(sound.bgm, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(90, sound.bgm);
}

//SE再生(音の重なりなし
void Play_Sound_Ingame(int sound, int volume)
{
	if (CheckSoundMem(sound) == 0)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);
		ChangeVolumeSoundMem(volume, sound);
	}
}

//SE再生（音の重なりあり
void Play_Sound_Ingame2(int sound, int volume)
{
	PlaySoundMem(sound, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(volume, sound);
}

//BGMをストップ
void Stop_InGameBgm(void)
{
	StopSoundMem(sound.bgm);
}
int tutorial_log;
//チュートリアルのログ
void TutorialDraw(const Goal* goal, const GameOver* gameover)
{
	if (ingame.stage_num == eOne&&ingame.start == true&&
		goal->print_flag == false && gameover->image_flag == false&&ingame.goalmenu_flag==false)
	{
		if (ingame.mitibiki_flag == true)
		{
			DrawRotaGraphF(640.0f, 360.0f, 3.0, 0.0, ingame.back, TRUE);

		}
		DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, tutorial_log, TRUE);
		DrawRotaGraphF(1190.0f, 425.0f, 0.16, 0.0, ingame.mitibikikun, TRUE);
		if (ingame.mitibiki_flag == true)
		{
			DrawRotaGraphF(875.0f, 160.0f, 0.75, 0.0, ingame.tutoriallog_select, TRUE);
		}
		TutorialCursor();
	}
}

void TutorialUpdate(void)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//ステージ1の時
	if (ingame.stage_num == eOne)
	{
		//チュートリアル実績
		TutorialAchievements(GetCursor1(), GetRock(), GetWood(), Get_Tool(), GetStage());


		char tutorial_load[256];
		snprintf(tutorial_load, sizeof(tutorial_load), "Resource/tutorial/log%d.png", ingame.tutorial_log_num);
		tutorial_log = LoadGraph(tutorial_load);

		//リセットする
		if (ingame.start == false)
		{
			ingame.tutorial_log_num = 2;
			ingame.tutorial_achievements = 1;
		}

		//チュートリアルのページをめくる
		if (ingame.tutorial_log_num < 18&& ingame.start == true)
		{
			//Aボタンで進める
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress &&
				ingame.mitibiki_flag == true)
			{
				ingame.tutorial_log_num++;
			}
		}

		if (ingame.tutorial_log_num > 2 && ingame.start == true)
		{
			//Bボタンで戻る
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress &&
				ingame.mitibiki_flag == true)
			{
				ingame.tutorial_log_num--;
			}
		}


		/*if (pad_input->GetButtonInputState(XINPUT_BUTTON_Y) == ePadInputState::ePress &&
			ingame.mitibiki_flag == false)
		{
			ingame.mitibiki_flag = true;
		}
		else if (pad_input->GetButtonInputState(XINPUT_BUTTON_Y) == ePadInputState::ePress &&
			ingame.mitibiki_flag == true)
		{
			ingame.mitibiki_flag = false;
		}*/
	}
}

void TutorialAchievements(const Cursor* cursor, const Rock* rock, const Wood* wood, const Tool* tool,
	const CreateStage* stage)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	switch (ingame.tutorial_achievements)
	{
	case 1:
		if (ingame.tutorial_log_num < 4)
		{
			ingame.mitibiki_flag = true;
		}
		else /*if (ingame.tutorial_log_num == 4)*/
		{
			ingame.mitibiki_flag = false;
			if (cursor->array_x == 5)
			{
				animetion_num++;
				if (animetion_num>30)
				{
					ingame.tutorial_log_num++;
					ingame.tutorial_achievements++;
					animetion_num=0;
					break;

				}
				
			}
		}
		break;
	case 2:
		if (ingame.tutorial_log_num < 5)
		{
			ingame.mitibiki_flag = true;
		}
		else
		{
			ingame.mitibiki_flag = false;
			if (rock->item_num > 0)
			{
				animetion_num++;
				if (animetion_num > 30)
				{
					ingame.tutorial_log_num++;
					ingame.tutorial_achievements++;
					animetion_num = 0;
					break;
				}
			}
		}
		break;
	case 3:
		if (ingame.tutorial_log_num < 6)
		{
			ingame.mitibiki_flag = true;
		}
		else
		{
			ingame.mitibiki_flag = false;
			if (tool->item_number == eRoad)
			{
				animetion_num++;
				if (animetion_num > 30)
				{
					ingame.tutorial_log_num++;
					ingame.tutorial_achievements++;
					animetion_num = 0;
					break;
				}
			}
		}
		break;
	case 4:
		if (tool->road_num > 0)
		{
			animetion_num++;
			if (animetion_num > 30)
			{
				ingame.tutorial_log_num++;
				ingame.tutorial_achievements++;
				animetion_num = 0;
				break;
			}
		}
		break;
	case 5:
		if (stage->array[7][4] == 4)
		{
			animetion_num++;
			if (animetion_num > 30)
			{
				ingame.tutorial_log_num++;
				ingame.tutorial_achievements++;
				animetion_num = 0;
				break;
			}
		}
		break;
	case 6:
		if (tool->wood_road_num==1)
		{
			animetion_num++;
			if (animetion_num > 30)
			{
				ingame.tutorial_log_num++;
				ingame.tutorial_achievements++;
				animetion_num = 0;
				break;
			}
		}
		break;
	case 7:
		if (stage->array[8][4] == 5)
		{
				ingame.tutorial_log_num++;
				ingame.tutorial_achievements++;
				break;
		}
	case 8:
		animetion_num++;
		if (animetion_num > 30)
		{
			if (stage->array[8][4] == 5)
			{
				ingame.mitibiki_flag = true;
				if (ingame.tutorial_log_num > 13)
				{
					ingame.mitibiki_flag = false;
					animetion_num = 0;
				}
			}
		}

	default:

		break;
	}
}
void TutorialCursor(void) 
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	if (ingame.tutorial_log_num == 4 && ingame.menu_flag==false )
	{
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::eHold)
		{
			DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_controol_left, TRUE);
		}
		else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::eHold)
		{
			DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_controol_right, TRUE);
		}
		else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::eHold)
		{
			DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_controol_up, TRUE);
		}
		else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::eHold)
		{
			DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_controol_down, TRUE);
		}
	}
}
