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