#include "ResultScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"
#include <stdlib.h>

int result_score;		//�\������X�R�A�̒l

//���U���g��ʏ�����
void ResultSceneInit(void)
{

}

//���U���g�V�[���̍X�V
eSceneType ResultSceneUpdate(void)
{
	//z�L�[����������
	if (GetKeyInputState(KEY_INPUT_Z) == ePress)
	{
		//�^�C�g����ʂ�
		return eTitle;
	}
	return eResult;
}

//���U���g�V�[���̕`��
void ResultSceneDraw(void)
{
	DrawFormatString(100, 100, GetColor(255, 255, 255), "z�Ń^�C�g����ʂ�");
}

