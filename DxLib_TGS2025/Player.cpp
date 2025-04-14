#include "Player.h"
#include "../Utility/InputManager.h"
#include "../System/System.h"
#include "DxLib.h"

#define		D_RUN_ANIM_MAX		(8)			//�摜�̕�����
#define		D_GROUND_POS		(550.0f)	//�n��
#define		D_JUMP_POWER		(-20.0f)	//�W�����v�̗͂̑傫��
#define     D_DEFAULT_SPEED		(5.0f)		//����

Player player;
int run_animation[D_RUN_ANIM_MAX];		//����摜�̃n���h��
int animation_count;					//�t���[���J�E���g
int animation_num;						//�t���[���J�E���g�̗v�f
int situation_count = 0;				//�v���C���[�̏��
int Jump_SE;							//�W�����vSE�̃n���h��

void PlayerRun(void);
void PlayerJump(void);
void PlayerAnimationControl(void);

//�v���C���[�̏�����
void PlayerInit(void)
{
	//�����ݒ�
	player = {};
	player.position.x = 120.0f;				//�����ʒu�i�w�j
	player.position.y = 490.0f;				//�����ʒu�i�x�j
	player.box_size.x = 64.0f;				//��`�̑傫���i�w�j
	player.box_size.y = 128.0f;				//��`�̑傫���i�x�j
	player.velocity.x = D_DEFAULT_SPEED;	//�v���C���[�̉��ړ�	
	player.velocity.y = 0.0f;				//�v���C���[�̏c�ړ�
	player.is_jump = TRUE;					//�v���C���[�̃W�����v�̐^�U
	player.situation = 0;					//�v���C���[�̏��

	//�����Ă��邪�����̓ǂݍ���
	LoadDivGraph("Resource/Images/spr_ninja_run.png", D_RUN_ANIM_MAX, D_RUN_ANIM_MAX, 1, 128, 128, run_animation);

	//se�̓ǂݍ���
	Jump_SE = LoadSoundMem("Resource/SE/jump.mp3");

	//�A�j���[�V�����̐ݒ�
	animation_count = 0;
	animation_num = 0;

	//�����摜�̐ݒ�
	player.image = run_animation[animation_num];
}

//�v���C���[�̍X�V
void PlayerUpdate(void)
{
	//���鏈��
	PlayerRun();
	//��ԏ���
	PlayerJump();
	//�A�j���[�V��������
	PlayerAnimationControl();
}

//�v���C���[�̕`��
void PlayerDraw(void)
{
	DrawRotaGraphF(player.position.x, player.position.y, 2.0, 0.0, player.image, TRUE);
}

//�\����Player
const Player* GetPlayer(void)
{
	return &player;
}

//�v���C���[�����鑬��
void PlayerRun(void)
{
	//��󁨂������ꂽ��
	if (GetKeyInputState(KEY_INPUT_RIGHT) == eHold)
	{
		//����
		if (player.situation == 0)
		{
			player.velocity.x = D_DEFAULT_SPEED * 2.5f;
		}
		//�A�C�e������
		else if (player.situation == 1)
		{
			player.velocity.x = D_DEFAULT_SPEED * 1.3f;
			situation_count++;
			if (situation_count >= 60)
			{
				player.situation = 0;
				situation_count = 0;
			}
		}
		//�X���C���ɓ���������
		else if (player.situation == 2)
		{
			player.velocity.x = D_DEFAULT_SPEED * 5.0f;
			situation_count++;
			if (situation_count >= 600)
			{
				player.situation = 0;
				situation_count = 0;
			}
		}

	}
	else
		//����
		if (player.situation == 0)
		{
			player.velocity.x = D_DEFAULT_SPEED;
		}
	//�A�C�e������
		else if (player.situation == 1)
		{
			player.velocity.x = D_DEFAULT_SPEED * 0.3f;
			situation_count++;
			if (situation_count >= 60)
			{
				player.situation = 0;
				situation_count = 0;
			}
		}
	//�X���C���ɓ���������
		else if (player.situation == 2)
		{
			player.velocity.x = D_DEFAULT_SPEED * 3.5f;
			situation_count++;
			if (situation_count >= 600)
			{
				player.situation = 0;
				situation_count = 0;
			}
		}
}


void PlayerJump(void)
{
	//�^���I�ȏd�͂�t�^����
	player.velocity.y += 1.0f;

	//SPACE�L�[�������ꂽ��
	if (GetKeyInputState(KEY_INPUT_SPACE) == ePress)
	{
		//�W�����v��Ԃ���Ȃ����
		if (player.is_jump != TRUE)
		{
			//������Ɉړ�����
			PlaySoundMem(Jump_SE, DX_PLAYTYPE_BACK);
			player.is_jump = TRUE;
			player.velocity.y = D_JUMP_POWER;
		}
	}

	//�v���C���[�̈ʒu���ړ����������炷
	player.position.y += player.velocity.y;

	//�n�ʂƐڒn���Ă��邩�H
	if (player.position.y >= D_GROUND_POS)
	{
		//�����Ԃɂ���
		player.is_jump = FALSE;
		player.position.y = D_GROUND_POS;
		player.velocity.y = 0.0f;
	}
}

//�摜�̐؂�ւ��̐���
void PlayerAnimationControl(void)
{
	animation_count++;
	//5�t���[���o�߂�����
	if (animation_count > 5)
	{
		//���̉摜�ԍ���ݒ�
		animation_count = 0;
		animation_num = ++animation_num % D_RUN_ANIM_MAX;
	}

	//�`��摜���w�肷��
	player.image = run_animation[animation_num];
}

//�v���C���[���A�C�e�����X���C���ɓ������Ă���̂�
void HitAction_Player(int* index)
{
	if (*index == 0 || *index == 1)
	{
		player.situation = 1;
	}
	if (*index == 9)
	{
		player.situation = 2;
	}
}
