#include"DxLib.h"
#include"map.h"
#include "../Object/WoodRock.h"
#include "../Object/Obstacle.h"
#include "../Object/Tool.h"
#include "../Object/Goal.h"
#include "../Object/Cursor.h"
#include "../Object/Car.h"
#include "../Scene/InGame/InGameScene.h"

#include <math.h>
#define MAP_TROUT_LENGTH (80)

CreateStage stage;
SnowBall snow;
int ground;
int groundreef;
int groundreef_top;
//int groundreef_botom;
int stage_start;
int ikl;

void Stage_Start(const InGame* ingame);
void StageLoad();
void Put_Road(const Tool* tool, const Cursor* cursor,int x,int y);
void Put_Wood_Road(const Tool* tool, const Cursor* cursor, int x, int y);
void Delete_WoodRock(const Wood* wood, const Rock* rock);
void MapCreate(const Wood* wood, const Rock* rock, const Mole* mole, const Tool* tool,
	const Lake* lake, const Goal* goal,int length);
void MolePutRock(const Mole* mole, int x, int y);
void MolePutWood(const Mole* mole, int x, int y);
void GetStageNum(const InGame* ingame);
void MapTroutDraw(const InGame* ingame);

//初期化
void MapInit(void)
{
	
	//csvファイルから値を取得
	StageLoad();
	//マップの各値を初期化
	MapValueInit();

	
	stage.start = false;
	stage.menu_flag = false;
	stage.mitibiki_flag = false;
	stage.number = 1;

	GetStageNum(GetInGame());

	
}

void MapResourceInit(void)
{
	//画像の取得
	groundreef = LoadGraph("Resource/images/MapOriginal10.png");
	groundreef_top = LoadGraph("Resource/images/MapOriginal10_top.png");
	/*groundreef_botom = LoadGraph("Resource/images/MapOriginal10_botom.png");*/
	stage.trout_image = LoadGraph("Resource/images/trout.png");
	stage.no_admittance = LoadGraph("Resource/images/No_admittance.png");
	ikl = LoadGraph("Resource/images/Back_Wood.png");
	//　氷山の画像
	stage.mountain_image = LoadGraph("Resource/images/mountain.png");
	//　スノーボールの画像
	snow.img = LoadGraph("Resource/images/snowball.png");
}
//更新
void MapUpdate(void)
{
	//ステージ処理開始
	Stage_Start(GetInGame());
	SnowBallMove();

	if (stage.start == true && stage.menu_flag == false&& stage.mitibiki_flag==false)
	{

		//採取した後に描画を消す
		Delete_WoodRock(GetWood(), GetRock());

		for (int j = 0; j < 7; j++)
		{
			for (int i = 0; i < 12; i++)
			{
				//道を置く
				Put_Road(Get_Tool(), GetCursor1(), i, j);
				//橋を置く
				Put_Wood_Road(Get_Tool(), GetCursor1(), i, j);
				//モグラが岩を置く
				MolePutRock(GetMole(), i, j);
				//モグラが木を置く
				MolePutWood(GetMole(), i, j);
			}
		}
	}
	else if(stage.start == false && stage.menu_flag == false)
	{
		MapReset();
	}
}

void MapDraw(void)
{
	//背景の描画
	DrawRotaGraphF(640, 360, 1.0, 0.0, groundreef, TRUE);
	/*DrawRotaGraphF(640, 360, 1.0, 0.0, groundreef_botom, TRUE);*/
	DrawRotaGraphF(640, 360, 1.0, 0.0, groundreef_top, TRUE);
	//マスの描画
	MapTroutDraw(GetInGame());
	//マップ作成
	MapCreate(GetWood(), GetRock(), GetMole(), Get_Tool(), GetLake(), GetGoal(), MAP_TROUT_LENGTH);

	DrawFormatString(200, 200, GetColor(255, 255, 255), "%d", snow.dir);
	
	//csvの中身を見るString
	/*for (int j = 0; j < 7; j++) 
	{
		for (int i = 0; i < 12; i++)
		{
			DrawFormatString(200+i*30, 200+j*30, GetColor(0, 255, 255), "%d", stage.array[i][j]);
		}
	}*/
}

const CreateStage* GetStage(void)
{
	return&stage;
}

//ステージ生成
void StageLoad(void)
{
	//構造体CreateStageの初期化
	stage.beside = 0;
	stage.vertical = 0;
	stage.kinds = 0;
	stage.char_count = 1;
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			stage.array[i][j] = 0;
		}
	}
	stage.stage_x = 100;
	stage.stage_y = 400;


	char file_name[256];
	int number = 0;
	snprintf(file_name, sizeof(file_name), "Resource/stage/stage_%d.csv", stage.number);

	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, file_name, "r");

	while (err == 0)
	{
		stage.kinds = fgetc(fp);
		if (stage.kinds == EOF)
		{
			break;
		}
		else if (stage.kinds == '\n')
		{
			stage.vertical++;
			stage.beside = 0;
			continue;
		}
		else if (stage.kinds == ',')
		{
			stage.beside++;
			stage.char_count = 0;
			continue;
		}
		else
		{
			if (stage.beside < 12 && stage.vertical < 7)
			{
				switch (stage.char_count)
				{
				case 0:
					stage.array[stage.beside][stage.vertical] = stage.kinds - '0';
					stage.char_count++;
					break;
				case 1:
					stage.array[stage.beside][stage.vertical] = stage.array[stage.beside][stage.vertical] * 10 + stage.kinds - '0';
					break;
				}
				
			}
		}
	}
	if (fp != NULL)
	{
		fclose(fp);
	}
}

//マップ作成
void MapCreate(const Wood* wood, const Rock* rock, const Mole* mole, const Tool* tool,
	const Lake* lake, const Goal* goal, int length)
{
	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			switch (stage.array[x][y])
			{
			case 1://木
				DrawRotaGraphF(length * x + 200 + wood->add_anim_x[x][y], length * y + 120, 1.0, 0.0, wood->animation[x][y], TRUE);
				break;
			case 2://石
				DrawRotaGraphF(length * x + 200 + rock->add_anim_x[x][y], length * y + 120, 1.0, 0.0, rock->animation[x][y], TRUE);
				break;
			case 3://ロックモグラ
				DrawRotaGraphF(length * x + 200, length * y + 120, 1.0, 0.0, mole->animation[x][y], TRUE);
				break;
			case 4://道
				DrawRotaGraphF(length * x + 200, length * y + 120, 1.0, 0.0, tool->road_img_array[x][y], TRUE);
				break;
			case 5://橋
				DrawRotaGraphF(length * x + 200, length * y + 120, 1.0, 0.0, tool->road_img_array[x][y], TRUE);
				break;
			case 6://湖
				DrawRotaGraphF(length * x + 200, length * y + 120, 1.0, 0.0, lake->image, TRUE);
				break;
			case 7://ゴール
				DrawRotaGraphF(length * x + 200, length * y + 120, 0.1, 0.0, goal->flag_image, TRUE);
				break;
			case 8://動けないマス
				DrawRotaGraphF(length * x + 200, length * y + 120, 1.0, 0.0, stage.no_admittance, TRUE);
				break;
			case 9://山
				DrawRotaGraphF(length * x + 200, length * y + 125, 0.15, 0.0, stage.mountain_image, TRUE);
				DrawRotaGraphF(length * x + 200, length * y + 85 + snow.add_y, 0.05, 0.0, snow.img, TRUE);
				break;
			case 10://ウッドモグラ
				DrawRotaGraphF(length * x + 200, length * y + 125, 1.0, 0.0, mole->wood_anim[x][y], TRUE);
				break;
			}

		}
	}

}

//ステージスタート
void Stage_Start(const InGame* ingame)
{
	//TRUEならstageもTRUEに
	if (ingame->start == true && ingame->menu_flag == false&& ingame->mitibiki_flag==false)
	{
		stage.start = true;
	}

	//そうでなければFALSEに
	else if(ingame->start == false&&ingame->menu_flag == false && ingame->mitibiki_flag == false)
	{
		stage.start = false;
	}

	stage.menu_flag = ingame->menu_flag;
	stage.mitibiki_flag= ingame->mitibiki_flag;
}

//スノーボールのムーブ
void SnowBallMove(void)
{
	snow.cnt++;

	if (snow.cnt > 60)
	{
		//eRight(2)だから+2
		snow.dir = GetRand(1) + 2;
		snow.cnt = 0;
	}
	snow.vec_y = 0.5f;
	snow.add_y += snow.vec_y;
}


//カーソルの位置と対応している配列の中身を道に変更
void Put_Road(const Tool* tool, const Cursor* cursor,int x,int y)
{
	if (tool->road_flag[x][y] == true)
	{
		stage.array[x][y] = 4;
	}
}


//カーソルの位置と対応している配列の中身を丸太の道に変更
void Put_Wood_Road(const Tool* tool, const Cursor* cursor,int x,int y)
{

	if (tool->wood_road_flag[x][y] == true)
	{
		stage.array[x][y] = 5;
	}
}



//岩を消すフラグがtrueなら消す
void Delete_WoodRock(const Wood* wood,const Rock* rock)
{
	if (rock->delete_flag[rock->count_x][rock->count_y] == true)
	{
		stage.array[rock->count_x][rock->count_y] = 0;
		WR_Delete_Flag();
	}
	if (wood->delete_flag[wood->count_x][wood->count_y] == true)
	{
		stage.array[wood->count_x][wood->count_y] = 0;
		WR_Delete_Flag();
	}
}

//モグラが岩を置くフラグがtrueなら岩を置く
void MolePutRock(const Mole* mole, int x, int y)
{
	//置くフラグがtrueなら
	if (mole->put_rock_flag[x][y] == true)
	{
		//岩を描画
		stage.array[x][y] = 2;
		//置かれた岩が何番目の岩か数えるフラグ
		stage.rock_count_flag = true;

		//今まで岩があった場所と被っているか
		for (int k = 0; k < stage.rock_count; k++)
		{
			//被っていないなら新しい番目に配列番号を入れる
			if (stage.rock_x[k] != x || stage.rock_y[k] != y)
			{
				stage.rock_x[stage.rock_count] = x;
				stage.rock_y[stage.rock_count] = y;
			}
			//もし場所が被っているなら番号を更新しない
			else if (stage.rock_x[k] == x && stage.rock_y[k] == y)
			{
				stage.rock_count_flag = false;
			}
		}
		//新しい番目に入れたときに番号を更新
		if (stage.rock_count_flag == true)
		{
			stage.rock_count++;
		}
		//フラグの初期化
		stage.rock_count_flag = false;
	}

}

void MolePutWood(const Mole* mole,int x, int y)
{
	//置くフラグがtrueなら
	if (mole->put_wood_flag[x][y] == true)
	{
		//木を描画
		stage.array[x][y] = 1;
		//置かれた木が何番目の木か数えるフラグ
		stage.wood_count_flag = true;

		//今まで木があった場所と被っているか
		for (int k = 0; k < stage.wood_count; k++)
		{
			//被っていないなら新しい番目に配列番号を入れる
			if (stage.wood_x[k] != x || stage.wood_y[k] != y)
			{
				stage.wood_x[stage.wood_count] = x;
				stage.wood_y[stage.wood_count] = y;
			}
			//もし場所が被っているなら番号を更新しない
			else if (stage.wood_x[k] == x && stage.wood_y[k] == y)
			{
				stage.wood_count_flag = false;
			}
		}
		//新しい番目に入れたときに番号を更新
		if (stage.wood_count_flag == true)
		{
			stage.wood_count++;
		}
		//フラグの初期化
		stage.wood_count_flag = false;
	}
}


//マップの各値を初期化
void MapValueInit(void)
{
	stage.wood_count = 0;  //木
	stage.wood_count_flag = 0;
	stage.rock_count = 0;	//岩
	stage.rock_count_flag = 0;
	stage.mole_count = 0;	//モグラ
	int g = 0;		//道
	int h = 0;		//丸太の道
	//int k = 0;      //湖の画像
	int l = 0;      //ゴールの画像  
	int m = 0;      //動けないマスの画像
	stage.woodmole_count = 0;    //ウッドモグラ
	
	//SnowBall変数
	snow.add_x = 0.0f;
	snow.add_y = 0.0f;
	snow.vec_x = 0.0f;
	snow.vec_y = 0.0f;
	snow.cnt = 0;
	snow.dir = eRight;

	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			switch (stage.array[x][y])
			{
			case 1:
				stage.wood_x[stage.wood_count] = x;
				stage.wood_y[stage.wood_count] = y;
				stage.wood_count++;
				break;
			case 2:
				stage.rock_x[stage.rock_count] = x;
				stage.rock_y[stage.rock_count] = y;
				stage.rock_count++;
				break;
			case 3:
				stage.mole_x[stage.mole_count] = x;
				stage.mole_y[stage.mole_count] = y;
				stage.mole_count++;
				break;
			case 4:
				stage.road_x[g] = x;
				stage.road_y[g] = y;
				g++;
				break;
			case 5:
				stage.wood_road_x[h] = x;
				stage.wood_road_y[h] = y;
				h++;
				break;
			case 7:
				stage.goal_x[l] = x;
				stage.goal_y[l] = y;
				l++;
				break;
			case 10:
				stage.woodmole_x[stage.woodmole_count] = x;
				stage.woodmole_y[stage.woodmole_count] = y;
				stage.woodmole_count++;
			}
		}
	}

}

//マスの描画
void MapTroutDraw(const InGame* ingame)
{
	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			if (stage.number == 1)
			{

				if (x > 0 && x < 10 && y>3 && y < 6)
				{
					DrawRotaGraphF(MAP_TROUT_LENGTH * x + 200, MAP_TROUT_LENGTH * y + 120, 1.0, 0.0, stage.trout_image, TRUE);
				}


			}
			else
			{

				DrawRotaGraphF(MAP_TROUT_LENGTH * x + 200, MAP_TROUT_LENGTH * y + 120, 1.0, 0.0, stage.trout_image, TRUE);
			}
		}
	}
}


void GetStageNum(const InGame* ingame)
{
	switch (ingame->stage_num)
	{
	case eOne:
		stage.number = 1;
		break;
	case eTwo:
		stage.number = 2;
		break;
	case eThree:
		stage.number = 3;
		break;
	case eFour:
		stage.number = 4;
		break;
	case eFive:
		stage.number = 5;
		break;
	case eSix:
		stage.number = 6;
		break;

	}
}

void MapReset(void)
{
	//スタートフラグの初期化
	stage.start = false;
	stage.menu_flag = false;
	stage.mitibiki_flag = false;




	
	StageLoad();
	GetStageNum(GetInGame());
	MapValueInit();
}

