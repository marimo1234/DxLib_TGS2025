#include "DxLib.h"
#include "Tool.h"
#include "../Utility/InputManager.h"
#include "../Utility/PadInputManager.h"
#include"../Scene/InGame/InGameScene.h"

#define PICKAXE_X		(1175)		//つるはしx座標
#define PICKAXE_Y		(675)		//つるはしy座標
#define FRAME_X			(1400)		//枠x座標
#define FRAME_Y			(1150)		//枠y座標
#define STONETILE_X		(950)		//石の地面x座標
#define STONETILE_Y		(655)		//石の地面y座標
#define LOGTILE_X		(1030)		//丸太の地面x座標
#define LOGTILE_Y		(675)		//丸太の地面y座標
#define AX_X			(1085)		//斧x座標
#define AX_Y			(670)		//斧y座標

int pickaxe_img;		//つるはしの画像ハンドル
int itemframe_img;		//枠の画像ハンドル
int stonetile_img;		//石の地面の画像ハンドル
int logtile_img;		//丸太の地面の画像ハンドル
int ax_img;				//斧の画像ハンドル
int frameselect_img;	//選択枠（アイテム）の画像ハンドル
int frameselect_x;		//選択枠のｘ座標
int frameselect_y;		//選択枠のｙ座標
float pickaxe_angle;	//つるはしの角度
int stone_x;			
int stone_y;
int road_flag;
int tool_start;

Tool tool;

void ToolInit(void)
{
	//初期化
	frameselect_x = 952;
	frameselect_y = 670;
	tool.item_number = ePickaxe;
	stone_x = 500;
	stone_y = 500;
	road_flag = FALSE;
	tool_start = FALSE;

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
	//選択枠(アイテム)の画像読み込み
	frameselect_img = LoadGraph("Resource/images/frameselect.png");
}

void ToolManagerUpdate(void)
{
	Move_Frame();
	Tool_Start(GetStart());
}

void ToolDraw(void) 
{
	//アイテム枠の描画
	DrawRotaGraph(FRAME_X, FRAME_Y, 1.0, 0.0, itemframe_img, TRUE);
	//つるはしの描画（アイテム枠）
	DrawRotaGraph(PICKAXE_X, PICKAXE_Y,0.1,0.0,pickaxe_img, TRUE);
	//道路の描画（アイテム枠）
	DrawRotaGraph(STONETILE_X, STONETILE_Y,0.3,0.0,stonetile_img, TRUE);
	//丸太の地面の描画（アイテム枠）
	DrawRotaGraph(LOGTILE_X, LOGTILE_Y, 0.4, 0.0, logtile_img , TRUE);
	//斧の描画（アイテム枠）
	DrawRotaGraph(AX_X, AX_Y, 0.15, 0.0, ax_img, TRUE);
	//枠選択の描画（アイテム枠）
	DrawRotaGraph(frameselect_x, frameselect_y, 0.15, 0.0, frameselect_img, TRUE);
	//道路描画
	Draw_Road();
}

void Move_Frame(void)
{
	//道路設置
	Put_Road();

	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetButtonInputState(XINPUT_BUTTON_RIGHT_SHOULDER) == ePadInputState::ePress)
	{
		switch (tool.item_number)
		{
		case eRoad:
			tool.item_number = eLog;
			break;
		case eLog:
			tool.item_number = eAx;
			break;
		case eAx:
			tool.item_number = ePickaxe;
			break;
		case ePickaxe:
			tool.item_number = eRoad;
			break;
		}
	}
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_LEFT_SHOULDER) == ePadInputState::ePress)
	{
		switch (tool.item_number)
		{
		case eRoad:
			tool.item_number = ePickaxe;
			break;
		case eLog:
			tool.item_number = eRoad;
			break;
		case eAx:
			tool.item_number = eLog;
			break;
		case ePickaxe:
			tool.item_number = eAx;
			break;
		}
	}
	//x座標変更
	frameselect_x = 952 + (tool.item_number * 73);
}

//道路を置く
void Put_Road(void)
{
	if (GetKeyInputState(KEY_INPUT_P) == ePress)
	{
		if (tool.item_number == 0)
		{ 
			road_flag = TRUE;
		}
	}
}

//置いた道路描画
void Draw_Road(void)
{
	if (road_flag == TRUE)
	{
		DrawRotaGraph(stone_x, stone_y, 0.3, 0.0, stonetile_img, TRUE);
	}
}

//ゲームスタート受け取り
void Tool_Start(const Start* start)
{
	if (start->GameStart == TRUE)
	{
		tool_start = TRUE;
	}
}

//
const Tool* Get_Tool(void)
{
	return &tool;
}