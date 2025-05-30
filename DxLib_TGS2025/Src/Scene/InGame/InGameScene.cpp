#include "InGameScene.h"
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
#include "../../Object/car.h"
#include "DxLib.h"

#include <math.h>
#include <stdlib.h>
#include<stdio.h>

#define D_SCROOL_SPEED		(200.0f)

//確認用変数　後に消します
int atr ;
int btr ;

//この辺まだ使っていない
//void HitCheck(const Cursor* cursor, const Obstacle* obstacle, int index);
void PlayBgm(void);

InGame ingame;
InGame_Sound sound;

void NextStageFlag(const Goal* goal);
void NextSelectFlag(const Goal* goal);
void GameOverReset(const GameOver* gameover);
void GetStageNumber(const StageSelect* stageselect);


//初期化
void InGameSceneInit(void)
{
	//説明の後ろに表示
	ingame.back = LoadGraph("Resource/images/waku.png");
	//インゲーム前の画面
	ingame.space= LoadGraph("Resource/images/aida.png");
	//操作説明の表示
	ingame.manual_open = false;
	//操作説明の画像
	ingame.manual_image= LoadGraph("Resource/images/manual_menu.png");

	ingame.menu_image = LoadGraph("Resource/images/white_back.png");
	ingame.menu_cursor = LoadGraph("Resource/images/menu_cursor.png");
	ingame.menu_char_image[0] = LoadGraph("Resource/images/continue.png");
	ingame.menu_char_image[1] = LoadGraph("Resource/images/retry.png");
	ingame.menu_char_image[2] = LoadGraph("Resource/images/title.png");
	ingame.menu_char_image[3] = LoadGraph("Resource/images/next_stage.png");
	ingame.menu_char_image[4] = LoadGraph("Resource/images/stage_select.png");
	

	//インゲームスタートのフラグ変数
	ingame.start = false;
	//ステージ番号を取得
	GetStageNumber(GetStageSelect());
	/*ingame.stage_num = eOne;*/
	//ステージ次のステージに変更するフラグ
	ingame.next_stage_flag = false;

	ingame.menu_flag = false;
	ingame.menu_num = 0;
	ingame.menu_cursor_x=300.0f;
	ingame.menu_cursor_y = 200.0f;

	ingame.goalmenu_flag = false;
	ingame.goalmenu_num = 0;
	ingame.goalmenu_cursor_x = 300.0f;
	ingame.goalmenu_cursor_y = 300.0f;

	ingame.goalselect_flag = false;

	for (int i = 0; i < 5; i++)
	{
		ingame.char_extrate[i] = 0.8f;
	}
	//確認用変数　後々消します
	atr = 0;
	btr = 1;

	//BGMの初期化
		PlayBgm();
		//ステージ生成の初期化
		
		
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

eSceneType InGameSceneUpdate()
{
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

	//ゴールを受け取ったらステージを変えることを可能にする
	NextStageFlag(GetGoal());

	//ゴールしたなら次のステージへ
	StageChange();
	//ゲームオーバーになったらリセットします
	GameOverReset(GetGameOver());

	InGameMenuUpdate();

	NextSelectFlag(GetGoal());

	ChangeCharExtrate();

	GoalSelectFlagReset();

	
	//メニューセレクトの分岐
	PadInputManager* pad_input = PadInputManager::GetInstance();
	if (ingame.menu_num == 0 &&
		pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		ingame.menu_flag = false;
		ingame.menu_num = 0;
	}
	if (ingame.menu_num == 1 &&
		pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		ingame.start = false;
		ingame.menu_flag = false;
		ingame.menu_num = 0;
	}
	if (ingame.menu_num==2&&
		pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		return eTitle;	//タイトルに戻る
		ingame.menu_num = 0;
	}


	//ゴールメニューセレクトの分岐
	if (ingame.goalmenu_num == 0 && ingame.goalmenu_flag == true &&
		pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		ingame.goalselect_flag = true;
		ingame.start = false;
		ingame.menu_flag = false;
		ingame.goalmenu_flag = false;
		ingame.goalmenu_num = 0;
	}
	if (ingame.goalmenu_num == 1 && ingame.goalmenu_flag == true &&
		pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		return eStageSelect;	//タイトルに戻る
		ingame.menu_flag = false;
		ingame.goalmenu_num = 0;
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
	

	//atrがgoal.flagを受け取っているかの確認、btrがステージ遷移できるかどうかの確認
	//後々消します
	/*DrawFormatString(300, 300, GetColor(255, 255, 255), "%d %d", atr,btr);*/
	if (ingame.start == false && ingame.manual_open == true)
	{
		DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, ingame.manual_image, TRUE);
	}
	if (ingame.start == false && ingame.manual_open == false)
	{
		DrawRotaGraphF(640.0f, 360.0f, 3.0, 0.0, ingame.back, TRUE);
		DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, ingame.space, TRUE);
	}
	
	//Startボタンが押されたときにだすセレクト画面
	MenuDraw();

	//goalしたときに出すセレクト画面
	GoalSelectMenuDraw();

	
}
const InGame* GetInGame(void)
{
	return &ingame;
}

//Gameスタート
void GameStart(void)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (ingame.start == false)
	{
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_X) == ePadInputState::ePress)
		{
			ingame.space = LoadGraph("Resource/images/aidaX.png");
		}
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_X) == ePadInputState::ePress)
		{
			ingame.start = true;
			ingame.manual_open = false;
		}
	}
	if (ingame.manual_open == false&& ingame.start == false)
	{
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_Y) == ePadInputState::ePress)
		{
			ingame.space = LoadGraph("Resource/images/aidaY.png");
		}
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_Y) == ePadInputState::eRelease)
		{
			ingame.manual_open = true;
		}
	}
	else if (ingame.manual_open == true)
	{
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_Y) == ePadInputState::eRelease)
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

//インゲームBGM再生
void PlayBgm(void)
{
	sound.bgm = LoadSoundMem("Resource/Sounds/main.mp3");
	PlaySoundMem(sound.bgm, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(90, sound.bgm);
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
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
		{
			ingame.goalmenu_num--;
			if (ingame.goalmenu_num < 0)
			{
				ingame.goalmenu_num = 1;
			}

			ingame.goalmenu_cursor_y = 300.0f + ingame.goalmenu_num * 130.0f;
		}
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
		{
			ingame.goalmenu_num++;
			ingame.goalmenu_num = ingame.goalmenu_num % 2;

			ingame.goalmenu_cursor_y = 300.0f + ingame.goalmenu_num * 130.0f;
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
	}

	
}

void GoalSelectFlagReset(void)
{
	if (ingame.next_stage_flag == true)
	{
		ingame.goalselect_flag = false;
	}
}

void GameOverReset(const GameOver* gameover)
{
	if (gameover->flag == true)
	{
		ingame.start = false;
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
			btr ++;
		}
		break;
	case eTwo:
		if (ingame.next_stage_flag == true)
		{
			ingame.stage_num = eThree;
			btr ++;
		}
		break;
	case eThree:
		if (ingame.next_stage_flag == true)
		{
			ingame.stage_num = eFour;
			btr ++;
		}
		break;
	case eFour:
		if (ingame.next_stage_flag == true)
		{
			ingame.stage_num = eFive;
			btr ++;
		}
		break;
	case eFive:
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

void InGameMenuUpdate(void)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetButtonInputState(XINPUT_BUTTON_START) == ePadInputState::ePress)
	{
		ingame.menu_flag = true;
	}

	if (ingame.menu_flag == true&& ingame.goalmenu_flag == false)
	{
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
		{
			ingame.menu_num--;
			if (ingame.menu_num < 0)
			{
				ingame.menu_num = 2;
			}
			
			ingame.menu_cursor_y = 200.0f + ingame.menu_num * 130.0f;
		}
		if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
		{
			ingame.menu_num++;
			ingame.menu_num = ingame.menu_num % 3;
			
			ingame.menu_cursor_y = 200.0f + ingame.menu_num * 130.0f;
		}
	}
}


void ChangeCharExtrate(void)
{
	for (int i = 0; i < 5; i++)
	{
		ingame.char_extrate[i] = 0.8f;
	}
	ingame.char_extrate[ingame.menu_num] = 0.9f;
	ingame.char_extrate[ingame.goalmenu_num+3] = 0.9f;
}




void MenuDraw(void)
{
	if (ingame.menu_flag == true && ingame.goalmenu_flag == false)
	{
		DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, ingame.menu_image, TRUE);
		DrawRotaGraph(ingame.menu_cursor_x, ingame.menu_cursor_y, 1.0, 0.0, ingame.menu_cursor, TRUE);
		for (int i = 0; i < 3; i++)
		{
			DrawRotaGraphF(640.0f, i * 130.0f + 200.0f, ingame.char_extrate[i], 0.0, ingame.menu_char_image[i], TRUE);
		}
	}
}

void GoalSelectMenuDraw(void)
{
	if (ingame.goalmenu_flag == true)
	{
		DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, ingame.menu_image, TRUE);
		DrawRotaGraphF(ingame.goalmenu_cursor_x, ingame.goalmenu_cursor_y, 1.0, 0.0, ingame.menu_cursor, TRUE);
		for (int i = 3; i < 5; i++)
		{
			DrawRotaGraphF(640.0f, (i - 3) * 130.0f + 300.0f, ingame.char_extrate[i], 0.0, ingame.menu_char_image[i], TRUE);
		}
	}
}
