#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/PadInputManager.h"
#include "DxLib.h"
#include <math.h>

int title_image;		//タイトル画像のハンドル

Title title;

//タイトルシーンの初期化
void TitleSceneInit(void)
{

	title.char_num = 0;
	title.cursor_x = 370.0f;
	title.cursor_y = 450.0f;
	//画像の読み込み
	title.image = LoadGraph("Resource/Images/title_image.png");	//タイトル画像
	title.name_image = LoadGraph("Resource/Images/Title_Text.png");	//タイトル画像
	title.cursor_image = LoadGraph("Resource/Images/menu_cursor.png");	//タイトル画像
	title.char_image[0] = LoadGraph("Resource/Images/Start.png");	//タイトルの選択文字
	title.char_image[1] = LoadGraph("Resource/Images/Options.png");	//タイトルの選択文字
	title.char_image[2] = LoadGraph("Resource/Images/Exit.png");	//タイトルの選択文字


	//seの読み込み
	//select_SE = LoadSoundMem("Resource/SE/select.mp3");		//セレクトサウンド
	//decision_SE = LoadSoundMem("Resource/SE/decision.mp3");	//決定サウンド
}


//タイトルシーンの更新
eSceneType TitleSceneUpdate(void)
{
	TitleCursorUpdate();
	//スペースキーが押された瞬間に、各画面に遷移する
	if (GetKeyInputState(KEY_INPUT_SPACE) == ePress)
	{
		return eInGame;	//インゲーム画面へ
	}
	if (GetKeyInputState(KEY_INPUT_X) == eRelease)
	{
		//return eHelp;	//インゲーム画面へ
	}
	if (GetKeyInputState(KEY_INPUT_C) == ePress)
	{
		return eEnd;	//インゲーム画面へ
	}

	PadInputManager* pad_input = PadInputManager::GetInstance();

	//タイトル画面の分岐
	if (title.char_num == 0 &&
		pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		/*Play_Sound_Ingame(sound.decision, 100);*/
		return eStageSelect;	//ステージセレクト画面へ
		title.char_num = 0;
	
	}
	if (title.char_num == 1 &&
		pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		/*Play_Sound_Ingame(sound.decision, 100);*/
		//return eHelp;	//インゲーム画面へ
		title.char_num = 0;
	}
	if (title.char_num == 2 &&
		pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		/*Play_Sound_Ingame(sound.decision, 100);*/
		return eEnd;	//インゲーム画面へ
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
	DrawRotaGraphF(650.0f, 180.0f, 0.55, 0.0, title.name_image, TRUE);
	DrawExtendFormatString(470, 360, 2.0, 2.0, GetColor(255, 255, 255), "Aボタンでステージセレクト画面へ");
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraphF(640.0f, 450.0f+90.0f*i, 0.6, 0.0, title.char_image[i], TRUE);
	}

	DrawRotaGraphF(title.cursor_x, title.cursor_y , 1.0, 0.0, title.cursor_image, TRUE);
}

//StageSelectを取得
const Title* GetTitle(void)
{
	return &title;
}


//Goalした後のセレクト画面を出すフラグ
void TitleCursorUpdate(void)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
	{
		//Play_Sound_Title2(sound.select_move, 100);
		title.char_num--;
		if (title.char_num < 0)
		{
			title.char_num =2 ;
		}

		title.cursor_y = 450.0f + title.char_num * 90.0f;
	}
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
	{
		//Play_Sound_Title2(sound.select_move, 100);
		title.char_num++;
		title.char_num = title.char_num % 3;

		title.cursor_y = 450.0f + title.char_num * 90.0f;
	}
}