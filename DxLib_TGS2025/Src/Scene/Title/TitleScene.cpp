﻿#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/PadInputManager.h"
#include "DxLib.h"
#include <math.h>

int title_image;		//タイトル画像のハンドル

Title title;

//タイトルシーンの初期化
void TitleSceneInit(void)
{
	//画像の読み込み
	title.image = LoadGraph("Resource/Images/title_image.png");	//タイトル画像

	//seの読み込み
	//select_SE = LoadSoundMem("Resource/SE/select.mp3");		//セレクトサウンド
	//decision_SE = LoadSoundMem("Resource/SE/decision.mp3");	//決定サウンド
}


//タイトルシーンの更新
eSceneType TitleSceneUpdate(void)
{
	//スペースキーが押された瞬間に、各画面に遷移する
	if (GetKeyInputState(KEY_INPUT_SPACE) == ePress)
	{
		return eInGame;	//インゲーム画面へ
	}
	if (GetKeyInputState(KEY_INPUT_X) == eRelease)
	{
		return eHelp;	//インゲーム画面へ
	}
	if (GetKeyInputState(KEY_INPUT_C) == ePress)
	{
		return eEnd;	//インゲーム画面へ
	}

	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetButtonInputState(XINPUT_BUTTON_X) == ePadInputState::ePress)
	{
		return eStageSelect;	//ステージセレクト画面へ
	}

	return eTitle;
}

//タイトルシーン描画
void TitleSceneDraw(void)
{
	//DrawGraph(0, 0, title_image, TRUE);								//背景
	/*DrawFormatString(50, 10, GetColor(255, 255, 255), "スペースでインゲーム画面へ");
	DrawFormatString(50, 60, GetColor(255, 255, 255), "Xでヘルプ画面へ");
	DrawFormatString(50, 110, GetColor(255, 255, 255), "Cでエンド 画面なし");*/

	DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, title.image, TRUE);
	DrawExtendFormatString(470, 360, 2.0, 2.0, GetColor(255, 255, 255), "Xボタンでステージセレクト画面へ");

}

//StageSelectを取得
const Title* GetTitle(void)
{
	return &title;
}