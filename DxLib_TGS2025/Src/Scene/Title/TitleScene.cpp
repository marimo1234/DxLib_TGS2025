#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/PadInputManager.h"
#include "DxLib.h"
#include <math.h>

int title_image;		//タイトル画像のハンドル
int title_init_step = 0;

void Play_Title_SE(int sound, int volume);

Title title;

//タイトルシーンのリソース初期化
void TitleResourceInit(void)
{
	switch (title_init_step)
	{
	case 0:
		title.char_num = 0;
		title.bgm = LoadSoundMem("Resource/Sounds/title&stageselect_bgm.mp3");
		title.cursor_se = LoadSoundMem("Resource/Sounds/stage_select_cursor.mp3");
		title.button_se = LoadSoundMem("Resource/Sounds/stageselect_button.mp3");
		break;
	case 1:
		title.image = LoadGraph("Resource/Images/title_image.png");	//タイトル画像
		title.name_image = LoadGraph("Resource/Images/Title_Text.png");	//タイトル画像
		title.cursor_image = LoadGraph("Resource/Images/menu_cursor.png");	//タイトル画像
		title.char_image[0] = LoadGraph("Resource/Images/Start.png");	//タイトルの選択文字
		title.char_image[1] = LoadGraph("Resource/Images/Credits.png");	//タイトルの選択文字
		title.char_image[2] = LoadGraph("Resource/Images/End.png");	//タイトルの選択文字
		title.control_image = LoadGraph("Resource/Images/control_img.png");
		break;
	case 2:
		title.mole_image[0] = LoadGraph("Resource/Images/title_mole00.png");
		title.mole_image[1] = LoadGraph("Resource/Images/title_mole01.png");
		title.mole_image[2] = LoadGraph("Resource/Images/title_mole02.png");
		title.mole_image[3] = LoadGraph("Resource/Images/title_mole03.png");
		title.mole_image[4] = LoadGraph("Resource/Images/title_mole04.png");
		title.mole_image[5] = LoadGraph("Resource/Images/title_mole05.png");
		title.mole_image[6] = LoadGraph("Resource/Images/title_mole06.png");
		break;
	default:
		break;
	}
	title_init_step++;
}

//タイトルシーンの初期化
void TitleSceneInit(void)
{
	title.cursor_x = 370.0f;
	title.cursor_y = 450.0f+title.char_num * 90.0f;
	title.mole_num = 0;
	title.mole_count = 0;
	title.mole_move = 0;
	title.mole_active = GetRand(2) + 1;
	
	Play_Title_BGM();
}

//タイトルシーンの更新
eSceneType TitleSceneUpdate(void)
{
	TitleCursorUpdate();
	title.mole_count++;

	if (title.mole_count % 3 == 0)
	{
		if (title.mole_move == 0 && title.mole_num != 5)
		{
			title.mole_num++;
		}
		else if (title.mole_move == 1 && title.mole_num != 0)
		{
			title.mole_num--;
		}

		if (title.mole_num == 5&& title.mole_count>180)
		{
			title.mole_move = 1;
			title.mole_count = 0;
		}
		else if (title.mole_num == 0 && title.mole_count > 180)
		{
			title.mole_move = 0;
			title.mole_count = 0;
			title.mole_active = GetRand(2) + 1;
		}

		/*title.mole_count = 0;*/
	}

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
		Play_Title_SE(title.button_se, 100);
		return eStageSelect;	//ステージセレクト画面へ
		title.char_num = 0;
	
	}
	if (title.char_num == 1 &&
		pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		Play_Title_SE(title.button_se, 100);
		return eCredits;	//クレジット画面へ
		title.char_num = 1;
	}
	if (title.char_num == 2 &&
		pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		Stop_BGM();
		Play_Title_SE(title.button_se, 100);
		return eEnd;	//エンド画面へ
	}
	return eTitle;
}

//タイトルシーン描画
void TitleSceneDraw(void)
{
	DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, title.image, TRUE);
	DrawRotaGraphF(650.0f, 180.0f, 0.55, 0.0, title.name_image, TRUE);
	DrawRotaGraphF(900.0f, 680.0f, 1.0, 0.0, title.control_image, TRUE);

	//モグラの描画
	TitleMoleDraw();

	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraphF(640.0f, 450.0f+90.0f*i, 0.6, 0.0, title.char_image[i], TRUE);
	}

	DrawRotaGraphF(title.cursor_x, title.cursor_y , 1.0, 0.0, title.cursor_image, TRUE);

	//DrawFormatString(120, 120, GetColor(255, 255, 255), "%d", title.mole_count);
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
		Play_Title_SE(title.cursor_se, 100);
		title.char_num--;
		if (title.char_num < 0)
		{
			title.char_num =2 ;
		}

		title.cursor_y = 450.0f + title.char_num * 90.0f;
	}
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
	{
		Play_Title_SE(title.cursor_se, 100);
		title.char_num++;
		title.char_num = title.char_num % 3;

		title.cursor_y = 450.0f + title.char_num * 90.0f;
	}
}

void Play_Title_BGM(void)
{
	if (CheckSoundMem(title.bgm) == 0)
	{
		ChangeVolumeSoundMem(100, title.bgm);
		PlaySoundMem(title.bgm, DX_PLAYTYPE_LOOP);
	}
}

void Play_Title_SE(int sound, int volume)
{
	ChangeVolumeSoundMem(volume, sound);
	PlaySoundMem(sound, DX_PLAYTYPE_BACK);
}

void Stop_BGM(void)
{
	StopSoundMem(title.bgm);
}

void TitleMoleDraw(void)
{
	DrawRotaGraphF(420.0f, 380.0f, 0.5, 0.0, title.mole_image[0], TRUE);
	DrawRotaGraphF(230.0f, 550.0f, 2.0, 0.0, title.mole_image[0], TRUE);
	DrawRotaGraphF(1020.0f, 450.0f, 1.0, 0.0, title.mole_image[0], TRUE);

	switch (title.mole_active)
	{
	case 1:
		DrawRotaGraphF(420.0f, 380.0f, 0.5, 0.0, title.mole_image[title.mole_num], TRUE);
		break;
	case 2:
		DrawRotaGraphF(230.0f, 550.0f, 2.0, 0.0, title.mole_image[title.mole_num], TRUE);
		break;
	case 3:
		DrawRotaGraphF(1020.0f, 450.0f, 1.0, 0.0, title.mole_image[title.mole_num], TRUE);
		break;
	}
	
}