#include "DxLib.h"
#include "Tool.h"

#define PICKAXE_X		(1230)		//つるはしx座標
#define PICKAXE_Y		(670)		//つるはしy座標
#define FRAME_X			(1100)		//枠x座標
#define FRAME_Y			(700)		//枠y座標
#define STONETILE_X		(955)		//石の地面x座標
#define STONETILE_Y		(655)		//石の地面y座標
#define LOGTILE_X		(1035)		//丸太の地面x座標
#define LOGTILE_Y		(675)		//丸太の地面y座標
#define AX_X			(1160)		//斧x座標
#define AX_Y			(670)		//斧y座標

int pickaxe_img;
int itemframe_img;
int stonetile_img;
int logtile_img;
int ax_img;

void ToolInit(void)
{
	//アイテム枠画像読み込み
	itemframe_img = LoadGraph("Resource/images/item_frame.png");
	//ピッケル画像読み込み
	pickaxe_img=LoadGraph("Resource/images/pickaxe.png");
	//石の地面画像の読み込み
	stonetile_img=LoadGraph("Resource/images/stone_tiles.png");
	//丸太の地面画像の読み込み
	logtile_img = LoadGraph("Resource/images/Log.png");
	//斧の画像読み込み
	ax_img = LoadGraph("Resource/images/ax.png");
}
void ToolManagerUpdate(void)
{

}
void ToolDraw(void) 
{
	//アイテム枠の描画
	DrawRotaGraph(FRAME_X, FRAME_Y, 1.0, 0.0, itemframe_img, TRUE);
	//ピッケルの描画（アイテム枠）
	DrawRotaGraph(PICKAXE_X, PICKAXE_Y,0.15,0.0,pickaxe_img, TRUE);
	//石の地面の描画（アイテム枠）
	DrawRotaGraph(STONETILE_X, STONETILE_Y,0.3,0.0,stonetile_img, TRUE);
	//丸太の地面の描画（アイテム枠）
	DrawRotaGraph(LOGTILE_X, LOGTILE_Y, 0.4, 0.0, logtile_img , TRUE);
	//斧の描画（アイテム枠）
	DrawRotaGraph(AX_X, AX_Y, 0.15, 0.0, ax_img, TRUE);
}