#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"
#include <math.h>

int title_image;		//�^�C�g���摜�̃n���h��

//�^�C�g���V�[���̏�����
void TitleSceneInit(void)
{
	//�摜�̓ǂݍ���
	//title_image = LoadGraph("Resource/Images/Title.png");	//�^�C�g���摜

	//se�̓ǂݍ���
	//select_SE = LoadSoundMem("Resource/SE/select.mp3");		//�Z���N�g�T�E���h
	//decision_SE = LoadSoundMem("Resource/SE/decision.mp3");	//����T�E���h
}


//�^�C�g���V�[���̍X�V
eSceneType TitleSceneUpdate(void)
{
	//�X�y�[�X�L�[�������ꂽ�u�ԂɁA�e��ʂɑJ�ڂ���
	if (GetKeyInputState(KEY_INPUT_SPACE) == ePress)
	{
		return eInGame;	//�C���Q�[����ʂ�
	}
	return eTitle;
}

//�^�C�g���V�[���`��
void TitleSceneDraw(void)
{
	//DrawGraph(0, 0, title_image, TRUE);								//�w�i
	DrawFormatString(100, 100, GetColor(255, 255, 255), "�X�y�[�X�ŃC���Q�[����ʂ�");
}