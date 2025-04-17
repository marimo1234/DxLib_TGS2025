#include "DxLib.h"
#include "Tool.h"

#define PICKAXE_X		(100)
#define PICKAXE_Y		(100)

int pickaxe_img;

void ToolInit(void)
{
	//ƒsƒbƒPƒ‹‰æ‘œ“Ç‚İ‚İ
	LoadGraph("Resource/images/pickacxe.png",pickaxe_img);
}
void ToolManagerUpdate(void)
{

}
void ToolDraw(void) 
{
	DrawRotaGraph(PICKAXE_X, PICKAXE_Y, 1.0, 0.0, pickaxe_img, TRUE);
}