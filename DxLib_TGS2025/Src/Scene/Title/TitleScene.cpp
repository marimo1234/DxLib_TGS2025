#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/PadInputManager.h"
#include"../../../Effect/Fade.h"
#include "DxLib.h"
#include <math.h>

#define MOLE_MOVE_UP (0)
#define MOLE_MOVE_DOWN (1)
int title_image;		//タイトル画像のハンドル
int title_init_step = 0;
static Fade fade;
static bool is_fading = false;

void Play_Title_SE(int sound, int volume);
void ChangeCharExtrate_T(void);


Title title;

//タイトルシーンのリソース初期化
void TitleResourceInit(void)
{
	switch (title_init_step)
	{
	case 10:
		title.char_num = 0;
		title.bgm = LoadSoundMem("Resource/Sounds/title&stageselect_bgm.mp3");
		title.cursor_se = LoadSoundMem("Resource/Sounds/stage_select_cursor.mp3");
		title.button_se = LoadSoundMem("Resource/Sounds/stageselect_button.mp3");
		break;
	case 25:
		title.image = LoadGraph("Resource/Images/title_image.png");	//タイトル画像
		title.cursor_image = LoadGraph("Resource/Images/menu_cursor.png");	//タイトル画像
		title.char_image[0] = LoadGraph("Resource/Images/Start.png");	//タイトルの選択文字
		title.char_image[1] = LoadGraph("Resource/Images/Credits.png");	//タイトルの選択文字
		title.char_image[2] = LoadGraph("Resource/Images/End.png");	//タイトルの選択文字
		title.control_image = LoadGraph("Resource/Images/control_img.png");
		break;
	case 30:
		LoadDivGraph("Resource/images/title_mole_anim.png", 8, 8, 1, 80, 80, title.mole_image);

		break;
	case 35:
		title.name_image[0] = LoadGraph("Resource/Images/Title_Text_Anim0.png");	//タイトル画像
		title.name_image[1] = LoadGraph("Resource/Images/Title_Text_Anim1.png");	
		title.name_image[2] = LoadGraph("Resource/Images/Title_Text_Anim2.png");	
		title.name_image[3] = LoadGraph("Resource/Images/Title_Text_Anim3.png");	
		title.name_image[4] = LoadGraph("Resource/Images/Title_Text_Anim4.png");	
		title.name_image[5] = LoadGraph("Resource/Images/Title_Text_Anim5.png");	
		title.name_image[6] = LoadGraph("Resource/Images/Title_Text_Anim6.png");	
		title.name_image[7] = LoadGraph("Resource/Images/Title_Text_Anim7.png");	
		title.name_image[8] = LoadGraph("Resource/Images/Title_Text_Anim8.png");	
		title.name_image[9] = LoadGraph("Resource/Images/Title_Text_Anim9.png");	
		title.name_image[10] = LoadGraph("Resource/Images/Title_Text_Anim10.png");	
		title.name_image[11] = LoadGraph("Resource/Images/Title_Text_Anim11.png");	
		title.name_image[12] = LoadGraph("Resource/Images/Title_Text_Anim12.png");	
		break;
	case 40:
		title.name_image[13] = LoadGraph("Resource/Images/Title_Text_Anim13.png");	
		title.name_image[14] = LoadGraph("Resource/Images/Title_Text_Anim14.png");	
		title.name_image[15] = LoadGraph("Resource/Images/Title_Text_Anim15.png");	
		title.name_image[16] = LoadGraph("Resource/Images/Title_Text_Anim16.png");	
		title.name_image[17] = LoadGraph("Resource/Images/Title_Text_Anim17.png");	
		title.name_image[18] = LoadGraph("Resource/Images/Title_Text_Anim18.png");	
		title.name_image[19] = LoadGraph("Resource/Images/Title_Text_Anim19.png");	
		title.name_image[20] = LoadGraph("Resource/Images/Title_Text_Anim20.png");	
		title.name_image[21] = LoadGraph("Resource/Images/Title_Text_Anim21.png");	
		title.name_image[22] = LoadGraph("Resource/Images/Title_Text_Anim22.png");	
		title.name_image[23] = LoadGraph("Resource/Images/Title_Text_Anim23.png");
		title.name_image[24] = LoadGraph("Resource/Images/Title_Text_Anim24.png");	
		title.name_image[25] = LoadGraph("Resource/Images/Title_Text_Anim25.png");	
		title.name_image[26] = LoadGraph("Resource/Images/Title_Text_Anim26.png");	
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
	title.cursor_y = 455.0f + title.char_num * 90.0f;
	title.mole_num = 0;
	title.mole_count = 0;
	title.mole_move = 0;
	title.mole_active = GetRand(2) + 1;
	title.name_count = 0;
	title.name_num = 0;

	title.er[0] = 0.7f;
	for (int i = 1; i < 3; i++)
	{
		title.er[i] = 0.6f;
	}

	Play_Title_BGM();
	fade.Initialize(true);
	is_fading = true;
}

//タイトルシーンの更新
eSceneType TitleSceneUpdate(void)
{
	//選択バーの拡大率（フェードより前に置かないとフェード終わるまで処理が更新されない）
	ChangeCharExtrate_T();
	if (is_fading)
	{
		fade.Update();
		if (fade.GetEndFlag())
		{
			is_fading = false;
		}
		return eTitle;
	}

	TitleCursorUpdate();
	TitleNameAnimation();
	
	title.mole_count++;

	

	if (title.mole_count % 2 == 0)
	{
		if (title.mole_move == MOLE_MOVE_UP && title.mole_num != 6)
		{
			title.mole_num++;
		}
		else if (title.mole_move == MOLE_MOVE_DOWN && title.mole_num != 0)
		{
			title.mole_num--;
		}

		if (title.mole_num == 6&& title.mole_count>180)
		{
			title.mole_move = MOLE_MOVE_DOWN;
			title.mole_count = 0;
		}
		else if (title.mole_num == 0 && title.mole_count > 180)
		{
			title.mole_move = MOLE_MOVE_UP;
			title.mole_count = 0;
			title.mole_active = GetRand(2) + 1;
		}

		/*title.mole_count = 0;*/
	}


	PadInputManager* pad_input = PadInputManager::GetInstance();

	//タイトル画面の分岐
	if (title.char_num == 0 &&
		pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		Play_Title_SE(title.button_se, 100);
		return eStageSelect;	//　フェードアウトが終わるまではTitleのまま	
	}
	if (title.char_num == 1 &&
		pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		Play_Title_SE(title.button_se, 100);
		return eCredits;	//クレジット画面へ
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
	//　タイトル背景画像
	DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, title.image, TRUE);
	//　タイトル画像
	DrawRotaGraphF(650.0f, 180.0f, 1.10, 0.0, title.name_image[title.name_num], TRUE);
	//　Aボタンの画像
	DrawRotaGraphF(900.0f, 680.0f, 1.0, 0.0, title.control_image, TRUE);

	//　モグラの描画
	TitleMoleDraw();

	// タイトルのバーの画像
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraphF(640.0f, 450.0f + 90.0f * i, title.er[i], 0.0, title.char_image[i], TRUE);
	}

	// 矢印の画像
	DrawRotaGraphF(title.cursor_x, title.cursor_y , 1.0, 0.0, title.cursor_image, TRUE);

	//DrawFormatString(120, 120, GetColor(255, 255, 255), "%d", title.mole_count);

	fade.Draw();
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

		title.cursor_y = 455.0f + title.char_num * 90.0f;
	}
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
	{
		Play_Title_SE(title.cursor_se, 100);
		title.char_num++;
		title.char_num = title.char_num % 3;

		title.cursor_y = 455.0f + title.char_num * 90.0f;
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

//　タイトルのモグラ描画
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

//　タイトルアニメーション
void TitleNameAnimation(void)
{
	title.name_count++;
	if (title.name_count % 8 == 0 && title.name_num < 26)
	{
		title.name_num++;
	}
	if (title.name_count > 300)
	{
		title.name_count = 0;
		title.name_num = 0;
	}
}

//メニュー画面の文字の拡大率処理
void ChangeCharExtrate_T(void)
{
	for (int i = 0; i < 3; i++)
	{
		title.er[i] = 0.6f;
	}
	title.er[title.char_num] = 0.7f;
	
}