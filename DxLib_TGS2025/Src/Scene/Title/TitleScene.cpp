#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"
#include <math.h>

int title_image;		//�^�C�g���摜�̃n���h��
int cursor_number;		//�J�[�\���̔ԍ�
int cursor_y;			//�c�ʒu
int cursor_image;		//�J�[�\���摜�̃n���h��
int select_SE;			//�Z���N�g�̃T�E���h�n���h��
int decision_SE;		//����̃T�E���h�n���h��

void SelectCursor();
void Select_Sound();

//�^�C�g���V�[���̏�����
void TitleSceneInit(void)
{
	//�摜�̓ǂݍ���
	title_image = LoadGraph("Resource/Images/Title.png");	//�^�C�g���摜
	cursor_image = LoadGraph("Resource/Images/cursor.png");	//�J�[�\���摜

	//se�̓ǂݍ���
	select_SE = LoadSoundMem("Resource/SE/select.mp3");		//�Z���N�g�T�E���h
	decision_SE = LoadSoundMem("Resource/SE/decision.mp3");	//����T�E���h

	//�J�[�\���̏����ʒu�̐ݒ�
	cursor_number = 0;
	cursor_y = 350;

}


//�^�C�g���V�[���̍X�V
eSceneType TitleSceneUpdate(void)
{
	//�J�[�\���ʒu�̕ύX
	SelectCursor();

	//�X�y�[�X�L�[�������ꂽ�u�ԂɁA�e��ʂɑJ�ڂ���
	if (GetKeyInputState(KEY_INPUT_SPACE) == ePress)
	{
		//���肵���Ƃ��̉��i�o�b�N�O���E���h�ōĐ��j
		PlaySoundMem(decision_SE, DX_PLAYTYPE_BACK);
		switch (cursor_number)
		{
		case 0:
			return eInGame;		//�C���Q�[����ʂ�
		case 1:
			return eHelp;		//�w���v��ʂ�
		case 2:
			return eEnd;		//�I��
		default:
			break;
		}
	}
	return eTitle;
}

//�^�C�g���V�[���`��
void TitleSceneDraw(void)
{
	DrawGraph(0, 0, title_image, TRUE);								//�w�i
	DrawRotaGraph(750, cursor_y, 0.5, 0.0, cursor_image, TRUE);		//�J�[�\��
}

//�J�[�\���̈ʒu�ύX
void SelectCursor()
{
	//��󁪂������ꂽ��
	if (GetKeyInputState(KEY_INPUT_UP) == ePress)
	{
		Select_Sound();
		cursor_number--;
		if (cursor_number < 0)
		{
			cursor_number = 2;
		}
	}
	//��󁫂������ꂽ��
	if (GetKeyInputState(KEY_INPUT_DOWN) == ePress)
	{
		Select_Sound();
		cursor_number++;
		cursor_number = cursor_number % 3;
	}

	//�J�[�\���̍��W��ݒ�
	cursor_y = 360 + (cursor_number * 85);
}

//�I���̉�
void Select_Sound(void)
{
	//�Đ��i�o�b�N�O���E���h�j
	PlaySoundMem(select_SE, DX_PLAYTYPE_BACK);
}