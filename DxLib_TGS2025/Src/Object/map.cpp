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

void Stage_Start(const InGame* ingame);
void Put_Road(const Tool* tool, const Cursor* cursor);
void Put_Wood_Road(const Tool* tool, const Cursor* cursor);
void Delete_WoodRock(const Wood* wood, const Rock* rock);
void MapCreate(const Wood* wood, const Rock* rock, const Mole* mole, const Tool* tool,
	const Lake* lake, const Goal* goal);
void Break_Road(const Tool* tool, const Cursor* cursor);

//初期化
void MapInit(void)
{
	//画像の取得
	groundreef = LoadGraph("Resource/images/MapOriginal2.png");
	stage.trout_image= LoadGraph("Resource/images/trout.png");
	//csvファイルから値を取得
	StageLoad();
	//マップの各値を初期化
	MapValueInit();

	
	stage.start = false;

	
}

//更新
void MapUpdate(void)
{
	//ステージ処理開始
	Stage_Start(GetInGame());
	

	if (stage.start == true)
	{
		//採取した後に描画を消す
		Delete_WoodRock(GetWood(), GetRock());
		//道を壊す
		Break_Road(Get_Tool(),GetCursor1());
		//道を置く
		Put_Road(Get_Tool(), GetCursor1());
		//橋を置く
		Put_Wood_Road(Get_Tool(), GetCursor1());

		
	}
	else
	{
		MapReset();
	}
}

void MapDraw(void)
{
	//背景の描画
	DrawRotaGraphF(640, 360, 1.0, 0.0, groundreef, TRUE);
	//マスの描画
	MapTroutDraw();
	//マップ作成
	MapCreate(GetWood(), GetRock(), GetMole(), Get_Tool(), GetLake(), GetGoal());

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

	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, "Resource/stage/stage.csv", "r");

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
			stage.array[stage.beside][stage.vertical] = stage.kinds - '0';
			stage.beside++;
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
				DrawRotaGraphF(MAP_TROUT_LENGTH * x + 200, MAP_TROUT_LENGTH * y + 120, 1.0, 0.0, mole->animation, TRUE);
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
				DrawRotaGraphF(MAP_TROUT_LENGTH * x + 200, MAP_TROUT_LENGTH * y + 120, 1.0, 0.0, goal->flag_image, TRUE);
				break;
			}

		}
	}

}

//ステージスタート
void Stage_Start(const InGame* ingame)
{
	//TRUEならstageもTRUEに
	if (ingame->start == true)
	{
		stage.start = true;
	}

	//そうでなければFALSEに
	else
	{
		stage.start = false;
	}
}


//カーソルの位置と対応している配列の中身を道に変更
void Put_Road(const Tool* tool, const Cursor* cursor)
{
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			if (tool->road_flag[i][j] == true)
			{
				stage.array[i][j] = 4;
			}
		}
	}
}


//カーソルの位置と対応している配列の中身を丸太の道に変更
void Put_Wood_Road(const Tool* tool, const Cursor* cursor)
{
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			if (tool->wood_road_flag[i][j] == true)
			{
				stage.array[i][j] = 5;
			}
		}
	}
}

//カーソルの位置と対応しているベースの道を壊す
void Break_Road(const Tool* tool,const Cursor*cursor)
{
	for (int j = 0; j < 7; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			if (tool->road_break_flag[i][j] == true)
			{
				if (tool->stage_begin_array[i][j] == 6)
				{
					stage.array[i][j] = 6;
				}
				else
				{
					stage.array[i][j] = 0;
				}
			}
		}
	}
}

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

//マップの各値を初期化
void MapValueInit(void)
{
	int i = 0;		//木
	int j = 0;		//岩
	int f = 0;		//穴
	int g = 0;		//道
	int h = 0;		//丸太の道
	int k = 0;      //湖の画像
	int l = 0;      //ゴールの画像  

	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			switch (stage.array[x][y])
			{
			case 1:
				stage.wood_x[i] = x;
				stage.wood_y[i] = y;
				stage.wood_count[i] = i;
				i++;
				break;
			case 2:
				stage.rock_x[j] = x;
				stage.rock_y[j] = y;
				stage.rock_count[j] = j;
				j++;
				break;
			case 3:
				stage.hole_x[f] = x;
				stage.hole_y[f] = y;
				f++;
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
				stage.lake_x[k] = x;
				stage.lake_y[k] = y;
				k++;
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
void MapTroutDraw(void)
{
	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			DrawRotaGraphF(MAP_TROUT_LENGTH * x + 200, MAP_TROUT_LENGTH * y + 120, 1.0, 0.0, stage.trout_image, TRUE);
		}
	}
}

void MapReset(void)
{
	//スタートフラグの初期化
	stage.start = false;

	StageLoad();
	MapValueInit();
	MapTroutDraw();
}
