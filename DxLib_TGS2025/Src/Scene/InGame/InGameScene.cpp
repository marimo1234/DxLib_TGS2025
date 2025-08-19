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
#include "DxLib.h"

#include <math.h>
#include <stdlib.h>
#include<stdio.h>

#define D_SCROOL_SPEED		(200.0f)
#define COUNT_NUM_INDEX		(2)       //スタートまでのカウントダウンの初期値（3から始まる）
#define COUNT_MAX		(180)  //カウントダウンの秒数

//確認用変数　後に消します
int atr;
int btr;
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
void GameOverReset(const GameOver* gameover, const Car* car);
void GetStageNumber(const SS_Num* ss_num);
void InGameMenuUpdate(const Goal* goal, const GameOver* gameover, const Car* car);
void Play_Sound_Ingame(int sound, int volume);
void Play_Sound_Ingame2(int sound, int volume);
void TutorialUpdate(void);
void TutorialAchievements(const Cursor* cursor, const Rock* rock, const Wood* wood, const Tool* tool, const CreateStage* stage);
void TutorialDraw(const Goal* goal, const GameOver* gameover, const Car* car);
void TutorialCursor(void);
void ItemTutorial(void);
void BlinkingAnimation(void);
void TutorialReset(void);
void WarnTutorial(const Car* car);



//初期化
void InGameSceneInit(void)
{

	//操作説明の表示
	ingame.manual_open = false;
	ingame.tutorial_log_num = 2;
	//インゲームスタートのフラグ変数
	ingame.start = false;
	//ステージ番号を取得
	GetStageNumber(GetSS_Num());
	/*ingame.stage_num = eOne;*/
	//ステージ次のステージに変更するフラグ
	ingame.next_stage_flag = false;

	ingame.menu_flag = false;
	ingame.menu_num = 0;
	ingame.menu_cursor_x = 280.0f;
	ingame.menu_cursor_y = 130.0f;

	ingame.goalmenu_flag = false;
	ingame.goalmenu_num = 0;
	ingame.goalmenu_cursor_x = 280.0f;
	ingame.goalmenu_cursor_y = 300.0f;

	ingame.goalselect_flag = false;

	ingame.menu_manual_flag = false;

	ingame.gameover_se_flag = false;

	ingame.num_idx = COUNT_NUM_INDEX;   //カウントダウンインデックス
	ingame.cnt = 0;   //カウントダウン用変数

	ingame.mitibiki_flag = false;
	ingame.tutorial_achievements = 1;
	ingame.menuanimationflag = false;
	ingame.woodtutorial = false;
	ingame.woodrodamakeswitch = false;
	ingame.madewoodswitch = false;
	ingame.itembarcomentswitch = false;
	ingame.itembaraxcount = 1;
	ingame.itembarwoodroadcount = 1;

	ingame.tutorial_count = 0;
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
		//数字の画像
		LoadDivGraph("Resource/images/StageSelect_Num.png", 6, 6, 1, 220, 270, ingame.num_img);
		//メニューのマニュアルで使う操作説明画像
		ingame.menu_manual_image = LoadGraph("Resource/images/manual_menu.png");
		//ミチビキ君
		ingame.mitibikikun = LoadGraph("Resource/images/mitibikikunn.png");
		//チュートリアル中のログの選択画像
		ingame.tutoriallog_select = LoadGraph("Resource/images/logselection.png");
		ingame.tutoriallog_selectA = LoadGraph("Resource/images/logselectionA.png");
		//メニューのボタン
		ingame.start_button_image = LoadGraph("Resource/images/STARTbutton.png");
		//チュートリアル中のコントローラアニメーション
		ingame.tutorial_controol_left = LoadGraph("Resource/images/log4_left.png");
		ingame.tutorial_controol_right = LoadGraph("Resource/images/log4_right.png");
		ingame.tutorial_controol_up = LoadGraph("Resource/images/log4_up.png");
		ingame.tutorial_controol_down = LoadGraph("Resource/images/log4_down.png");
		//アイテム欄のチュートリアルのアニメーション
		ingame.itemtutorial1 = LoadGraph("Resource/images/itemtutorial1.png");
		ingame.itemtutorial2 = LoadGraph("Resource/images/itemtutorial2.png");
		ingame.itemtutorial3 = LoadGraph("Resource/images/itemtutorial3.png");
		ingame.itemtutorial4 = LoadGraph("Resource/images/itemtutorial4.png");
		//チュートリアル中のAぼたんの点滅
		ingame.brakestoneanimetion1 = LoadGraph("Resource/images/log5-2.png");
		ingame.brakestoneanimetion2 = LoadGraph("Resource/images/log5-3.png");
		ingame.brakestoneanimetion3 = LoadGraph("Resource/images/log5-4.png");
		ingame.brakestoneanimetion4 = LoadGraph("Resource/images/log5-5.png");
		ingame.brakestoneanimetion5 = LoadGraph("Resource/images/log5-6.png");
		ingame.brakestoneanimetion6 = LoadGraph("Resource/images/log5-7.png");
		//チュートリアル中の道の生成アニメーション
		ingame.makeroda1 = LoadGraph("Resource/images/log7-1.png");
		ingame.makeroda2 = LoadGraph("Resource/images/log7-2.png");
		//チュートリアル中の道の置き方アニメーション
		ingame.putroda1 = LoadGraph("Resource/images/log8-1.png");
		ingame.putroda2 = LoadGraph("Resource/images/log8-2.png");
		//チュートリアル中の木の切り方
		ingame.brakewood1 = LoadGraph("Resource/images/log9-1.png");
		ingame.brakewood2 = LoadGraph("Resource/images/log9-2.png");
		ingame.brakewood3 = LoadGraph("Resource/images/log9-3.png");
		ingame.brakewood4 = LoadGraph("Resource/images/log9-4.png");
		ingame.brakewood5 = LoadGraph("Resource/images/log9-5.png");
		ingame.brakewood6 = LoadGraph("Resource/images/log9-6.png");
		//チュートリアル中の橋の置き方
		ingame.putbridge1 = LoadGraph("Resource/images/log10-1.png");
		//チュートリアル中の橋の作り方
		ingame.woodrodamake1 = LoadGraph("Resource/images/log10.5.png");
		ingame.woodrodamake2 = LoadGraph("Resource/images/log10.9.png");
		//チュートリアル中のログ
		ingame.tutorial_log1 = LoadGraph("Resource/tutorial/log2.png");
		ingame.tutorial_log2 = LoadGraph("Resource/tutorial/log3.png");
		ingame.tutorial_log3 = LoadGraph("Resource/tutorial/log4.png");
		ingame.tutorial_log4 = LoadGraph("Resource/tutorial/log5.png");
		ingame.tutorial_log5 = LoadGraph("Resource/tutorial/log6.png");
		ingame.tutorial_log6 = LoadGraph("Resource/tutorial/log7.png");
		ingame.tutorial_log7 = LoadGraph("Resource/tutorial/log8.png");
		ingame.tutorial_log8 = LoadGraph("Resource/tutorial/log9.png");
		ingame.tutorial_log9 = LoadGraph("Resource/tutorial/log10.png");
		ingame.tutorial_log10 = LoadGraph("Resource/tutorial/log11.png");
		ingame.tutorial_log11 = LoadGraph("Resource/tutorial/log12.png");
		ingame.tutorial_log12 = LoadGraph("Resource/tutorial/log13.png");
		ingame.warntutorial= LoadGraph("Resource/images/log20.png");
		//チュートリアル中のアイテム欄のコメント
		ingame.itembarcoment1 = LoadGraph("Resource/images/itemtutorialcoment1.png");
		ingame.itembarcoment2 = LoadGraph("Resource/images/itemtutorialcoment2.png");
		ingame.itembarcoment3 = LoadGraph("Resource/images/itemtutorialcoment3.png");
		ingame.itembarcoment4 = LoadGraph("Resource/images/itemtutorialcoment4.png");
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
	GameOverReset(GetGameOver(), GetCar());

	//////////////////////
	TutorialUpdate();
	/////////////////////

	InGameMenuUpdate(GetGoal(), GetGameOver(),GetCar());

	NextSelectFlag(GetGoal());

	ChangeCharExtrate();

	GoalSelectFlagReset();

	TutorialCursor();

	TutorialReset();
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
			ingame.num_idx = COUNT_NUM_INDEX;    //カウントダウン画像番号のリセット
			ingame.cnt = 0;        //カウントダウンリセット
			ingame.start = false;
			TutorialReset();
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
		ingame.num_idx = COUNT_NUM_INDEX;    //カウントダウン画像番号のリセット
		ingame.cnt = 0;        //カウントダウンリセット
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

	
	//車の描画
	CarDraw();
	
	//ツールの描画
	ToolDraw();

	//警告マークの描画
	CarWarnDraw();

	//カーソルの描画
	CursorDraw(Get_Tool());
	
	//木岩のエフェクト描画
	WoodRockEffectDraw();

	//スタートボタン
	/*DrawRotaGraphF(60.0f, 60.0f, 0.6f, 0.0, ingame.start_button_image, TRUE);*/

	//ゴールの描画
	GoalDraw();

	////////////////////
	TutorialDraw(GetGoal(), GetGameOver(), GetCar());
	///////////////////

	//atrがgoal.flagを受け取っているかの確認、btrがステージ遷移できるかどうかの確認
	//後々消します
	/*DrawFormatString(300, 300, GetColor(255, 255, 255), "%d %d", atr,btr);*/
	if (ingame.start == false && ingame.manual_open == true ||
		ingame.menu_flag == true && ingame.manual_open == true)
	{
		DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, ingame.manual_image, TRUE);
	}
	if (ingame.start == false && ingame.manual_open == false && ingame.menu_flag == false && ingame.stage_num != eOne)
	{
		/*DrawRotaGraphF(640.0f, 360.0f, 3.0, 0.0, ingame.back, TRUE);
		DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, ingame.space, TRUE);*/
	}

	if (ingame.start == false && ingame.menu_flag == false && ingame.stage_num != eOne)
	{
		DrawRotaGraphF(640.0f, 100.0f, 0.5, 0.0, ingame.num_img[ingame.num_idx], TRUE);
	}

	//Startボタンが押されたときにだすセレクト画面
	MenuDraw();

	//goalしたときに出すセレクト画面
	GoalSelectMenuDraw();



	/////////////////////
	//DrawFormatString(150, 150, GetColor(255, 255, 255), "%d %d %d", iii, ingame.menu_flag, ingame.itembarwoodroadcount );
	//DrawFormatString(150, 150, GetColor(255, 255, 255), "%d %d %d %d ", ingame.tutorial_log_num, ingame.tutorial_achievements, ingame.makerodacount, ingame.tutorial_count);
	////////////////////

	/*DrawFormatString(150, 150, GetColor(255, 255, 255), "%d", ingame.cnt);*/
}

const InGame* GetInGame(void)
{
	return &ingame;
}

//Gameスタート
void GameStart(void)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	if (ingame.stage_num == eOne)
	{
		if (ingame.tutorial_count < 80)
		{
			ingame.tutorial_count++;
		}
		if (ingame.start == false && ingame.menu_flag == false)
		{
			ingame.gameover_se_flag = false;
			ingame.start = true;
			ingame.manual_open = false;
			Play_InGameBgm();
		}
	}
	else
	{
		//カウントダウンの後に始まる
		if (ingame.start == false && ingame.menu_flag == false)
		{
			InGameStartCount();
			InGameCountAnim();
		}
		////Yを押したら操作説明が出る
		//if (ingame.manual_open == false && ingame.start == false && ingame.menu_flag == false)
		//{
		//	if (pad_input->GetButtonInputState(XINPUT_BUTTON_Y) == ePadInputState::eRelease)
		//	{
		//		ingame.manual_open = true;
		//	}
		//}
		////Bボタンで操作説明画面から戻る
		//else if (ingame.manual_open == true)
		//{
		//	if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::eRelease)
		//	{
		//		ingame.manual_open = false;
		//	}
		//}
	}
}

//インゲーム前のカウントダウン
void InGameStartCount(void)
{
	if (ingame.cnt <= COUNT_MAX)
	{
		ingame.cnt++;
	}

	if (ingame.cnt > COUNT_MAX)
	{
		ingame.gameover_se_flag = false;
		ingame.start = true;
		ingame.manual_open = false;
		Play_InGameBgm();
	}
}

void InGameCountAnim(void)
{
	if (ingame.cnt != 0 && ingame.cnt % 60 == 0)
	{
		ingame.num_idx--;
	}
}
//ステージの番号を取得
void GetStageNumber(const SS_Num* ss_num)
{
	ingame.stage_num = ss_num->stg_num;
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
		atr++;
		ingame.start = false;
		/*Stop_InGameBgm();*/
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
void GameOverReset(const GameOver* gameover, const Car* car)
{
	if (gameover->flag == true)
	{
		ingame.num_idx = COUNT_NUM_INDEX;    //カウントダウン画像番号のリセット
		ingame.cnt = 0;        //カウントダウンリセット
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
			else if (gameover->image_flag == true)
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
void InGameMenuUpdate(const Goal* goal, const GameOver* gameover,const Car*car)
{

	ingame.menu_cursor_y = 130.0f + ingame.menu_num * 120.0f;

	PadInputManager* pad_input = PadInputManager::GetInstance();

	//Goal,GameOver,Manualが開かれていない時
	if (goal->print_flag == false && gameover->image_flag == false && ingame.manual_open == false && ingame.mitibiki_flag == false
		&& car->direction != eStop && car->goal_flag == false && pad_input->GetButtonInputState(XINPUT_BUTTON_START) == ePadInputState::ePress)
	{
		Play_Sound_Ingame2(sound.select_move, 100);
		ingame.menu_flag = true;
	}

	if (ingame.menu_flag == true && ingame.goalmenu_flag == false
		&& ingame.menu_manual_flag == false && ingame.mitibiki_flag == false)
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
	ingame.char_extrate[ingame.goalmenu_num + 5] = 0.9f;
}



//メニュー画面の描画
void MenuDraw(void)
{
	if (ingame.menu_flag == true && ingame.goalmenu_flag == false
		&& ingame.menu_manual_flag == false && ingame.mitibiki_flag == false)
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
			DrawRotaGraphF(640.0f, 130.0 + 240.0f, 0.8, 0.0, ingame.menu_char_image[6], TRUE);
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
void TutorialDraw(const Goal* goal, const GameOver* gameover, const Car* car)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	if (ingame.stage_num == eOne && ingame.start == true &&
		goal->print_flag == false && gameover->image_flag == false && ingame.goalmenu_flag == false)
	{
		if (ingame.mitibiki_flag == true)
		{
			DrawRotaGraphF(640.0f, 360.0f, 3.0, 0.0, ingame.back, TRUE);

		}
		DrawRotaGraphF(1190.0f, 425.0f, 0.16, 0.0, ingame.mitibikikun, TRUE);
		if (ingame.menuanimationflag == false)
		{
			if (ingame.woodrodamakeswitch == true)
			{
				DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.woodrodamake1, TRUE);
			}
			else if (ingame.madewoodswitch == false)
			{
				switch (ingame.tutorial_log_num)
				{
				case 2:

					if (ingame.warntutorial_flag == true && car->warntutorial_car_flag == true)
					{
						WarnTutorial(GetCar());
						ingame.warntutorial_flag_public = true;
						if (ingame.warntutorial_flag == true && pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
						{
							ingame.itemcoment_switch = true;
							ingame.mitibiki_flag = false;
							ingame.warntutorial_flag = false;
							ingame.warntutorial_flag_public = false;
						}
					}
					if (ingame.warntutorial_flag_public == false)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_log1, TRUE);
					}
					break;
				case 3:
					if (ingame.warntutorial_flag == true && car->warntutorial_car_flag == true)
					{
						WarnTutorial(GetCar());
					    
						if (ingame.warntutorial_flag == true && pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
						{
							ingame.itemcoment_switch = true;
							ingame.mitibiki_flag = false;
							ingame.warntutorial_flag = false;
							ingame.warntutorial_flag_public = false;
						}
					}
					if (ingame.warntutorial_flag_public == false)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_log2, TRUE);
					}
					break;
				case 4:
					if (ingame.warntutorial_flag == true && car->warntutorial_car_flag == true)
					{
						WarnTutorial(GetCar());
						ingame.warntutorial_flag_public = true;
						if (ingame.warntutorial_flag == true && pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
						{
							ingame.itemcoment_switch = true;
							ingame.mitibiki_flag = false;
							ingame.warntutorial_flag = false;
							ingame.warntutorial_flag_public = false;
						}
					}
					if (ingame.warntutorial_flag_public == false)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_log3, TRUE);
					}
					break;
				case 5:
					if (ingame.warntutorial_flag == true && car->warntutorial_car_flag == true)
					{
						WarnTutorial(GetCar());
						ingame.warntutorial_flag_public = true;
						if (ingame.warntutorial_flag == true && pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::eHold)
						{
							ingame.itemcoment_switch = true;
							ingame.mitibiki_flag = false;
							ingame.warntutorial_flag = false;
							ingame.warntutorial_flag_public = false;
						}
					}
					if (ingame.warntutorial_flag_public == false)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_log4, TRUE);
					}
					break;
				case 6:
					if (ingame.warntutorial_flag == true && car->warntutorial_car_flag == true)
					{
						WarnTutorial(GetCar());
						ingame.warntutorial_flag_public = true;
						if (ingame.warntutorial_flag == true && pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::eHold)
						{
							ingame.itemcoment_switch = true;
							ingame.mitibiki_flag = false;
							ingame.warntutorial_flag = false;
							ingame.warntutorial_flag_public = false;
						}
					}
					if (ingame.warntutorial_flag_public == false)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_log5, TRUE);
					}
					break;
				case 7:
					if (ingame.warntutorial_flag == true && car->warntutorial_car_flag == true)
					{
						WarnTutorial(GetCar());
						ingame.warntutorial_flag_public = true;
						if (ingame.warntutorial_flag == true && pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
						{
							ingame.itemcoment_switch = true;
							ingame.mitibiki_flag = false;
							ingame.warntutorial_flag = false;
							ingame.warntutorial_flag_public = false;
						}
					}
					if (ingame.warntutorial_flag_public == false)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_log7, TRUE);
					}
					break;
				case 8:
					if (ingame.warntutorial_flag == true && car->warntutorial_car_flag == true)
					{
						WarnTutorial(GetCar());
						ingame.warntutorial_flag_public = true;
						if (ingame.warntutorial_flag == true && pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
						{
							ingame.itemcoment_switch = true;
							ingame.mitibiki_flag = false;
							ingame.warntutorial_flag = false;
							ingame.warntutorial_flag_public = false;
						}
					}
				    if (ingame.warntutorial_flag_public == false)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_log7, TRUE);
					}
					break;
				case 9:

					if (ingame.warntutorial_flag == true && car->warntutorial_car_flag == true)
					{
						WarnTutorial(GetCar());
						ingame.warntutorial_flag_public = true;
						if (ingame.warntutorial_flag == true && pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
						{
							ingame.itemcoment_switch = true;
							ingame.mitibiki_flag = false;
							ingame.warntutorial_flag = false;
							ingame.warntutorial_flag_public = false;
						}
					}
					if (ingame.warntutorial_flag_public == false)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_log8, TRUE);
					}
					break;
				case 10:

					if (ingame.warntutorial_flag == true && car->warntutorial_car_flag == true)
					{
						WarnTutorial(GetCar());
						ingame.warntutorial_flag_public = true;
						if (ingame.warntutorial_flag == true && pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
						{
							ingame.itemcoment_switch = true;
							ingame.mitibiki_flag = false;
							ingame.warntutorial_flag = false;
							ingame.warntutorial_flag_public = false;
						}
					}
					if (ingame.warntutorial_flag_public == false)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_log9, TRUE);
					}
					break;
				case 11:

					if (ingame.warntutorial_flag == true && car->warntutorial_car_flag == true)
					{
						WarnTutorial(GetCar());
						ingame.warntutorial_flag_public = true;
						if (ingame.warntutorial_flag == true && pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
						{
							ingame.itemcoment_switch = true;
							ingame.mitibiki_flag = false;
							ingame.warntutorial_flag = false;
							ingame.warntutorial_flag_public = false;
						}
					}
					if (ingame.warntutorial_flag_public == false)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_log10, TRUE);
					}
					break;
				case 12:

					if (ingame.warntutorial_flag == true && car->warntutorial_car_flag == true)
					{
						WarnTutorial(GetCar());
						ingame.warntutorial_flag_public = true;
						if (ingame.warntutorial_flag == true && pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
						{
							ingame.itemcoment_switch = true;
							ingame.mitibiki_flag = false;
							ingame.warntutorial_flag = false;
							ingame.warntutorial_flag_public = false;
						}
					}
					if (ingame.warntutorial_flag_public == false)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_log11, TRUE);
					}
					break;
				case 13:

					if (ingame.warntutorial_flag == true && car->warntutorial_car_flag == true)
					{
						WarnTutorial(GetCar());
						ingame.warntutorial_flag_public = true;
						if (ingame.warntutorial_flag == true && pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
						{
							ingame.itemcoment_switch = true;
							ingame.mitibiki_flag = false;
							ingame.warntutorial_flag = false;
							ingame.warntutorial_flag_public = false;
						}
					}
					if (ingame.warntutorial_flag_public == false)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.tutorial_log12, TRUE);
					}
					break;
				default:
					break;
				}
			}
		}
		if (ingame.mitibiki_flag == true && ingame.tutorial_count == 80 && ingame.tutorial_log_num==2 && ingame.warntutorial_flag_public == false)
		{
			DrawRotaGraphF(875.0f, 160.0f, 0.75, 0.0, ingame.tutoriallog_selectA, TRUE);
		}
		else if(ingame.warntutorial_flag_public == false &&ingame.mitibiki_flag == true && ingame.tutorial_count == 80)
		{
			DrawRotaGraphF(875.0f, 160.0f, 0.75, 0.0, ingame.tutoriallog_select, TRUE);
		}
		TutorialCursor();
		if ((ingame.tutorial_log_num == 6 || ingame.menuanimationflag == true)&& ingame.itemcoment_switch == true)
		{
			ItemTutorial();
			
			 if(ingame.tutorial_achievements==2)
			{
				DrawRotaGraphF(855.0f, 235.0f, 1.0, 0.0, ingame.itembarcoment4, TRUE);
			}
			 else if (ingame.tutorial_log_num == 6)
			{
				DrawRotaGraphF(875.0f, 225.0f, 1.0, 0.0, ingame.itembarcoment1, TRUE);
			}
			else if (ingame.itembarcomentswitch == false)
			{
				DrawRotaGraphF(875.0f, 225.0f, 1.0, 0.0, ingame.itembarcoment2, TRUE);
			}
			else if (ingame.itembarcomentswitch == true)
			{
				DrawRotaGraphF(875.0f, 225.0f, 1.0, 0.0, ingame.itembarcoment3, TRUE);
			}
		}
		if (ingame.tutorial_log_num == 5 || ingame.tutorial_log_num == 7 || ingame.tutorial_log_num == 8 || ingame.tutorial_log_num == 9 || ingame.tutorial_log_num == 10)
		{
			BlinkingAnimation();
		}

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


		/*char tutorial_load[256];
		snprintf(tutorial_load, sizeof(tutorial_load), "Resource/tutorial/log%d.png", ingame.tutorial_log_num);
		tutorial_log = LoadGraph(tutorial_load);*/

		//リセットする
		if (ingame.start == false)
		{
			ingame.tutorial_log_num = 2;
			ingame.tutorial_achievements = 1;
		}

		//チュートリアルのページをめくる
		if (ingame.tutorial_log_num < 18 && ingame.start == true)
		{
			//Aボタンで進める
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress &&
				ingame.mitibiki_flag == true && ingame.tutorial_count == 80&& ingame.warntutorial_flag_public == false)
			{
				ingame.tutorial_log_num++;
				if (ingame.tutorial_log_num==6)
				{
					ingame.tutorial_log_num = 8;
				}
			}
		}

		if (ingame.tutorial_log_num > 2 && ingame.start == true)
		{
			//Bボタンで戻る
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress &&
				ingame.mitibiki_flag == true && ingame.tutorial_count == 80)
			{
				ingame.tutorial_log_num--;
				if (ingame.tutorial_log_num == 7)
				{
					ingame.tutorial_log_num = 5;
				}
			}
		}


		/*if (pad_input->GetButtonInputState(XINPUT_BUTTON_Y) == ePadInputState::ePress &&
			ingame.mitibiki_flag == false)
		{
			ingame.mitibiki_flag = true;
		}*/
		if (ingame.tutorial_log_num == 4)
		{
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress &&
				ingame.mitibiki_flag == true)
			{
				ingame.mitibiki_flag = false;
			}
		}
	}
}
//チュートリアルの説明順番設定
void TutorialAchievements(const Cursor* cursor, const Rock* rock, const Wood* wood, const Tool* tool,
	const CreateStage* stage)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	switch (ingame.tutorial_achievements)
	{
	case 1:
		ingame.woodtutorial == false;
		if (ingame.tutorial_log_num < 4)
		{
			ingame.mitibiki_flag = true;
		}
		else if (ingame.tutorial_log_num == 4)
		{
			if (cursor->array_x == 5)
			{
				ingame.tutorial_log_num++;
				ingame.tutorial_achievements++;
				animetion_num = 0;
				break;

			}
		}
		break;
	case 2:
		if (stage->array[6][4] == 5)
		{
			ingame.mitibiki_flag = true;
			ingame.tutorial_log_num = 11;
			ingame.tutorial_achievements = 8;
			ingame.woodtutorial = false;
			ingame.woodrodamakeswitch = false;
			ingame.madewoodswitch = false;
			break;
		}
		ingame.woodtutorial == false;
		/*if (ingame.tutorial_log_num < 5)
		{
			ingame.mitibiki_flag = true;
		}*/
		//else
		//{
			if (rock->item_num > 0)
			{
				ingame.tutorial_log_num=6;
				ingame.tutorial_achievements=3;
				animetion_num = 0;
				break;

			}
			else if (tool->item_number != ePickaxe&&ingame.tutorial_log_num<6)
			{
				ingame.tutorial_log_num = 6;
				/*ingame.tutorial_achievements += 1;*/
			}
			else if (tool->item_number == ePickaxe && ingame.tutorial_log_num ==6)
			{
				ingame.tutorial_log_num = 5;
				/*ingame.tutorial_achievements += 1;*/
			}
		//}
		break;
	case 3:
		if (stage->array[6][4] == 5)
		{
			ingame.mitibiki_flag = true;
			ingame.tutorial_log_num = 11;
			ingame.tutorial_achievements = 8;
			ingame.woodtutorial = false;
			ingame.woodrodamakeswitch = false;
			ingame.madewoodswitch = false;
			break;
		}
		ingame.woodtutorial == false;
		if (tool->item_number == eRoad)
		{

			ingame.tutorial_log_num=7;
			ingame.tutorial_achievements=4;
			animetion_num = 0;
			ingame.itemtutorial_num = 1;
			break;

		}
		break;
	case 4:
		if (stage->array[6][4] == 5)
		{
			ingame.mitibiki_flag = true;
			ingame.tutorial_log_num = 11;
			ingame.tutorial_achievements = 8;
			ingame.woodtutorial = false;
			ingame.woodrodamakeswitch = false;
			ingame.madewoodswitch = false;
			break;
		}
		else if (tool->item_number != eRoad)
		{
			ingame.tutorial_log_num--;
			ingame.tutorial_achievements--;
		}
		ingame.tutorial_log_num++;
		ingame.tutorial_achievements++;
		animetion_num = 0;
		ingame.itemtutorial_num = 1;
		break;

	case 5:
		if (stage->array[6][4] == 5)
		{
			ingame.mitibiki_flag = true;
			ingame.tutorial_log_num = 11;
			ingame.tutorial_achievements = 8;
			ingame.woodtutorial = false;
			ingame.woodrodamakeswitch = false;
			ingame.madewoodswitch = false;
			break;
		}
		else if (tool->item_number != eRoad&& stage->array[4][4] != 4)
		{
			ingame.tutorial_log_num-=2;
			ingame.tutorial_achievements-=2;
		}
		if (stage->array[5][4] == 4&& tool->wood_road_num == 1)
		{
			ingame.tutorial_log_num++;
			ingame.tutorial_achievements++;
			animetion_num = 0;
			break;

		}
		else if (stage->array[5][4] == 4)
		{
			ingame.tutorial_log_num++;
			ingame.tutorial_achievements++;
			animetion_num = 0;
			ingame.menuanimationflag = true;
			break;

		}
		break;
	case 6:
		if (stage->array[6][4] == 5)
		{
			ingame.mitibiki_flag = true;
			ingame.tutorial_log_num = 11;
			ingame.tutorial_achievements = 8;
			ingame.woodtutorial = false;
			ingame.woodrodamakeswitch = false;
			ingame.madewoodswitch = false;
			break;
		}
		if (tool->item_number == eAx)
		{
			ingame.menuanimationflag = false;
		}
		else 
		{
			ingame.menuanimationflag = true;
		}
		if (wood->item_num > 0)
		{
			if (tool->wood_road_num != 1)
			{
				ingame.itembarcomentswitch = true;
				ingame.menuanimationflag = true;
				ingame.woodtutorial = true;
			}
			
		}
		if (tool->wood_road_num == 1)
		{
			ingame.menuanimationflag = false;
			ingame.tutorial_log_num++;
			ingame.tutorial_achievements++;
			animetion_num = 0;
			ingame.woodrodamakeswitch = false;
			ingame.madewoodswitch = false;
			break;

		}
		break;
	case 7:
		if (stage->array[6][4] == 5)
		{
			ingame.mitibiki_flag = true;
			ingame.tutorial_log_num++;
			ingame.tutorial_achievements++;
			break;
		}
		break;
	case 8:

		if (ingame.tutorial_log_num < 13)
		{
			ingame.mitibiki_flag = true;
		}
		else
		{
			ingame.mitibiki_flag = false;
		}



	default:

		break;
	}
}
void TutorialCursor(void)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();
	if (ingame.tutorial_log_num == 4 && ingame.menu_flag == false&& ingame.warntutorial_flag_public ==false)
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
void ItemTutorial(void)
{
	if (ingame.warntutorial_flag_public == false)
	{


		if (ingame.menu_flag == false)
		{
			if (ingame.woodtutorial == true)
			{
				ingame.itembarwoodroadcount++;

			}
			else if (ingame.tutorial_achievements==2)
			{
				ingame.itemtutorial_num = 0;
				ingame.itembaraxcount = 0; 
				ingame.itembarwoodroadcount = 0;
			}
			else if (ingame.tutorial_log_num == 6)
			{
				ingame.itemtutorial_num++;

			}
			else if (ingame.tutorial_achievements == 7)
			{
				ingame.itembarbridgecount++;
			}
			else if (ingame.tutorial_log_num == 9 && ingame.woodtutorial == false)
			{
				ingame.itembaraxcount++;
			}
			

		}
		if (ingame.itemtutorial_num > 150)
		{
			ingame.itemtutorial_num = 1;
		}
		else if (ingame.itemtutorial_num > 45)
		{
			DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.itemtutorial4, TRUE);
		}
		else if (ingame.itembarwoodroadcount > 70 && ingame.woodtutorial == true)
		{
			ingame.itembarwoodroadcount = 1;
			ItemTutorial();
		}
		else if (ingame.itemtutorial_num > 30 || ingame.itembarwoodroadcount > 30)
		{
			DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.itemtutorial3, TRUE);
		}
		else if (ingame.itembaraxcount > 44 && ingame.tutorial_log_num == 9 && ingame.woodtutorial == false)
		{
			ingame.itembaraxcount = 1;
			ItemTutorial();
		}
		else if (ingame.itemtutorial_num > 15 || ingame.itembaraxcount > 15 || ingame.itembarwoodroadcount > 15)
		{
			DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.itemtutorial2, TRUE);
		}
		else if (ingame.itemtutorial_num > 0 || ingame.itembaraxcount > 0 || ingame.itembarwoodroadcount > 0)
		{
			DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.itemtutorial1, TRUE);
		}
	}
}
void BlinkingAnimation(void)
{
	if (ingame.warntutorial_flag_public == false)
	{


		if (ingame.tutorial_log_num == 5)
		{
			if (ingame.menu_flag == false)
			{
				ingame.brakestoneanimetioncount++;
			}

			if (ingame.brakestoneanimetioncount > 225)
			{
				ingame.brakestoneanimetioncount = 0;
			}
			else if (ingame.brakestoneanimetioncount > 195)
			{
				DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.brakestoneanimetion7, TRUE);
			}
			else if (ingame.brakestoneanimetioncount > 165)
			{
				DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.brakestoneanimetion6, TRUE);
			}
			else if (ingame.brakestoneanimetioncount > 135)
			{
				DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.brakestoneanimetion5, TRUE);
			}
			else if (ingame.brakestoneanimetioncount > 105)
			{
				DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.brakestoneanimetion4, TRUE);
			}
			else if (ingame.brakestoneanimetioncount > 85)
			{
				DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.brakestoneanimetion3, TRUE);
			}
			else if (ingame.brakestoneanimetioncount > 55)
			{
				DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.brakestoneanimetion2, TRUE);
			}
			else if (ingame.brakestoneanimetioncount > 25)
			{
				DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.brakestoneanimetion1, TRUE);
			}
		}
		else if (ingame.tutorial_log_num == 8)
		{
			if (ingame.menu_flag == false)
			{
				ingame.putrodacount++;
			}

			if (ingame.putrodacount > 105)
			{
				ingame.putrodacount = 0;
			}
			else if (ingame.putrodacount > 70)
			{
				DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.putroda2, TRUE);
			}
			else if (ingame.putrodacount > 35)
			{
				DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.putroda1, TRUE);
			}
		}
		else if (ingame.tutorial_log_num == 9)
		{

			if (ingame.menuanimationflag == false)
			{


				if (ingame.menu_flag == false)
				{
					ingame.brakewoodcount++;
				}
				if (ingame.woodrodamakeswitch == false)
				{
					if (ingame.brakewoodcount > 195)
					{
						ingame.brakewoodcount = 0;
					}
					else if (ingame.brakewoodcount > 165)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.brakewood6, TRUE);
					}
					else if (ingame.brakewoodcount > 135)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.brakewood5, TRUE);
					}
					else if (ingame.brakewoodcount > 105)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.brakewood4, TRUE);
					}
					else if (ingame.brakewoodcount > 85)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.brakewood3, TRUE);
					}
					else if (ingame.brakewoodcount > 55)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.brakewood2, TRUE);
					}
					else if (ingame.brakewoodcount > 25)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.brakewood1, TRUE);
					}
				}
				/*else if (ingame.woodrodamakeswitch == true && ingame.tutorial_log_num == 9)
				{
					if (ingame.brakewoodcount > 105)
					{
						ingame.brakewoodcount = 0;
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.woodrodamake1, TRUE);
					}
					else if (ingame.brakewoodcount > 70)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.woodrodamake2, TRUE);
					}
					else if (ingame.brakewoodcount > 35)
					{
						DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.woodrodamake1, TRUE);
					}
				}*/
			}
		}
		else if (ingame.tutorial_log_num == 10)
		{
			if (ingame.menu_flag == false)
			{
				ingame.putbridgecount++;
			}

			if (ingame.putbridgecount > 70)
			{
				ingame.putbridgecount = 0;
			}
			else if (ingame.putbridgecount > 35)
			{
				DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.putbridge1, TRUE);
			}
		}
	}
}
void WarnTutorial(const Car*car) 
{
	
	DrawRotaGraphF(875.0f, 235.0f, 1.0, 0.0, ingame.warntutorial, TRUE);
	ingame.mitibiki_flag = true;
	ingame.itemcoment_switch = false;
}
void TutorialReset(void)
{
	if (ingame.start == false)
	{
		ingame.tutorial_count = 0;
		ingame.mitibiki_flag = false;
		ingame.tutorial_achievements = 1;
		ingame.menuanimationflag = false;
		ingame.woodtutorial = false;
		ingame.woodrodamakeswitch = false;
		ingame.madewoodswitch = false;
		ingame.itembarcomentswitch = false;
		ingame.putbridgecount = 0;
		ingame.brakewoodcount = 0;
		ingame.putrodacount = 0;
		ingame.makerodacount = 0;
		ingame.brakestoneanimetioncount = 0;
		ingame.itemtutorial_num = 1;
		ingame.itembaraxcount = 1;
		ingame.itembarwoodroadcount = 1;
		ingame.warntutorial_flag = true;
		ingame.itemcoment_switch = true;
	}
}