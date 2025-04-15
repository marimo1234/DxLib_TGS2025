#include "Player.h"
#include "../Utility/InputManager.h"
#include "../System/System.h"
#include "DxLib.h"

#define		D_RUN_ANIM_MAX		(8)			//�摜�̕�����
#define		D_GROUND_POS		(550.0f)	//�n��
#define     D_DEFAULT_SPEED		(5.0f)		//����

Player player;
int run_animation[D_RUN_ANIM_MAX];		//����摜�̃n���h��
int animation_count;					//�t���[���J�E���g
int animation_num;						//�t���[���J�E���g�̗v�f
int situation_count = 0;				//�v���C���[�̏��

void PlayerRun(void);
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

	//�����Ă��邪�����̓ǂݍ���
	LoadDivGraph("Resource/Images/spr_ninja_run.png", D_RUN_ANIM_MAX, D_RUN_ANIM_MAX, 1, 128, 128, run_animation);

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
	//�A�j���[�V��������
	PlayerAnimationControl();
}

//�v���C���[�̕`��
void PlayerDraw(void)
{
	
}

//�\����Player
const Player* GetPlayer(void)
{
	return &player;
}

//�v���C���[�����鑬��
void PlayerRun(void)
{
	
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
