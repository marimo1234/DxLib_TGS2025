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
	//アイテム枠画像読み込み
	item_frame = LoadGraph("Resource/images/item_frame.png");
	//ピッケル画像読み込み
	pickaxe=LoadGraph("Resource/images/pickaxe.png");
	//石の地面画像の読み込み
	stonetile=LoadGraph("Resource/images/stone_tiles.png");

}
void ToolManagerUpdate(void)
{

}
void ToolDraw(void) 
{
	//アイテム枠の描画
	DrawRotaGraph(FRAME_X, FRAME_Y, 1.0, 0.0, item_frame, TRUE);
	//ピッケルの描画（アイテム枠）
	DrawRotaGraph(PICKAXE_X, PICKAXE_Y,0.15,0.0,pickaxe, TRUE);
	//石の地面の描画（アイテム枠）
	DrawRotaGraph(STONETILE_X, STONETILE_Y,0.3,0.0,stonetile, TRUE);
}