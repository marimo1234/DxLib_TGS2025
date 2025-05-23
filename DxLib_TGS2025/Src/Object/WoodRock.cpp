#include "DxLib.h"
#include "WoodRock.h"
#include "../Utility/InputManager.h"
#include"../Utility/PadInputManager.h"
#include "../Object/Tool.h"
#include "../Object/Cursor.h"
#include "../Object/Map.h"
#include "../Object/Obstacle.h"
#include"../Scene/InGame/InGameScene.h"

#include <math.h>

#define WOODROCK_X_MAX (12)
#define WOODROCK_Y_MAX (7)

#define WOOD_ITEM_X (1170.0f)
#define WOOD_ITEM_Y (110.0f)
#define ROCK_ITEM_X (1170.0f)
#define ROCK_ITEM_Y (50.0f)
#define HIT_COOLTIME (30)


int woodrock_start;

Wood wood;
Rock rock;

void WoodHitCheck(const Tool* tool, const Cursor* cursor, const CreateStage* stage);
void RockHitCheck(const Tool* tool, const Cursor* cursor, const CreateStage* stage);

void WoodRockStart(const InGame* ingame);
void WoodRockSub(const Tool* tool);
void WoodRockAdd(const Tool* tool);
void WoodRockHitInit(const CreateStage* stage);
void WoodRockSub(const Tool* tool);
void GetMoleRockPosition(const Mole* mole);


//初期化
void WoodRockInit(void)
{
	//ヒットフラグ、ヒット数、アニメーション、削除フラグの初期化
	WoodRockHitInit(GetStage());

	//ムーブフラグの初期化
	wood.move_flag = false;
	rock.move_flag = false;

	wood.fps = 0;
	rock.fps = 0;
	//画像変数の初期化
	for (int i = 0; i < 3; i++)
	{
		wood.image[i] = -1;
		rock.image[i] = -1;
	}
	//配列番号の初期化
	wood.count_x = 0;
	wood.count_y = 0;
    rock.count_x = 0;
	rock.count_y = 0;

	//採ったアイテムの数の初期化
	wood.item_num = 0;
	rock.item_num = 0;

	//画像の読み込み
	wood.image[0] = LoadGraph("Resource/images/Wood0.png");
	wood.image[1] = LoadGraph("Resource/images/Wood1.png");
	wood.image[2] = LoadGraph("Resource/images/Wood2.png");
	wood.image[3] = LoadGraph("Resource/images/Wood3.png");

	rock.image[0] = LoadGraph("Resource/images/Rock0.png");
	rock.image[1] = LoadGraph("Resource/images/Rock1.png");
	rock.image[2] = LoadGraph("Resource/images/Rock2.png");
	rock.image[3] = LoadGraph("Resource/images/Rock3.png");

	rock.position.x = 600.0f;
	rock.position.y = 360.0f;
}

//更新
void WoodRockUpdate(void)
{
	//ゲームのスタートを受け取る
	WoodRockStart(GetInGame());

	//スタートがtrueになったなら
	if (woodrock_start == true)
	{  
		//木,岩のアニメーション
		WoodAnimation();
		RockAnimation();

		//ツールとカーソルとのHitチェック
		WoodHitCheck(Get_Tool(), GetCursor1(),GetStage());
		RockHitCheck(Get_Tool(), GetCursor1(),GetStage());

		//道路を作ったらアイテム化した数が減る
		WoodRockSub(Get_Tool());
		WoodRockAdd(Get_Tool());

		GetMoleRockPosition(GetMole());
	}
	else
	{
		//初期化
		WoodRockReset();
	}

	//ムーブフラグがtrueのとき
	if (wood.move_flag== true)
	{
		WoodMove();
	}
	if (rock.move_flag == true)
	{
		RockMove();
	}
}

//描画処理
void WoodRockDraw(void)
{
	//画像の描画
	//ムーブフラグがtrueのとき
	if (wood.move_flag == true)
	{
		DrawRotaGraphF(wood.position.x, wood.position.y, 1.0, 0.0, wood.image[3], TRUE);
	}
	if (rock.move_flag== true)
	{
		DrawRotaGraphF(rock.position.x, rock.position.y, 1.0, 0.0, rock.image[3], TRUE);
	}
	
	//アイテム化した木と岩の数の描画
	WoodRockItemCount();
	

}

//木のアニメーション
void WoodAnimation(void)
{
	switch (wood.hit_count[wood.count_x][wood.count_y])
	{
	case eHit0:// Hit数0
		wood.animation[wood.count_x][wood.count_y] = wood.image[0];

		if (wood.hit_flag[wood.count_x][wood.count_y] == true)
		{
			wood.animation[wood.count_x][wood.count_y] = wood.image[1];
			wood.fps++;
			if (wood.fps > HIT_COOLTIME)
			{
				wood.hit_count[wood.count_x][wood.count_y] = eHit1;
				wood.hit_flag[wood.count_x][wood.count_y] = false;//hitフラグをfalseにする
				wood.fps = 0;
			}

		}
		break;

	case eHit1:// Hit数1
		if (wood.hit_flag[wood.count_x][wood.count_y] == true)
		{
			wood.animation[wood.count_x][wood.count_y] = wood.image[2];
			wood.fps++;
			if (wood.fps > HIT_COOLTIME)
			{
				wood.hit_count[wood.count_x][wood.count_y] = eHit2;
				wood.hit_flag[wood.count_x][wood.count_y] = false;//hitフラグをfalseにする
				wood.fps = 0;
			}
		}

		break;

	case eHit2:// Hit数2
		
		if (wood.hit_flag[wood.count_x][wood.count_y] == true)
		{
				wood.item_num++;     //　HIT数が3になった時、アイテム化した物の数を+1する
				wood.hit_count[wood.count_x][wood.count_y] = eHit3;
				wood.hit_flag[wood.count_x][wood.count_y] = false;   //hitフラグをfalseにする
				wood.fps = 0;
		}
		break;

	case eHit3:// Hit数3
		
		wood.delete_flag[wood.count_x][wood.count_y] = true;//削除フラグをtrueにする
		wood.position.x = (float)wood.count_x * 80.0f + 200.0f;//現在のx座標を格納
		wood.position.y = (float)wood.count_y * 80.0f + 120.0f;//現在のy座標を格納
		wood.move_flag = true;//ムーブフラグをtrueにする
		wood.hit_count[wood.count_x][wood.count_y] = eHitEnd;

		break;

	default:
		break;
	}
}
//岩のアニメーション
void RockAnimation(void)
{

	switch (rock.hit_count[rock.count_x][rock.count_y])
	{
	case eHit0:// Hit数0
		rock.animation[rock.count_x][rock.count_y] = rock.image[0];
		if (rock.hit_flag[rock.count_x][rock.count_y] == true)
		{			
			rock.animation[rock.count_x][rock.count_y] = rock.image[1];

			rock.fps++;
			if (rock.fps > HIT_COOLTIME)
			{	
				rock.hit_count[rock.count_x][rock.count_y] = eHit1;
				rock.hit_flag[rock.count_x][rock.count_y] = false;//hitフラグをfalseにする
				rock.fps = 0;
			}
		}
		break;

	case eHit1:// Hit数1
		if (rock.hit_flag[rock.count_x][rock.count_y] == true)
		{
			rock.animation[rock.count_x][rock.count_y] = rock.image[2];
			rock.fps++;
			if (rock.fps > HIT_COOLTIME)
			{
				rock.hit_count[rock.count_x][rock.count_y] = eHit2;
				rock.hit_flag[rock.count_x][rock.count_y] = false;//hitフラグをfalseにする
				rock.fps = 0;
			}
		}

		break;

	case eHit2:// Hit数2
		
		if (rock.hit_flag[rock.count_x][rock.count_y] == true)
		{
			rock.item_num++;//HIT数が3になった時、アイテム化した物の数を+1する
			rock.hit_count[rock.count_x][rock.count_y] = eHit3;
			rock.hit_flag[rock.count_x][rock.count_y] = false;//hitフラグをfalseにする
		}
		break;

	case eHit3:// Hit数3
		rock.delete_flag[rock.count_x][rock.count_y] = true; //削除フラグをtrueにする
		rock.position.x = (float)rock.count_x * 80.0f + 200.0f; //現在のx座標を格納
		rock.position.y = (float)rock.count_y * 80.0f + 120.0f; //現在のy座標を格納
		rock.move_flag = true;//ムーブフラグをtrueにする
		rock.hit_count[rock.count_x][rock.count_y] = eHitEnd;//0に戻す
		
		break;
		
	default:
		break;
	}

}
//木の情報を取得
const Wood* GetWood(void)
{
	return &wood;
}
//岩の情報を取得
const Rock* GetRock(void)
{
	return &rock;
}

//処理をスタートするフラグ
void WoodRockStart(const InGame* ingame)
{
	if (ingame->start == true)
	{
		woodrock_start = true;
	}
	else
	{
		woodrock_start = false;
	}

}

//木、石が使われたときに所有数を減らす
void WoodRockSub (const Tool*tool)
{
	if (tool->rock_sub_flag == true)
	{
		rock.item_num--;
	}
	if (tool->wood_sub_flag == true)
	{
		wood.item_num--;
	}
}
//木、石が使われたときに所有数を増やす
void WoodRockAdd(const Tool* tool)
{
	if(tool->rock_add_flag == true)
	{
		rock.item_num++;
	}
	if (tool->wood_add_flag == true)
	{
		wood.item_num++;
	}
}

//木の当たり判定
void WoodHitCheck(const Tool* tool, const Cursor* cursor, const CreateStage* stage)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//カーソルの配列番号が木だったら
	if (stage->array[cursor->array_x][cursor->array_y] == 1);
	{

		for (int i = 0; i < WOODROCK_MAX; i++)
		{
			//カーソルと木の配列番号が一致したら
			if (cursor->array_x == stage->wood_x[i] && cursor->array_y == stage->wood_y[i])
			{
				//変更する配列番号を記憶
				wood.count_x = stage->wood_x[i];
				wood.count_y = stage->wood_y[i];
				//ツールがオノになっていたら
				if (tool->item_number == eAx)
				{
					//Aボタンが押されたなら
					if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
					{
						//Hitフラグをtrueにする
						wood.hit_flag[wood.count_x][wood.count_y] = true;
					}
				}
			}
		}


	}
}

//岩の当たり判定
void RockHitCheck(const Tool* tool, const Cursor* cursor, const CreateStage* stage)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//カーソルの配列番号が岩だったら
	if (stage->array[cursor->array_x][cursor->array_y] == 2);
	{
		for (int i = 0; i < WOODROCK_MAX; i++)
		{
			//カーソルと石の配列番号が一致したら
			if (cursor->array_x == stage->rock_x[i] && cursor->array_y == stage->rock_y[i])
			{
				//変更する配列番号を記憶
				rock.count_x = stage->rock_x[i];
				rock.count_y = stage->rock_y[i];
				//ツールがつるはしになっていたら
				if (tool->item_number == ePickaxe)
				{
					//Aボタンが押されたなら
					if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
					{
						//Hitフラグをtrueにする
						rock.hit_flag[rock.count_x][rock.count_y] = true;
					}
				}
			}
		}


	}
}

//アイテム化したアイテムをカウントする位置
void WoodRockItemCount(void)
{
	DrawRotaGraphF(WOOD_ITEM_X, WOOD_ITEM_Y, 1.0, 0.0, wood.image[3], TRUE);
	DrawExtendFormatString(1210, 115, 2.0, 2.0, GetColor(255, 255, 255), "%d", wood.item_num);
	DrawRotaGraphF(ROCK_ITEM_X, ROCK_ITEM_Y, 1.0, 0.0, rock.image[3], TRUE);
	DrawExtendFormatString(1210, 55, 2.0, 2.0, GetColor(255, 255, 255), "%d", rock.item_num);
}
//リセット
void WoodRockReset(void)
{

	//アイテム数の初期化
	wood.item_num = 0;
	rock.item_num = 0;

	//ムーブフラグの初期化
	wood.move_flag = false;
	rock.move_flag = false;


	//初期化
	WoodRockHitInit(GetStage());
	
}
//アイテム化した時の木の挙動
void WoodMove(void)
{
	float mx = WOOD_ITEM_X; //Xの最大値
	float my = WOOD_ITEM_Y; // Yの最小値
	float bx = wood.position.x;//ポジションの格納
	float by = wood.position.y;

	//二次関数（アイテムカウントしている位置を頂点と考える）
	float bp = pow(bx - mx, 2);
	float ba = (by - my) / bp;
	float y = ba * bp + my;

	//二次関数（x+1の座標を求める）
	float bx2 = bx + 1.0f;
	float bp2 = pow(bx2 - mx, 2);
	float y2 = ba * bp2 + my;

	//xが1増加した時のyの増加量を求める
	float fy = fabsf(y2 - y);

	wood.position.x += 7.0f;
	wood.position.y += 7.0f * -fy; 

	if (wood.position.y + 1 < my)
	{
		wood.move_flag = false;
	}

}
//アイテム化した時の岩の挙動
void RockMove(void)
{
	float mx = ROCK_ITEM_X; //Xの最大値
	float my = ROCK_ITEM_Y; // Yの最小値
	float bx = rock.position.x;//ポジションの格納
	float by = rock.position.y;

	//二次関数（アイテムカウントしている位置を頂点と考える）
	float bp = pow(bx - mx, 2);
	float ba = (by - my) / bp;
	float y = ba * bp + my;

	//二次関数（x+1の座標を求める）
	float bx2 = bx + 1.0f;
	float bp2 = pow(bx2 - mx, 2);
	float y2 = ba * bp2 + my;

	//xが1増加した時のyの増加量を求める
	float fy = fabsf(y2 - y);

		rock.position.x += 7.0f;
	rock.position.y += 7.0f * -fy; 

	if (rock.position.y+1 < my)
	{
		rock.move_flag = false;
	}
}


//Deleteフラグがtrueになったらfalseにする
void WR_Delete_Flag(void)
{
	if (wood.delete_flag[wood.count_x][wood.count_y] == true)
	{
		wood.delete_flag[wood.count_x][wood.count_y] = false;
	}
	if (rock.delete_flag[rock.count_x][rock.count_y] == true)
	{
		rock.delete_flag[rock.count_x][rock.count_y] = false;
	}
}
//Hitカウントの初期化
void WoodRockHitInit(const CreateStage* stage)
{
	for (int j = 0; j < WOODROCK_Y_MAX; j++)
	{
		for (int i = 0; i < WOODROCK_X_MAX; i++)
		{

			wood.hit_flag[i][j] = false;
			wood.animation[i][j] = wood.image[0];
			wood.delete_flag[i][j] = false;


			rock.hit_flag[i][j] = false;
			rock.animation[i][j] = rock.image[0];
			rock.delete_flag[i][j] = false;

			if (stage->array[i][j] == 1)
			{
				wood.hit_count[i][j] = eHit0;
			}
			else if (stage->array[i][j] == 2)
			{
				rock.hit_count[i][j] = eHit0;
			}
			else
			{
				wood.hit_count[i][j] = eHitEnd;
				rock.hit_count[i][j] = eHitEnd;
			}
		}
	}
}
//モグラ外資を置いた場所のHitカウントを初期化する
void GetMoleRockPosition(const Mole* mole)
{
	for (int j = 0; j < WOODROCK_Y_MAX; j++)
	{
		for (int i = 0; i < WOODROCK_X_MAX; i++)
		{
			if (mole->put_rock_flag[i][j] == true)
			{
				rock.hit_count[i][j] = eHit0;
				rock.animation[i][j] = rock.image[0];
			}
		}
	}
}