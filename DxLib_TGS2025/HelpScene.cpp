#include "HelpScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

//�w���v�V�[��������
void HelpSceneInit(void)
{

}

//�w���v�V�[���X�V
eSceneType HelpSceneUpdate(void)
{
	if (GetKeyInputState(KEY_INPUT_Z) == ePress)
	{
		return eInGame;								//�C���Q�[����
	}
	if (GetKeyInputState(KEY_INPUT_X) == ePress)
	{
		return eTitle;								//�^�C�g����ʂ�
	}
	return eHelp;
}


void HelpSceneDraw(void)
{
	SetFontSize(40);
	DrawString(1000, 550, "Z:�Q�[���J�n\nX:�^�C�g��\n", GetColor(255, 255, 255));			//�Q�[���J�n�ƃ^�C�g���ւ̕\��
	SetFontSize(16);
}