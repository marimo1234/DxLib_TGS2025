#include "DxLib.h"
#include "System/System.h"
#include "Utility/InputManager.h"
#include "Scene/SceneManager.h"

//���C���֐�
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//�N������
	if (WakeUp() != TRUE)
	{
		//OutputDebugString��Log.txt�o�͂���֐�
		OutputDebugString("�A�v���P�[�V�����̏������Ɏ��s���܂���\n");
		return -1;
	}

	//�V�[���}�l�[�W���[�̏�����
	SceneManagerInitialize();

	//���[�J���ϐ���`
	float fixed_time = 0.0f;	//�t���[���o�ߎ���(s)

	//���C�����[�v
	//�E�B���h�E������ꂽor�V�[���}�l�[�W���[���ŏI����ԂŃ��[�v���I���
	while (ProcessMessage() != -1 && IsFinish() != TRUE)
	{
		//�P�t���[��������̎��Ԃ��v�Z
		CalcFrameTime();
		//�P�t���[��������̎��Ԃ����Z����
		fixed_time += GetDeltaSecond();

		//�U�Ofps���^���Č�
		if (fixed_time >= (1.0f / 60.0f))
		{
			fixed_time = 0.0f;	//�N���A

			//���͂̍X�V
			InputManagerUpdate();

			//��ʂ̏�����
			ClearDrawScreen();

			//�V�[���̍X�V
			SceneManagerUpdate();

			//����ʂ̓��e��\��ʂɔ��f
			ScreenFlip();

			//�G�X�P�[�v�L�[���������ƃ��[�v�I��
			if (GetKeyInputState(KEY_INPUT_ESCAPE) == eRelease)
			{
				break;
			}
		}
	}
	//DxLib�I��
	ShutDown();

	return 0;
}

