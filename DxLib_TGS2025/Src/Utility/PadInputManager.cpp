#include"DxLib.h"
#include"PadInputManager.h"

// �ÓI�����o�ϐ��̏�����
PadInputManager* PadInputManager::instance = nullptr;

// �C���X�^���X���擾
PadInputManager* PadInputManager::GetInstance()
{
	if (instance == nullptr)
	{
		// �ŏ���1�񂾂��I�u�W�F�N�g�𐶐�����
		instance = new PadInputManager();
	}

	// ���Ԃ�Ԃ�
	return instance;
}

// �C���X�^���X�̍폜
void PadInputManager::DeleteInstance()
{
	if (instance != nullptr)
	{
		// �������̊J��
		delete instance;
		instance = nullptr;
	}
}

void PadInputManager::Update()
{
	// �Q�[���p�b�h�̏��
	XINPUT_STATE input;

	// �Q�[���p�b�h�̏�Ԃ��擾
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	// �������̈���R�s�[
	memcpy(old_button, now_button, (sizeof(char) * PAD_BUTTON_MAX));
	for (int i = 0; i < PAD_BUTTON_MAX; i++)
	{
		// ���݉����Ă���{�^���̍X�V
		now_button[i] = input.Buttons[i];
	}

	// ���g���K�[�̍X�V
	left_trigger = (int)input.LeftTrigger;

	// �E�g���K�[�̍X�V
	right_trigger = (int)input.RightTrigger;
}

// �{�^���̓��͏�Ԃ��擾
ePadInputState PadInputManager::GetButtonInputState(int button)
{
	// �{�^�����͂��L���Ȕ͈͂������珈�����s��
	if (CheckButtonRange(button))
	{
		if (old_button[button] == TRUE)
		{
			if (now_button[button] == TRUE)
			{
				// ���������Ă���
				return ePadInputState::eHold;
			}
			else
			{
				// �������u��
				return ePadInputState::eRelease;
			}
		}
		else
		{
			if (now_button[button] == TRUE)
			{
				// �������u��
				return ePadInputState::ePress;
			}
			else
			{
				// ������
				return ePadInputState::eNone;
			}
		}
	}
	// ������
	return ePadInputState::eNone;
}

// ���g���K�[�̒l���擾
int PadInputManager::GetLeftTrigger()const
{
	return left_trigger;
}

// �E�g���K�[�̒l���擾
int PadInputManager::GetRightTrigger()const
{
	return right_trigger;
}

// ���͂��L���Ȕ͈͉��`�F�b�N
bool PadInputManager::CheckButtonRange(int button)
{
	// ���݂̓��͒l��true��false���Ԃ�
	return (0 <= button && button < PAD_BUTTON_MAX);
}