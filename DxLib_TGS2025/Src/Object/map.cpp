#include"DxLib.h"
#include"map.h"
#include "../Object/WoodRock.h"
#include "../Object/Obstacle.h"
#include "../Object/Tool.h"
#include "../Object/Goal.h"
#include "../Object/Cursor.h"
#include "../Scene/InGame/InGameScene.h"

#define MAP_TROUT_LENGTH (80)

CreateStage stage;
int ground;
int groundreef;
int stage_start;
int ikl;

void Stage_Start(const InGame* ingame);
void StageLoad();
void Put_Road(const Tool* tool, const Cursor* cursor,int x,int y);
void Put_Wood_Road(const Tool* tool, const Cursor* cursor, int x, int y);
void Delete_WoodRock(const Wood* wood, const Rock* rock);
void MapCreate(const Wood* wood, const Rock* rock, const Mole* mole, const Tool* tool,
	const Lake* lake, const Goal* goal);
void Break_Road(const Tool* tool, const Cursor* cursor, int x, int y);
void MolePutRock(const Mole* mole, const Rock* rock, int x, int y);
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
	stage.number = 1;

	GetStageNum(GetInGame());

	
}

void MapResourceInit(void)
{
	//画像の取得
	groundreef = LoadGraph("Resource/images/MapOriginal7.png");
	stage.trout_image = LoadGraph("Resource/images/trout.png");
	stage.no_admittance = LoadGraph("Resource/images/No_admittance.png");
	ikl = LoadGraph("Resource/images/Back_Wood.png");
	stage.mountain_image = LoadGraph("Resource/images/mountain.png");
}
//更新
void MapUpdate(void)
{
	//ステージ処理開始
	Stage_Start(GetInGame());
	

	if (stage.start == true && stage.menu_flag == false)
	{

		//採取した後に描画を消す
		Delete_WoodRock(GetWood(), GetRock());

		for (int j = 0; j < 7; j++)
		{
			for (int i = 0; i < 12; i++)
			{
				//道を壊す
				Break_Road(Get_Tool(), GetCursor1(), i, j);
				//道を置く
				Put_Road(Get_Tool(), GetCursor1(), i, j);
				//橋を置く
				Put_Wood_Road(Get_Tool(), GetCursor1(), i, j);
				//モグラが石を置く
				MolePutRock(GetMole(), GetRock(), i, j);
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
	//マスの描画
	MapTroutDraw(GetInGame());
	//マップ作成
	MapCreate(GetWood(), GetRock(), GetMole(), Get_Tool(), GetLake(), GetGoal());

	//DrawFormatString(200, 200, GetColor(255, 255, 255), "%d", stage.number);
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
			continue;
		}
		else
		{
			if (stage.beside < 12 && stage.vertical < 7)
			{
				stage.array[stage.beside][stage.vertical] = stage.kinds - '0';
				stage.beside++;
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
	const Lake* lake, const Goal* goal)
{
	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			switch (stage.array[x][y])
			{
			case 1://木
				DrawRotaGraphF(MAP_TROUT_LENGTH * x + 200, MAP_TROUT_LENGTH * y + 120, 1.0, 0.0, wood->animation[x][y], TRUE);				
				break;
			case 2://石
					DrawRotaGraphF(MAP_TROUT_LENGTH * x + 200, MAP_TROUT_LENGTH * y + 120, 1.0, 0.0, rock->animation[x][y], TRUE);
				break;
			case 3://穴
				DrawRotaGraphF(MAP_TROUT_LENGTH * x + 200, MAP_TROUT_LENGTH * y + 120, 1.0, 0.0, mole->animation[x][y], TRUE);
				break;
			case 4://道
				DrawRotaGraphF(MAP_TROUT_LENGTH * x + 200, MAP_TROUT_LENGTH * y + 120, 1.0, 0.0, tool->road_img_array[x][y], TRUE);
				break;
			case 5://橋
				DrawRotaGraphF(MAP_TROUT_LENGTH * x + 200, MAP_TROUT_LENGTH * y + 120, 1.0, 0.0, tool->road_img_array[x][y], TRUE);
				break;
			case 6://湖
				DrawRotaGraphF(MAP_TROUT_LENGTH * x + 200, MAP_TROUT_LENGTH * y + 120, 1.0, 0.0, lake->image, TRUE);
				break;
			case 7://ゴール
				DrawRotaGraphF(MAP_TROUT_LENGTH * x + 200, MAP_TROUT_LENGTH * y + 120, 0.1, 0.0, goal->flag_image, TRUE);
				break;
			case 8://動けないマス
				DrawRotaGraphF(MAP_TROUT_LENGTH * x + 200, MAP_TROUT_LENGTH * y + 120, 1.0, 0.0, stage.no_admittance, TRUE);
				break;
			case 9://山
				DrawRotaGraphF(MAP_TROUT_LENGTH * x + 200, MAP_TROUT_LENGTH * y + 125, 0.15, 0.0, stage.mountain_image, TRUE);
				break;
			}

		}
	}

}

//ステージスタート
void Stage_Start(const InGame* ingame)
{
	//TRUEならstageもTRUEに
	if (ingame->start == true && ingame->menu_flag == false)
	{
		stage.start = true;
	}

	//そうでなければFALSEに
	else if(ingame->start == false&&ingame->menu_flag == false)
	{
		stage.start = false;
	}

	stage.menu_flag = ingame->menu_flag;
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

//カーソルの位置と対応しているベースの道を壊す
void Break_Road(const Tool* tool, const Cursor* cursor, int x, int y)
{
	if (tool->road_break_flag[x][y] == true)
	{
		if (tool->stage_begin_array[x][y] == 6)
		{
			stage.array[x][y] = 6;
		}
		else
		{
			stage.array[x][y] = 0;
		}
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
void MolePutRock(const Mole* mole, const Rock* rock, int x, int y)
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


//マップの各値を初期化
void MapValueInit(void)
{
	int i = 0;	//木
	stage.rock_count = 0;	//岩
	stage.rock_count_flag = 0;
	stage.mole_count = 0;	//穴
	int g = 0;		//道
	int h = 0;		//丸太の道
	//int k = 0;      //湖の画像
	int l = 0;      //ゴールの画像  
	int m = 0;      //動けないマスの画像

	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			switch (stage.array[x][y])
			{
			case 1:
				stage.wood_x[i] = x;
				stage.wood_y[i] = y;
				i++;
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
			case 6:
				/*stage.lake_x[k] = x;
				stage.lake_y[k] = y;
				k++;*/
				break;
			case 7:
				stage.goal_x[l] = x;
				stage.goal_y[l] = y;
				l++;
				break;
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

				if (x > 0 && x < 10 && y>2 && y < 5)
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



	
	StageLoad();
	GetStageNum(GetInGame());
	MapValueInit();
}

