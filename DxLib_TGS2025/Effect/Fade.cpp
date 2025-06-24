#pragma once
#include "Fade.h"
#include "DxLib.h"

// �R���X�g���N�^
Fade::Fade()
	: alpha(0)
	, is_fade_in(true)
	, end_flag(false)
{

}

// �f�X�g���N�^
Fade::~Fade()
{

}

// ����������
void Fade::Initialize(bool set_fade_in_flag)
{
	is_fade_in = set_fade_in_flag;
	end_flag = false;

	if (is_fade_in)
	{
		alpha = 255;
	}
	else
	{
		alpha = 0;
	}
}

// �X�V����
void Fade::Update()
{
	if (is_fade_in == true)
	{
		// �t�F�[�h�C���i���邭�Ȃ�j
		if (alpha > 0)
		{
			alpha -= 5;

			if (alpha <= 0)
			{
				alpha = 0;
				// �t�F�[�h�I��
				end_flag = true;
			}
		}
	}
	else
	{
		// �t�F�[�h�A�E�g�i�Â��Ȃ�j
		if (alpha < 255)
		{
			alpha += 5;

			if (alpha >= 255)
			{
				alpha = 255;
				// �t�F�[�h�I��
				end_flag = true;
			}
		}
	}
}

// �`�揈��
void Fade::Draw() const
{
	// �`��u�����h���[�h���A���t�@�u�����h�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	// ��ʃT�C�Y�̍��F�l�p
	DrawBox(0, 0, 1280, 720, 0x000000, TRUE);
	// �`��u�����h���[�h���m�[�u�����h�ɂ���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// �I������
void Fade::Finalize()
{

}

// �t�F�[�h�I���t���O���擾����
bool Fade::GetEndFlag() const
{
	return end_flag;
}