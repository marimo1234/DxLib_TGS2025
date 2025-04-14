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
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    unsigned int Cr;

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    Cr = GetColor(0, 0, 255);
    int red, blue, green;

    for (int x = 0; x < 640; x += 20) {
        for (int y = 0; y < 480; y += 20) {
            red = GetRand(255);
            blue = GetRand(255);
            green = GetRand(0);
            DrawBoxAA(x, y, x + 18, y + 18, GetColor(red, green, blue), TRUE);

        }
    }


    WaitKey();

    DxLib_End();

    return 0;
}