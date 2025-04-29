#include "DxLib.h"
#include "Tool.h"
#include "../Utility/InputManager.h"
#include "../Utility/PadInputManager.h"
#include "../Scene/InGame/InGameScene.h"
#include "../Object/WoodRock.h"
#include "../Object/Cursor.h"


#define PICKAXE_X		(1175)		//つるはしx座標
#define PICKAXE_Y		(675)		//つるはしy座標
#define FRAME_X			(1400)		//枠x座標
#define FRAME_Y			(1150)		//枠y座標
#define STONETILE_X		(937)		//石の地面x座標
#define STONETILE_Y		(670)		//石の地面y座標
#define LOGTILE_X		(1010)		//丸太の地面x座標
#define LOGTILE_Y		(670)		//丸太の地面y座標
#define AX_X			(1085)		//斧x座標
#define AX_Y			(670)		//斧y座標

int pickaxe_img;		//つるはしの画像ハンドル
int itemframe_img;		//枠の画像ハンドル
int road_img;			//石の地面の画像ハンドル
int wood_road_img;		//丸太の地面の画像ハンドル
int ax_img;				//斧の画像ハンドル
int frameselect_img;	//選択枠（アイテム）の画像ハンドル

int frameselect_x;		//選択枠のｘ座標
int frameselect_y;		//選択枠のｙ座標

float pickaxe_angle;	//つるはしの角度

int put_num;			//置いた数
int road_x;				//道のｘ座標
int road_y;				//道のｙ座標
int road_flag;			//道のフラグ

int tool_start;			//操作可能かの変数

//仮変数


Tool tool;

void const CursorToolCheck(const Cursor* cursor);
void Tool_Start(const InGame* ingame);
void const Road_Add_Num(const Rock* rock);
void const WoodRoad_Add_Num(const Wood* wood);


void ToolInit(void)
{
	//初期化
	frameselect_x = 952;
	frameselect_y = 670;
	tool.item_number = ePickaxe;
	tool.road_num = 0;
	tool.wood_road_num = 0;
	road_x = 500;
	road_y = 500;
	road_flag = false;
	tool_start = false;
	tool.rock_sub_flag = false;
	tool.wood_sub_flag = false;
	put_num = 0;
	//仮
	

	//アイテム枠画像読み込み
	itemframe_img = LoadGraph("Resource/images/item_frame.png");
	//ピッケル画像読み込み
	pickaxe_img=LoadGraph("Resource/images/pickaxe.png");
	//石の地面画像の読み込み
	road_img=LoadGraph("Resource/images/stone_tiles.png");
	//丸太の地面画像の読み込み
	wood_road_img = LoadGraph("Resource/images/Log.png");
	//斧の画像読み込み
	ax_img = LoadGraph("Resource/images/ax.png");
	//選択枠(アイテム)の画像読み込み
	frameselect_img = LoadGraph("Resource/images/frameselect.png");
}

void ToolManagerUpdate(void)
{
	Sub_Num();

	if (tool_start == true)
	{
		Move_Frame();
		//道路設置
		Put_Road();
	}
	else
	{
		Tool_Reset();
	}

	Tool_Start(GetInGame());
	Road_Add_Num(GetRock());
	WoodRoad_Add_Num(GetWood());
}

void ToolDraw(void) 
{
	//アイテム枠の描画
	DrawRotaGraph(FRAME_X, FRAME_Y, 1.0, 0.0, itemframe_img, TRUE);
	//つるはしの描画（アイテム枠）
	DrawRotaGraph(PICKAXE_X, PICKAXE_Y,0.1,0.0,pickaxe_img, TRUE);
	//道路の描画（アイテム枠）
	DrawRotaGraph(STONETILE_X, STONETILE_Y,0.65,0.0,road_img, TRUE);
	//丸太の地面の描画（アイテム枠）
	DrawRotaGraph(LOGTILE_X, LOGTILE_Y, 0.35, 0.0, wood_road_img , TRUE);
	//斧の描画（アイテム枠）
	DrawRotaGraph(AX_X, AX_Y, 0.15, 0.0, ax_img, TRUE);
	//枠選択の描画（アイテム枠）
	DrawRotaGraph(frameselect_x, frameselect_y, 0.15, 0.0, frameselect_img, TRUE);
	//道路描画
	Draw_Road();
	//道路の所持数
	DrawExtendFormatString(930, 600, 2.0, 2.0, GetColor(255, 255, 255), "%d", tool.road_num);
	//木の道の所持数
	DrawExtendFormatString(1010, 600, 2.0, 2.0, GetColor(255, 255, 255), "%d", tool.wood_road_num);

	//仮
}

void Move_Frame(void)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//ＲＢが押されたら
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

	//ＬＢが押されたら
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
	PadInputManager* pad_input = PadInputManager::GetInstance();
	
	//Aボタンが押されたら
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{

		//アイテムが道路なら
		if (tool.item_number == 0)
		{

			//道路の数が0より多いかつ、道路を置いた数が10を超えていないなら
			if (tool.road_num > 0&& put_num < 10)
			{
					road_flag = true;
					CursorToolCheck(GetCursor1());
					put_num++;
					tool.road_num--;
			}
		}
	}
}

//置いた道路描画
void Draw_Road(void)
{	
	//道路が置かれている状態なら
	if (road_flag == true)
	{
		//置かれている数だけ描画する
		for (int i = 0; i < put_num; i++)
		{
			DrawRotaGraph(tool.draw_x[i], tool.draw_y[i], 1.0, 0.0, road_img, TRUE);
		}
	}
}

//ゲームスタート受け取り
void Tool_Start(const InGame* ingame)
{
	//TRUEならtoolもTRUEに
	if (ingame->start == true)
	{
		tool_start = true;
	}

	//そうでなければFALSEに
	else
	{
		tool_start = false;
	}
}

//Toolの値渡し
const Tool* Get_Tool(void)
{
	return &tool;
}

void const CursorToolCheck(const Cursor* cursor)
{
	tool.draw_x[put_num] = cursor->position.x;
	tool.draw_y[put_num] = cursor->position.y;
}

//岩の道を増やす
void const Road_Add_Num(const Rock* rock)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//アイテムが道路なら
	if (tool.item_number == 0)
	{
		
		//岩の所持数が1以上なら
		if (rock->item_num >= 1)
		{

			//Ｂボタンが押されたら
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				tool.road_num++;
				tool.rock_sub_flag = true;
			}
		}
	}
}

//木の道を増やす
void const WoodRoad_Add_Num(const Wood* wood)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//アイテムが木の道路なら
	if (tool.item_number == 1)
	{

		//木の所持数が1以上なら
		if (wood->item_num >= 1)
		{

			//Ｂボタンが押されたら
			if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
			{
				tool.wood_road_num++;
				tool.wood_sub_flag = true;
			}
		}
	}
}

//数を増やした後にフラグを戻す
void Sub_Num(void)
{
	//岩の所持数をマイナス1するフラグを元に戻す
	if (tool.rock_sub_flag == true)
	{
		tool.rock_sub_flag = false;
	}
	//木の所持数をマイナス1するフラグを元に戻す
	if (tool.wood_sub_flag == true)
	{
		tool.wood_sub_flag = false;
	}
}

//ステージ切り替え時の値リセット
void Tool_Reset(void)
{
	tool.road_num = 0;
	tool.wood_road_num = 0;
	put_num = 0;
	road_flag = false;
}