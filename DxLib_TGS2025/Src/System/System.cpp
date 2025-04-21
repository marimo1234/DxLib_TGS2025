#include "System.h"
#include "ProjectConfig.h"
#include "DxLib.h"

LONGLONG old_time;
LONGLONG now_time;
float delta_second;


int WakeUp(void)
{
	//Log.txt�̐��������Ȃ�
	SetOutApplicationLogValidFlag(TRUE);
	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);
	//�E�B���h�E�T�C�Y�����߂�
	SetGraphMode(D_WINDOW_SIZE_X, D_WINDOW_SIZE_Y, D_COLOR_BIT);
	//�E�B���h�E���A�N�e�B�u�łȂ��Ă�����
	SetAlwaysRunFlag(TRUE);
	//Dx���C�u����������
	if (DxLib_Init() == -1)
	{
		//�ȏ��ʒm
		return FALSE;
	}
	//����ʂ���`����n�߂�
	SetDrawScreen(DX_SCREEN_BACK);


	//�O���[�o���ϐ��̏�����
	old_time = 0LL;
	now_time = 0LL;
	delta_second = 0.0f;

	//����ɋN���ł������Ƃ�ʒm����
	return TRUE;
}


void ShutDown(void)
{
	//Dx���C�u�����g�p���I��
	DxLib_End();
}

void CalcFrameTime(void)
{
	//���݂̋N�����Ԃ��L�^(�ʕb)
	now_time = GetNowHiPerformanceCount();

	//�i����-�O��j���P�t���[��������̎���
	//�ʕb����b�ɕϊ�
	delta_second = (float)(now_time - old_time) * 1.0e-6f;

	//�O�񎞊Ԃ̍X�V
	old_time = now_time;
}

//�P�t���[��������̎���
const float GetDeltaSecond(void)
{
	return delta_second;
}