#include "DxLib.h"
#include "Tool.h"

#define PICKAXE_X		(1230)		//��͂�x���W
#define PICKAXE_Y		(670)		//��͂�y���W
#define FRAME_X			(1100)		//�gx���W
#define FRAME_Y			(700)		//�gy���W
#define STONETILE_X		(955)		//�΂̒n��x���W
#define STONETILE_Y		(655)		//�΂̒n��y���W
#define LOGTILE_X		(1035)		//�ۑ��̒n��x���W
#define LOGTILE_Y		(675)		//�ۑ��̒n��y���W
#define AX_X			(1160)		//��x���W
#define AX_Y			(670)		//��y���W

int pickaxe_img;
int itemframe_img;
int stonetile_img;
int logtile_img;
int ax_img;

void ToolInit(void)
{
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
}
void ToolManagerUpdate(void)
{

}
void ToolDraw(void) 
{
	//�A�C�e���g�̕`��
	DrawRotaGraph(FRAME_X, FRAME_Y, 1.0, 0.0, itemframe_img, TRUE);
	//�s�b�P���̕`��i�A�C�e���g�j
	DrawRotaGraph(PICKAXE_X, PICKAXE_Y,0.15,0.0,pickaxe_img, TRUE);
	//�΂̒n�ʂ̕`��i�A�C�e���g�j
	DrawRotaGraph(STONETILE_X, STONETILE_Y,0.3,0.0,stonetile_img, TRUE);
	//�ۑ��̒n�ʂ̕`��i�A�C�e���g�j
	DrawRotaGraph(LOGTILE_X, LOGTILE_Y, 0.4, 0.0, logtile_img , TRUE);
	//���̕`��i�A�C�e���g�j
	DrawRotaGraph(AX_X, AX_Y, 0.15, 0.0, ax_img, TRUE);
}