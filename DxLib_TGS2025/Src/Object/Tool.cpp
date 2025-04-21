#include "DxLib.h"
#include "Tool.h"
#include "../Utility/InputManager.h"

#define PICKAXE_X		(1175)		//��͂�x���W
#define PICKAXE_Y		(675)		//��͂�y���W
#define FRAME_X			(1400)		//�gx���W
#define FRAME_Y			(1150)		//�gy���W
#define STONETILE_X		(950)		//�΂̒n��x���W
#define STONETILE_Y		(655)		//�΂̒n��y���W
#define LOGTILE_X		(1030)		//�ۑ��̒n��x���W
#define LOGTILE_Y		(675)		//�ۑ��̒n��y���W
#define AX_X			(1085)		//��x���W
#define AX_Y			(670)		//��y���W

int pickaxe_img;		//��͂��̉摜�n���h��
int itemframe_img;		//�g�̉摜�n���h��
int stonetile_img;		//�΂̒n�ʂ̉摜�n���h��
int logtile_img;		//�ۑ��̒n�ʂ̉摜�n���h��
int ax_img;				//���̉摜�n���h��
int frameselect_img;	//�I��g�i�A�C�e���j�̉摜�n���h��
int frameselect_x;		//�I��g�̂����W
int frameselect_y;		//�I��g�̂����W
int item_number;		//�A�C�e���i���o�[
float pickaxe_angle;	//��͂��̊p�x
int stone_x;
int stone_y;
int road_flag;

void ToolInit(void)
{
	//������
	frameselect_x = 952;
	frameselect_y = 670;
	item_number = 3;
	stone_x = 500;
	stone_y = 500;
	road_flag = FALSE;

	//�A�C�e���g�摜�ǂݍ���
	itemframe_img = LoadGraph("Resource/images/item_frame.png");
	//�s�b�P���摜�ǂݍ���
	pickaxe_img=LoadGraph("Resource/images/pickaxe.png");
	//�΂̒n�ʉ摜�̓ǂݍ���
	stonetile_img=LoadGraph("Resource/images/stone_tiles.png");
	//�ۑ��̒n�ʉ摜�̓ǂݍ���
	logtile_img = LoadGraph("Resource/images/Log.png");
	//���̉摜�ǂݍ���
	ax_img = LoadGraph("Resource/images/ax.png");
	//�I��g(�A�C�e��)�̉摜�ǂݍ���
	frameselect_img = LoadGraph("Resource/images/frameselect.png");
}

void ToolManagerUpdate(void)
{
	Move_Frame();
}

void ToolDraw(void) 
{
	//�A�C�e���g�̕`��
	DrawRotaGraph(FRAME_X, FRAME_Y, 1.0, 0.0, itemframe_img, TRUE);
	//��͂��̕`��i�A�C�e���g�j
	DrawRotaGraph(PICKAXE_X, PICKAXE_Y,0.1,0.0,pickaxe_img, TRUE);
	//���H�̕`��i�A�C�e���g�j
	DrawRotaGraph(STONETILE_X, STONETILE_Y,0.3,0.0,stonetile_img, TRUE);
	//�ۑ��̒n�ʂ̕`��i�A�C�e���g�j
	DrawRotaGraph(LOGTILE_X, LOGTILE_Y, 0.4, 0.0, logtile_img , TRUE);
	//���̕`��i�A�C�e���g�j
	DrawRotaGraph(AX_X, AX_Y, 0.15, 0.0, ax_img, TRUE);
	//�g�I���̕`��i�A�C�e���g�j
	DrawRotaGraph(frameselect_x, frameselect_y, 0.15, 0.0, frameselect_img, TRUE);
	//���H�`��
	Draw_Road();
}

void Move_Frame(void)
{
	//���H�ݒu
	Put_Road();

	//�E������������A�C�e�����E��
	if (GetKeyInputState(KEY_INPUT_RIGHT) == ePress)
	{
		item_number++;
		if (item_number > 3)
		{
			item_number = 0;
		}
	}
	//��������������A�C�e��������
	if (GetKeyInputState(KEY_INPUT_LEFT) == ePress)
	{
		item_number--;
		if (item_number < 0)
		{
			item_number = 3;
		}
	}
	//x���W�ύX
	frameselect_x = 952 + (item_number * 73);
}

//���H��u��
void Put_Road(void)
{
	if (GetKeyInputState(KEY_INPUT_P) == ePress)
	{
		if (item_number == 0)
		{ 
			road_flag = TRUE;
		}
	}
}

//�u�������H�`��
void Draw_Road(void)
{
	if (road_flag == TRUE)
	{
		DrawRotaGraph(stone_x, stone_y, 0.3, 0.0, stonetile_img, TRUE);
	}
}