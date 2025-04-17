#include "DxLib.h"
#include "Tool.h"

#define PICKAXE_X		(1230)
#define PICKAXE_Y		(670)
#define FRAME_X			(1100)
#define FRAME_Y			(700)
#define STONETILE_X		(955)
#define STONETILE_Y		(655)

int pickaxe;
int item_frame;
int stonetile;

void ToolInit(void)
{
	//�A�C�e���g�摜�ǂݍ���
	item_frame = LoadGraph("Resource/images/item_frame.png");
	//�s�b�P���摜�ǂݍ���
	pickaxe=LoadGraph("Resource/images/pickaxe.png");
	//�΂̒n�ʉ摜�̓ǂݍ���
	stonetile=LoadGraph("Resource/images/stone_tiles.png");

}
void ToolManagerUpdate(void)
{

}
void ToolDraw(void) 
{
	//�A�C�e���g�̕`��
	DrawRotaGraph(FRAME_X, FRAME_Y, 1.0, 0.0, item_frame, TRUE);
	//�s�b�P���̕`��i�A�C�e���g�j
	DrawRotaGraph(PICKAXE_X, PICKAXE_Y,0.15,0.0,pickaxe, TRUE);
	//�΂̒n�ʂ̕`��i�A�C�e���g�j
	DrawRotaGraph(STONETILE_X, STONETILE_Y,0.3,0.0,stonetile, TRUE);
}