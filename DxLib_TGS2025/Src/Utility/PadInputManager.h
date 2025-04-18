#pragma once

#define PAD_BUTTON_MAX (16)            // �Q�[���p�b�h�̃{�^���̍ő吔
#define PAD_STICK_MAX  (32767.0f)      // �X�e�B�b�N���X�����Ƃ��̍ő吔

enum class ePadInputState : unsigned char
{
	eNone,        // ������
	ePress,       // �{�^�����������u��
	eRelease,     // �{�^�����������u��
	eHold,        // �{�^�������������Ă���
};

class PadInputManager
{
private:
	static PadInputManager* instance;

	unsigned char now_button[PAD_BUTTON_MAX] = {};     // ���݂̃{�^���̓���
	unsigned char old_button[PAD_BUTTON_MAX] = {};     // �O��̃{�^���̓���

	int left_trigger = 0;                              // ���g���K�[
	int right_trigger = 0;                             // �E�g���K�[

private:
	// ���̂Ƃ��납��I�u�W�F�N�g���ł��Ȃ��悤�ɃR���X�g���N�^��private
	PadInputManager() = default;
	// �R�s�[�K�[�h
	// �R�s�[�R���X�g���N�^�̍폜
	PadInputManager(const PadInputManager&) = delete;
	// �R�s�[������Z�q�̍폜
	PadInputManager& operator = (const PadInputManager&) = delete;

public:
	~PadInputManager() = default;
public:
	// �C���X�^���X���擾
	static PadInputManager* GetInstance();
	// �C���X�^���X�̍폜
	static void DeleteInstance();

public:
	void Update();
public:
	// �{�^���̓��͏�Ԃ��擾
	ePadInputState GetButtonInputState(int button);

	// ���g���K�[�̒l���擾
	int GetLeftTrigger()const;
	// �E�g���K�[�̒l���擾
	int GetRightTrigger()const;

private:
	// ���͂��L���Ȕ͈͂��`�F�b�N
	bool CheckButtonRange(int button);

};