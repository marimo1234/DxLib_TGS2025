#include "CreditsScene.h"
#include "DxLib.h"
#include "../../Utility/PadInputManager.h"

Credits credits;

void Play_Credits_SE(int sound, int volume);

void CreditsSceneInit(void)
{
	//画像読み込み
	credits.credits_background_img= LoadGraph("Resource/images/credits_image.png");
	credits.B_back = LoadGraph("Resource/images/Bbacdk.png");
	//SE読み込み
	credits.button_se= LoadSoundMem("Resource/Sounds/stageselect_button.mp3");
}

eSceneType CreditsSceneUpdate(void)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//Bボタンでタイトルへ
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
	{
		//ボタンを押した音
		Play_Credits_SE(credits.button_se, 100);
		return eTitle;	//ステージセレクト画面へ
	}
	return eCredits;
}

void CreditsSceneDraw(void)
{
	DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, credits.credits_background_img, TRUE);
	DrawRotaGraphF(100.0f, 50.0f, 1.0, 0.0, credits.B_back, TRUE);
}

void Play_Credits_SE(int sound, int volume)
{
	ChangeVolumeSoundMem(volume, sound);
	PlaySoundMem(sound, DX_PLAYTYPE_BACK);
}