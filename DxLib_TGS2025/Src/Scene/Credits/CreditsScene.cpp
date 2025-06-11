#include "CreditsScene.h"
#include "DxLib.h"
#include "../../Utility/PadInputManager.h"

Credits credits;

void Play_Credits_SE(int sound, int volume);

void CreditsSceneInit(void)
{
	credits.button_se= LoadSoundMem("Resource/Sounds/stageselect_button.mp3");
}

eSceneType CreditsSceneUpdate(void)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
	{
		Play_Credits_SE(credits.button_se, 100);
		return eTitle;	//ステージセレクト画面へ
	}
	return eCredits;
}

void CreditsSceneDraw(void)
{
	DrawFormatString(100, 100, GetColor(255, 255, 255), "クレジット画面Bボタンでタイトルへ");
}

void Play_Credits_SE(int sound, int volume)
{
	ChangeVolumeSoundMem(volume, sound);
	PlaySoundMem(sound, DX_PLAYTYPE_BACK);
}