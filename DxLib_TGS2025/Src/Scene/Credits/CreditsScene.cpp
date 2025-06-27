#include "CreditsScene.h"
#include "DxLib.h"
#include "../../Utility/PadInputManager.h"
#include"../Title/TitleScene.h"
#include"../../../Effect/Fade.h"

Credits credits;
static Fade fade;
static bool is_fading = false;

void Play_Credits_SE(int sound, int volume);
void Play_Credits_BGM(const Title* title);

void CreditsSceneInit(void)
{
	credits.title_x = 60.0f;
	credits.title_y = 160.0f;
	credits.url_x = 60.0f;
	credits.url_y = 190.0f;
	//�摜�ǂݍ���
	credits.credits_background_img= LoadGraph("Resource/images/credits_image.png");
	credits.B_back = LoadGraph("Resource/images/Bbacdk.png");
	//SE�ǂݍ���
	credits.button_se= LoadSoundMem("Resource/Sounds/stageselect_button.mp3");

	Play_Credits_BGM(GetTitle());
	fade.Initialize(true);
	is_fading = true;
}

eSceneType CreditsSceneUpdate(void)
{
	fade.Update();
	if (fade.GetEndFlag())
	{
		is_fading = false;
	}
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//B�{�^���Ń^�C�g����
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
	{
		//�{�^������������
		Play_Credits_SE(credits.button_se, 100);
		return eTitle;	//�X�e�[�W�Z���N�g��ʂ�
	}
	return eCredits;
}

void CreditsSceneDraw(void)
{
	DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, credits.credits_background_img, TRUE);
	DrawRotaGraphF(1200.0f, 670.0f, 1.0, 0.0, credits.B_back, TRUE);

	//�N���W�b�g
	//�^�C�g��
	DrawExtendFormatString(100.0f, 40.0f, 3.0, 3.0,
		GetColor(255, 255, 255), "�g�p�f��");
	//���O��URL
	//BANNER KOUBOU
	DrawExtendFormatString(credits.title_x, credits.title_y, 2.0, 2.0,
		GetColor(255, 255, 255), "BANNER KOUBOU");
	DrawExtendFormatString(credits.url_x, credits.url_y, 1.5, 1.5,
		GetColor(0, 255, 0), "https://www.bannerkoubou.com/photoeditor/opacity/");

	//BEIZ images
	DrawExtendFormatString(credits.title_x, credits.title_y + 80.0 * 1, 2.0, 2.0,
		GetColor(255, 255, 255), "BEIZ images");
	DrawExtendFormatString(credits.url_x, credits.url_y + 80.0 * 1, 1.5, 1.5,
		GetColor(0, 255, 0), "https://www.beiz.jp/");

	//PixelGaro  �s�N�Z���K���[
	DrawExtendFormatString(credits.title_x, credits.title_y + 80.0 * 2, 2.0, 2.0,
		GetColor(255, 255, 255), "PixelGaro  �s�N�Z���K���[");
	DrawExtendFormatString(credits.url_x, credits.url_y + 80.0 * 2, 1.5, 1.5,
		GetColor(0, 255, 0), "https://hpgpixer.jp/");

	//�摜�̐F���i�g�[���j�ύX
	DrawExtendFormatString(credits.title_x, credits.title_y + 80.0 * 3, 2.0, 2.0,
		GetColor(255, 255, 255), "�摜�̐F���i�g�[���j�ύX");
	DrawExtendFormatString(credits.url_x, credits.url_y + 80.0 * 3, 1.5, 1.5,
		GetColor(0, 255, 0), "https://tomari.org/main/java/image1.html");

	//123APPS
	DrawExtendFormatString(credits.title_x, credits.title_y + 80.0 * 4, 2.0, 2.0,
		GetColor(255, 255, 255), "123APPS");
	DrawExtendFormatString(credits.url_x, credits.url_y + 80.0 * 4, 1.5, 1.5,
		GetColor(0, 255, 0), "https://123apps.com/ja/#google_vignette");

	//���b�R�c�[���Y
	DrawExtendFormatString(credits.title_x, credits.title_y + 80.0 * 5, 2.0, 2.0,
		GetColor(255, 255, 255), "���b�R�c�[���Y");
	DrawExtendFormatString(credits.url_x, credits.url_y + 80.0 * 5, 1.5, 1.5,
		GetColor(0, 255, 0), "https://rakko.tools/");

	fade.Draw();
}

void Play_Credits_SE(int sound, int volume)
{
	ChangeVolumeSoundMem(volume, sound);
	PlaySoundMem(sound, DX_PLAYTYPE_BACK);
}


//BGM���Đ�
void Play_Credits_BGM(const Title* title)
{
	if (CheckSoundMem(title->bgm) == 0)
	{
		ChangeVolumeSoundMem(100, title->bgm);
		PlaySoundMem(title->bgm, DX_PLAYTYPE_BACK);
	}
}