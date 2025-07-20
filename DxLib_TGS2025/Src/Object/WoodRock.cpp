#include "DxLib.h"
#include "WoodRock.h"
#include "../Utility/InputManager.h"
#include"../Utility/PadInputManager.h"
#include "../Object/Tool.h"
#include "../Object/Cursor.h"
#include "../Object/Map.h"
#include "../Object/Obstacle.h"
#include "../Object/Goal.h"
#include "../Object/Car.h"
#include"../Scene/InGame/InGameScene.h"

#include <math.h>

#define WOODROCK_X_MAX (12)//X配列のMAX
#define WOODROCK_Y_MAX (7)//Y配列のMAX

#define WOOD_ITEM_X (960.0f)//アイテム表示の座標
#define WOOD_ITEM_Y (660.0f)
#define ROCK_ITEM_X (880.0f)
#define ROCK_ITEM_Y (660.0f)

#define HIT_COOLTIME (27)//Hitクールタイム


bool woodrock_start;//処理スタートするフラグ
bool woodrock_menu_flag;//メニューが開かれたときのフラグ
bool woodrock_operable_flag;//Goal、GameOverが開かれたときのフラグ

Wood wood;
Rock rock;
WoodRock_SE woodrock_se;

void WoodHitCheck(const Tool* tool, const Cursor* cursor, const CreateStage* stage);
void RockHitCheck(const Tool* tool, const Cursor* cursor, const CreateStage* stage);

void WoodRockStart(const InGame* ingame, const Goal* goal, const GameOver* gameover,  const Car* car);
void WoodRockSub(const Tool* tool);
void WoodRockAdd(const Tool* tool);
void WoodRockHitInit(const CreateStage* stage);
void GetMolePutPosition(const Mole* mole);
void Play_Sound_WoodRock(int sound, int volume);


//初期化
void WoodRockInit(void)
{
	woodrock_start = false;
	woodrock_menu_flag = false;
	//ヒットフラグ、ヒット数、アニメーション、削除フラグの初期化
	WoodRockHitInit(GetStage());

	//配列番号の初期化
	wood.count_x = 0;
	wood.count_y = 0;
    rock.count_x = 0;
	rock.count_y = 0;

	//採ったアイテムの数の初期化
	wood.item_num = 0;
	rock.item_num = 0;

	//エフェクト変数の初期化
	wood.effect_num = 0;
	wood.effect_count = 0;
	rock.effect_num = 0;
	rock.effect_count = 0;
	wood.effect_flag = false;
	rock.effect_flag = false;

	
}

//画像読み込み
void WoodRockResourceInit(void)
{
	//画像の読み込み
	wood.image[0] = LoadGraph("Resource/images/Wood0.png");
	wood.image[1] = LoadGraph("Resource/images/Wood1.png");
	wood.image[2] = LoadGraph("Resource/images/Wood2.png");
	wood.image[3] = LoadGraph("Resource/images/Wood3.png");

	rock.image[0] = LoadGraph("Resource/images/Rock0.png");
	rock.image[1] = LoadGraph("Resource/images/Rock1.png");
	rock.image[2] = LoadGraph("Resource/images/Rock2.png");
	rock.image[3] = LoadGraph("Resource/images/Rock3.png");

	wood.effect_image[0] = LoadGraph("Resource/images/reef_effect1.png");
	wood.effect_image[1] = LoadGraph("Resource/images/reef_effect2.png");
	wood.effect_image[2] = LoadGraph("Resource/images/reef_effect3.png");
	wood.effect_image[3] = LoadGraph("Resource/images/reef_effect4.png");

	rock.effect_image[0] = LoadGraph("Resource/images/rock_fragment1.png");
	rock.effect_image[1] = LoadGraph("Resource/images/rock_fragment2.png");
	rock.effect_image[2] = LoadGraph("Resource/images/rock_fragment3.png");
	rock.effect_image[3] = LoadGraph("Resource/images/rock_fragment4.png");

	rock.put_effect_image[0] = LoadGraph("Resource/images/put_rock_0.png");
	rock.put_effect_image[1] = LoadGraph("Resource/images/put_rock_1.png");
	rock.put_effect_image[2] = LoadGraph("Resource/images/put_rock_2.png");
	rock.put_effect_image[3] = LoadGraph("Resource/images/put_rock_3.png");
	rock.put_effect_image[4] = LoadGraph("Resource/images/put_rock_4.png");
	rock.put_effect_image[5] = LoadGraph("Resource/images/put_rock_5.png");

	wood.put_effect_image[0] = LoadGraph("Resource/images/put_rock_0.png");
	wood.put_effect_image[1] = LoadGraph("Resource/images/put_rock_1.png");
	wood.put_effect_image[2] = LoadGraph("Resource/images/put_rock_2.png");
	wood.put_effect_image[3] = LoadGraph("Resource/images/put_rock_3.png");
	wood.put_effect_image[4] = LoadGraph("Resource/images/put_rock_4.png");
	wood.put_effect_image[5] = LoadGraph("Resource/images/put_rock_5.png");
	//サウンド読み込み
	wood.break_wood = LoadSoundMem("Resource/Sounds/break_wood7.mp3");
	rock.break_rock = LoadSoundMem("Resource/Sounds/break_rock2.mp3");
	woodrock_se.swing = LoadSoundMem("Resource/Sounds/swing.mp3");

	rock.itemnum_bg_image = LoadGraph("Resource/images/ItemNum_bg_image.png");
}
//更新
void WoodRockUpdate(void)
{
	//ゲームのスタートを受け取る
	WoodRockStart(GetInGame(),GetGoal(),GetGameOver(),GetCar());

	//スタートがtrueになったなら
	if (woodrock_start == true && woodrock_menu_flag == false && woodrock_operable_flag == true)
	{
		//木,岩のアニメーション
		WoodAnimation(wood.count_x,wood.count_y);
		RockAnimation(rock.count_x, rock.count_y);

		//ツールとカーソルとのHitチェック
		WoodHitCheck(Get_Tool(), GetCursor1(), GetStage());
		RockHitCheck(Get_Tool(), GetCursor1(), GetStage());

		//道路を作ったらアイテム化した数が減る
		WoodRockSub(Get_Tool());
		WoodRockAdd(Get_Tool());

		//モグラが岩を置く場所を取得
		GetMolePutPosition(GetMole());

		
	}
	else if(woodrock_start == false && woodrock_menu_flag == false)
	{
		//初期化
		WoodRockReset();
	}

	//ムーブフラグがtrueのとき
	for (int j = 0; j < WOODROCK_Y_MAX; j++)
	{
		for (int i = 0; i < WOODROCK_X_MAX; i++)
		{
			if (wood.move_flag[i][j] == true)
			{
				//アイテム表示位置まで放物線を描く
				WoodMove(i,j);
			}
			if (rock.move_flag[i][j] == true)
			{
				//アイテム表示位置まで放物線を描く
				RockMove(i,j);

			}
		}
	}

	
}

//描画処理
void WoodRockDraw(void)
{
	//ItemNumの透過カラー
	//DrawRotaGraphF(1190.0f, 80.0f, 1.0, 0.0, rock.itemnum_bg_image, TRUE);

	//ムーブフラグがtrueのとき
	for (int j = 0; j < WOODROCK_Y_MAX; j++)
	{
		for (int i = 0; i < WOODROCK_X_MAX; i++)
		{
			if (wood.move_flag[i][j] == true && woodrock_operable_flag == true)
			{
				DrawRotaGraphF(wood.position_x[i][j], wood.position_y[i][j], 1.0, 0.0, wood.image[3], TRUE);
			}
			if (rock.move_flag[i][j] == true && woodrock_operable_flag == true)
			{
				DrawRotaGraphF(rock.position_x[i][j], rock.position_y[i][j], 1.0, 0.0, rock.image[3], TRUE);
			}
		}
	}
	
	//アイテム化した木と岩の数の描画
	WoodRockItemCount();

	//エフェクトの描画
	WoodRockEffectDraw();	

	//DrawFormatString(200, 200, GetColor(255, 255, 255), "%d %d %d", rock.fps[3][2],rock.fps[5][2], rock.fps[7][2]);
		//DrawFormatString(200, 200, GetColor(255, 255, 255), "%f\n%f\n%d", rock.add_x[8][4], rock.add_x[1][2],wood.effect_count);

}

//木のアニメーション
void WoodAnimation(int x, int y)
{
	switch (wood.hit_count[x][y])
	{
	case eHit0:// Hit数0
		wood.animation[x][y] = wood.image[0];
		//ヒットフラグがtrueなら
		if (wood.hit_flag[x][y] == true)
		{
			wood.animation[x][y] = wood.image[1];//画像を変える
			wood.effect_flag = true;
			wood.fps[x][y]++;
			if (wood.fps[x][y] > HIT_COOLTIME)//クールタイムを超えたら次のヒットに移行
			{
				wood.hit_count[x][y] = eHit1;
				wood.effect_flag = false;
				wood.hit_flag[x][y] = false;//hitフラグをfalseにする
				wood.fps[x][y] = 0;
			}

		}
		break;

	case eHit1:// Hit数1
		//ヒットフラグがtrueなら
		if (wood.hit_flag[x][y] == true)
		{
			wood.animation[x][y] = wood.image[2];//画像を変える
			wood.effect_flag = true;
			wood.fps[x][y]++;
			if (wood.fps[x][y] > HIT_COOLTIME)//クールタイムを超えたら次のヒットに移行
			{
				wood.hit_count[x][y] = eHit2;
				wood.effect_flag = false;
				wood.hit_flag[x][y] = false;//hitフラグをfalseにする
				wood.fps[x][y] = 0;
			}
		}

		break;

	case eHit2:// Hit数2
		//ヒットフラグがtrueなら
		if (wood.hit_flag[x][y] == true)
		{
			wood.animation[x][y] = wood.image[3];//画像を変える
			wood.fps[x][y]++;
			wood.effect_flag = true;
			
			if (wood.fps[x][y] > HIT_COOLTIME)//クールタイムを超えたら次のヒットに移行
			{
				wood.hit_count[x][y] = eHit3;
				wood.effect_flag = false;
				wood.hit_flag[x][y] = false;   //hitフラグをfalseにする
				wood.fps[x][y] = 0;
				
			}
			
		}
		break;

	case eHit3:// Hit数3
		
		wood.delete_flag[x][y] = true;//削除フラグをtrueにする
		wood.position_x[x][y] = (float)wood.count_x * 80.0f + 200.0f;//現在のx座標を格納
		wood.position_y[x][y] = (float)wood.count_y * 80.0f + 120.0f;//現在のy座標を格納
		wood.add_y[x][y] = fabs((7.0f - (float)y) * 0.8f);
		wood.move_flag[x][y] = true;//ムーブフラグをtrueにする
		wood.hit_count[x][y] = eHitEnd;

		break;

	default:
		break;
	}
}
//岩のアニメーション
void RockAnimation(int x, int y)
{

	switch (rock.hit_count[x][y])
	{
	case eHit0:// Hit数0
		rock.animation[x][y] = rock.image[0];
		//ヒットフラグがtrueなら
		if (rock.hit_flag[x][y] == true)
		{
			rock.animation[x][y] = rock.image[1];//画像を変える
			rock.effect_flag = true;
			rock.fps[x][y]++;
			if (rock.fps[x][y] > HIT_COOLTIME)//クールタイムを超えたら次のヒットに移行
			{

				rock.hit_count[x][y] = eHit1;
				rock.effect_flag = false;
				rock.hit_flag[x][y] = false;//hitフラグをfalseにする
				rock.fps[x][y] = 0;
			}
		}
		break;

	case eHit1:// Hit数1
		//ヒットフラグがtrueなら
		if (rock.hit_flag[x][y] == true)
		{
			rock.animation[x][y] = rock.image[2];//画像を変える
			rock.effect_flag = true;
			rock.fps[x][y]++;
			if (rock.fps[x][y] > HIT_COOLTIME)//クールタイムを超えたら次のヒットに移行
			{
				rock.hit_count[x][y] = eHit2;
				rock.effect_flag = false;
				rock.hit_flag[x][y] = false;//hitフラグをfalseにする
				rock.fps[x][y] = 0;
			}
		}

		break;

	case eHit2:// Hit数2
		//ヒットフラグがtrueなら
		if (rock.hit_flag[x][y] == true)
		{
			rock.animation[x][y] = rock.image[3];//画像を変える
			rock.fps[x][y]++;
			rock.effect_flag = true;
			if (rock.fps[x][y] > HIT_COOLTIME)//クールタイムを超えたら次のヒットに移行
			{
				rock.hit_count[x][y] = eHit3;
				rock.effect_flag = false;
				rock.hit_flag[x][y] = false;//hitフラグをfalseにする
				rock.fps[x][y] = 0;
			}
		}
		break;

	case eHit3:// Hit数3
		rock.delete_flag[x][y] = true; //削除フラグをtrueにする
		rock.position_x[x][y] = (float)rock.count_x * 80.0f + 200.0f; //現在のx座標を格納
		rock.position_y[x][y] = (float)rock.count_y * 80.0f + 120.0f; //現在のy座標を格納
		rock.add_y[x][y] = fabs((7.0f - (float)y )* 0.8f);
		rock.move_flag[x][y] = true;//ムーブフラグをtrueにする
		rock.hit_count[x][y] = eHitEnd;//0に戻す
		
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
void WoodRockStart(const InGame* ingame, const Goal*goal,const GameOver*gameover ,const Car*car)
{
	//処理をスタート
	if (ingame->start == true&& ingame->menu_flag == false && ingame->mitibiki_flag == false)
	{
		woodrock_start = true;
		woodrock_operable_flag = true;

	}
	//処理を止める
	else if(ingame->start == false && ingame->menu_flag == false)
	{
		woodrock_start = false;
	}
	//メニューフラグを見る
	woodrock_menu_flag = ingame->menu_flag;

	//処理を止める
	if (goal->print_flag == true || gameover->image_flag == true || car->goal_flag == true||
		ingame->mitibiki_flag==true|| car->direction == eStop)
	{
		woodrock_operable_flag = false;
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

	//Aボタンが押されたなら
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		//ツールがオノになっていたら
		if (tool->item_number == eAx)
		{
			//カーソルの配列番号が木だったら
			if (stage->array[cursor->array_x][cursor->array_y] == 1 &&
				wood.fps[wood.count_x][wood.count_y] == 0)
			{

				for (int i = 0; i < WOODROCK_MAX; i++)
				{
					//カーソルと木の配列番号が一致したら
					if (cursor->array_x == stage->wood_x[i] && cursor->array_y == stage->wood_y[i])
					{
						//変更する配列番号を記憶
						wood.count_x = stage->wood_x[i];
						wood.count_y = stage->wood_y[i];
					}

						//Hitフラグをtrueにする
						wood.hit_flag[wood.count_x][wood.count_y] = true;

						//hit時の斧が木を叩くSEを追加
						Play_Sound_WoodRock(wood.break_wood, 150);
				}
			}
			//空振りの音を入れる
			else if (stage->array[cursor->array_x][cursor->array_y] != 1)
			{
				Play_Sound_WoodRock(woodrock_se.swing, 120);
			}
		}
	}
}

//岩の当たり判定
void RockHitCheck(const Tool* tool, const Cursor* cursor, const CreateStage* stage)
{
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//Aボタンが押されたなら
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		//ツールがつるはしになっていたら
		if (tool->item_number == ePickaxe)
		{
			/*カーソルの配列番号が岩だったら*/
			if (stage->array[cursor->array_x][cursor->array_y] == 2 &&
				rock.fps[rock.count_x][rock.count_y] == 0)
			{

				for (int i = 0; i < WOODROCK_MAX; i++)
				{
					//カーソルと石の配列番号が一致したら
					if (cursor->array_x == stage->rock_x[i] && cursor->array_y == stage->rock_y[i])
					{
						//変更する配列番号を記憶
						rock.count_x = stage->rock_x[i];
						rock.count_y = stage->rock_y[i];
					}

					//Hitフラグをtrueにする
					rock.hit_flag[rock.count_x][rock.count_y] = true;

					//hit時のツルハシが岩を叩くSEを追加
					Play_Sound_WoodRock(rock.break_rock, 120);

				}

			}
			//空振りの音を入れる
			else if (stage->array[cursor->array_x][cursor->array_y] != 2)
			{
				Play_Sound_WoodRock(woodrock_se.swing, 120);
			}
		}
	}
}

//アイテム化したアイテムをカウントする位置

void WoodRockItemCount(void)
{
	//DrawRotaGraphF(WOOD_ITEM_X, WOOD_ITEM_Y, 1.0, 0.0, wood.image[3], TRUE);
	///*DrawExtendFormatString(1210, 115, 2.0, 2.0, GetColor(255, 255, 255), "%d", wood.item_num);*/
	//DrawRotaGraphF(ROCK_ITEM_X, ROCK_ITEM_Y, 1.0, 0.0, rock.image[3], TRUE);
	///*DrawExtendFormatString(1210, 55, 2.0, 2.0, GetColor(255, 255, 255), "%d", rock.item_num);*/
}
//リセット
void WoodRockReset(void)
{
	woodrock_start = false;
	woodrock_menu_flag = false;
	woodrock_operable_flag = false;
	//アイテム数の初期化
	wood.item_num = 0;
	rock.item_num = 0;

	wood.effect_num = 0;
	wood.effect_count = 0;

	wood.effect_flag = false;
	rock.effect_flag = false;

	//初期化
	WoodRockHitInit(GetStage());

}

//アイテム化した時の木の挙動
void WoodMove(int x, int y)
{
	//二次関数のグラフの公式”y=a(x-p)^2+q"
	wood.move_count[x][y]++;
	float mx = WOOD_ITEM_X; //Xの目的地
	float my = WOOD_ITEM_Y; // Yの最大値
	float bx = wood.position_x[x][y];//ポジションの格納
	float by = wood.position_y[x][y];

	//二次関数（アイテムカウントしている位置を頂点と考える）
	float bp = pow(by - my, 2);
	float ba = (bx - mx) / bp;
	float x1 = ba * bp + mx;

	//二次関数（y+1の座標を求める）
	float by2 = by + 1.0f;
	float bp2 = pow(by2 - my, 2);
	float x2 = ba * bp2 + mx;

	//xが1増加した時のyの増加量を求める
	float fx = fabsf(x2 - x1);

	//20フレーム経ったら移動開始する
	if (wood.move_count[x][y] > 20)
	{
		//切った木のX座標が左か右か
		if (ba > 0)
		{
			wood.position_x[x][y] += wood.add_y[x][y]*1.5 * -fx;
		}
		else if (ba < 0)
		{
			wood.position_x[x][y] += wood.add_y[x][y]*1.5 * fx;
		}

		wood.position_y[x][y] += wood.add_y[x][y]*1.5;
	}
	//Yの最小値を上回ったら終了
	if (wood.position_y[x][y] > my)
	{
		wood.item_num++; //HIT数が3になった時、アイテム化した物の数を+1する
		wood.move_count[x][y] = 0;
		wood.move_flag[x][y] = false;
	}

}
//アイテム化した時の岩の挙動
void RockMove(int x, int y)
{
	//二次関数のグラフの公式”y=a(x-p)^2+q"
	rock.move_count[x][y]++;
	float mx = ROCK_ITEM_X; //Xの目的地
	float my = ROCK_ITEM_Y; // Yの最大値
	float bx = rock.position_x[x][y];//ポジションの格納
	float by = rock.position_y[x][y];

	//二次関数（アイテムカウントしている位置を頂点と考える）
	float bp = pow(by - my, 2);
	float ba = (bx - mx) / bp;
	float x1 = ba * bp + mx;

	//二次関数（y+1の座標を求める）
	float by2 = by + 1.0f;
	float bp2 = pow(by2 - my, 2);
	float x2 = ba * bp2 + mx;

	//xが1増加した時のyの増加量を求める
	float fx = fabsf(x2 - x1);

	//20フレーム経ったら移動開始する
	if (rock.move_count[x][y] > 20)
	{
		//掘った岩のX座標が左か右か
		if (ba > 0)
		{
			rock.position_x[x][y] += rock.add_y[x][y] * 1.5 * -fx;
		}
		else if (ba < 0)
		{
			rock.position_x[x][y] += rock.add_y[x][y] * 1.5 * fx;
		}

		rock.position_y[x][y] += rock.add_y[x][y] * 1.5;
	}
	//Yの最小値を上回ったら終了
	if (rock.position_y[x][y] > my)
	{
		rock.item_num++; //HIT数が3になった時、アイテム化した物の数を+1する
		rock.move_count[x][y] = 0;
		rock.move_flag[x][y] = false;
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

			//ヒット変数の初期化
			wood.hit_flag[i][j] = false;
			wood.animation[i][j] = wood.image[0];
			wood.delete_flag[i][j] = false;
			wood.fps[i][j] = 0;

			rock.hit_flag[i][j] = false;
			rock.animation[i][j] = rock.image[0];
			rock.delete_flag[i][j] = false;
			rock.fps[i][j] = 0;

			//ムーブ変数の初期化
			wood.move_flag[i][j] = false;
			wood.move_count[i][j] = 0;
			wood.position_x[i][j] = 0.0f;
			wood.position_y[i][j] = 0.0f;
			wood.add_y[i][j] = 0.0f;

			rock.move_flag[i][j] = false;
			rock.move_count[i][j] = 0;
			rock.position_x[i][j] = 0.0f;
			rock.position_y[i][j] = 0.0f;
			rock.add_y[i][j] = 0.0f;

			//木の揺れるアニメーション変数の初期化
			wood.add_anim_x[i][j] = 0;
			wood.sway_anim[i][j] = 0;

			//Hit数の初期化
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
			//モグラが岩を置くエフェクトの変数初期化
			wood.put_effect_num[i][j] = -1;
			wood.put_effect_count[i][j] = 0;
			rock.put_effect_num[i][j] = -1;
			rock.put_effect_count[i][j] = 0;
			

		}
	}
}

//モグラが岩・木を置いた場所のHitカウントを初期化する
void GetMolePutPosition(const Mole* mole)
{
	for (int j = 0; j < WOODROCK_Y_MAX; j++)
	{
		for (int i = 0; i < WOODROCK_X_MAX; i++)
		{
			if (mole->put_rock_flag[i][j] == true)
			{
				rock.put_effect_flag[i][j] = true;
				rock.hit_flag[i][j] = false;
				rock.hit_count[i][j] = eHit0;
				rock.animation[i][j] = rock.image[0];
			}
			else if (mole->put_wood_flag[i][j] == true)
			{
				wood.put_effect_flag[i][j] = true;
				wood.hit_flag[i][j] = false;
				wood.hit_count[i][j] = eHit0;
				wood.animation[i][j] = wood.image[0];
			}
			
		}
	}
	
	
}

//木のエフェクト
void WoodEffect(int x, int y)
{
	if (wood.effect_num < 4)
	{
		wood.effect_count++;

		if (wood.effect_count > 3)
		{
			wood.effect_num++;
			wood.effect_count = 0;

		}

		SwayWoodAnim(x,y);
	
	}
	else
	{
		wood.effect_count = 0;
		wood.effect_flag = false;
		wood.sway_anim[x][y] = 0;
		wood.add_anim_x[x][y] = 0;
	}

	DrawRotaGraph(x * 80 + 200, y * 80 + 120, 1.0, 0.0, wood.effect_image[wood.effect_num], TRUE);
}

//岩のエフェクト
void RockEffect(int x, int y)
{
	
	if (rock.effect_num < 4)
	{
		rock.effect_count++;

		if (rock.effect_count > 3)
		{
			rock.effect_num++;
			rock.effect_count = 0;

		}
	}
	else
	{
		rock.effect_count = 0;
		rock.effect_flag = false;
	}
	
	DrawRotaGraph(x * 80 + 200, y * 80 + 120, 1.0, 0.0, rock.effect_image[rock.effect_num],TRUE);
}

//モグラが木を置くときのエフェクト
void PutWoodEffect(int x, int y)
{
	if (wood.put_effect_num[x][y] < 5)
	{
		wood.put_effect_count[x][y]++;

		if (wood.put_effect_count[x][y] > 5)
		{
			wood.put_effect_num[x][y]++;
			wood.put_effect_count[x][y] = 0;
		}
	}
	else
	{
		wood.put_effect_count[x][y] = 0;
		wood.put_effect_flag[x][y] = false;
	}
	DrawRotaGraph(x * 80 + 200, y * 80 + 120, 1.0, 0.0, wood.put_effect_image[wood.put_effect_num[x][y]], TRUE);

}

//モグラが岩を置くときのエフェクト
void PutRockEffect(int x, int y)
{

	if (rock.put_effect_num[x][y] < 5)
	{
		rock.put_effect_count[x][y]++;

		if (rock.put_effect_count[x][y] > 5)
		{
			rock.put_effect_num[x][y]++;
			rock.put_effect_count[x][y] = 0;
		}
	}
	else
	{
		rock.put_effect_count[x][y] = 0;
		rock.put_effect_flag[x][y] = false;
	}
	DrawRotaGraph(x * 80 + 200, y * 80 + 120, 1.0, 0.0, rock.put_effect_image[rock.put_effect_num[x][y]], TRUE);


}
//エフェクトの描画
void WoodRockEffectDraw(void) 
{
	if (wood.effect_flag == true)
	{
		WoodEffect(wood.count_x, wood.count_y);
	}
	else
	{
		wood.effect_num = 0;
	}

	if (rock.effect_flag == true)
	{
		RockEffect(rock.count_x, rock.count_y);
	}
	else
	{
		rock.effect_num = 0;
	}


	for (int j = 0; j < WOODROCK_Y_MAX; j++)
	{
		for (int i = 0; i < WOODROCK_X_MAX; i++)
		{
			if (rock.put_effect_flag[i][j] == true)
			{
				PutRockEffect(i, j);
				PutWoodEffect(i, j);
			}
			else
			{
				rock.put_effect_num[i][j] = -1;
				wood.put_effect_num[i][j] = -1;
			}
		}
	}
}

//BGM、SE再生関数
void Play_Sound_WoodRock(int sound, int volume)
{
	if (CheckSoundMem(sound) == 0)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);
		ChangeVolumeSoundMem(volume, sound);
	}

}

//木が揺れるアニメーション関数
void SwayWoodAnim(int x,int y)
{
	if (wood.add_anim_x[x][y] > 1)
	{
		wood.sway_anim[x][y] = 1;
	}
	else if (wood.add_anim_x[x][y] < -1)
	{
		wood.sway_anim[x][y] = 0;
	}

	switch (wood.sway_anim[x][y])
	{
	case 0:
		wood.add_anim_x[x][y] += 1;
		break;
	case 1:
		wood.add_anim_x[x][y] -= 1;
		break;
	}
	
}


