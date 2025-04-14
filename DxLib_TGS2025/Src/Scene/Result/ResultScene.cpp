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
	Output_Score();
	//�X�y�[�X�L�[����������
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
	unsigned int color;		//�F�̒l
	SetFontSize(80);
	//�X�R�A�̒l���O��菬�����Ƃ�
	if (result_score < 0)
	{
		color = GetColor(255, 50, 50);
	}
	//�X�R�A�̒l��0�ȏ�
	else
	{
		color = GetColor(100, 100, 230);
	}
	DrawFormatString(300, 200, color, "�X�R�A     %d", result_score); //�X�R�A�̕\��
	SetFontSize(40);
	DrawString(50, 650, "Z:�^�C�g�����", GetColor(255, 255, 255));	  //�^�C�g����ʂւ̕\��
}

//�\������X�R�A�̕ϐ���n��
int* Get_score(void)
{
	return &result_score;
}

//�X�R�A�̏o��
void Output_Score(void)
{
	FILE* fp;
	char High_score[100];
	errno_t err;
	err = fopen_s(&fp, "Resource/Data/HighScore.txt", "r");			//�ǂݎ��
	if (err == 0)
	{
		fgets(High_score, 100 - 1, fp);
		fclose(fp);
		DrawFormatString(450, 500, GetColor(100, 255, 100), "�n�C�X�R�A   %d", atoi(High_score));	//�n�C�X�R�A�\��
	}
	else
	{
		DrawFormatString(100, 500, GetColor(255, 255, 255), "err");	//�G���[�\��
	}
}