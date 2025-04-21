#include "Player.h"
#include "../Utility/InputManager.h"
#include"../Utility/PadInputManager.h"
#include "../System/System.h"
#include "DxLib.h"



Player player;
int cursol;
static int move_lane_num = 1;
static int move_wait_time = 0;
int aif = 0;

void PlayerAnimationControl(void);

//�v���C���[�̏�����
void PlayerInit(void)
{
	//�����ݒ�
	player = {};
	player.position.x = 575.0f;				//�����ʒu�i�w�j
	player.position.y = 340.0f;				//�����ʒu�i�x�j
	player.box_size.x = 64.0f;				//��`�̑傫���i�w�j
	player.box_size.y = 128.0f;				//��`�̑傫���i�x�j
	player.velocity.x = 0.0f;	            //�v���C���[�̉��ړ�	
	player.velocity.y = 0.0f;				//�v���C���[�̏c�ړ�

	// �J�[�\���������̓ǂݍ���
	cursol = LoadGraph("Resource/Images/cursol.png");

	//�A�j���[�V�����̐ݒ�
	//animation_count = 0;
	//animation_num = 0;

	//�����摜�̐ݒ�
	//player.image = run_animation[animation_num];
}

//�v���C���[�̍X�V
void PlayerUpdate(void)
{
	CursolButtonMovement();

}

//�v���C���[�̕`��
void PlayerDraw(void)
{
	DrawGraph(player.position.x, player.position.y, cursol, TRUE);
	DrawFormatString(100, 100, GetColor(255, 255, 255), "%d", aif);
}

//�\����Player
const Player* GetPlayer(void)
{
	return &player;
}

void CursolButtonMovement()
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

  	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::ePress)
	{
		// �\���{�^���̍����������Ƃ�
		if (move_lane_num > 0)
		{
			// ���[����1���ɂ���
			move_lane_num--;

			aif++;
			// ���ړ�
			player.velocity.x = -75.0f;

			// �ړ���SE�i�����g���Ȃ炱���ɓ���Ăˁj
			
		}
	}
	else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
	{
		// �\���{�^���̉E���������Ƃ�
		if (move_lane_num < 3)
		{
			// ���[�����P�E�ɂ���
			move_lane_num++;

			// �E�ړ�
			player.velocity.x = 75.0f;

			// �ړ���SE�i���Ƃ���Ȃ�������Ăˁj
		}
	}
	else
	{
		// �ړ����x��0�ɖ߂�
		player.velocity.x = 0.0f;
	}

	// �v���C���[�ړ�
	player.position.x += player.velocity.x;
}

// �v���C���[�����郌�[�����擾����


