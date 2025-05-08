#include"DxLib.h"
#include"map.h"
#include "../Object/WoodRock.h"
#include "../Object/Obstacle.h"
#include "../Object/Tool.h"
#include "../Object/Goal.h"
#include "../Object/Cursor.h"


CreateStage stage;

int ground;
int groundreef;
int sea;
int trout[256][256];
int math;

void Put_Road(const Tool* tool,const Cursor* cursor);
void MapCreate(const Wood* wood, const Rock* rock, const Hole* hole, const Tool* tool,
	const Lake* lake, const Goal* goal);

void MapInit(void)
{
	groundreef = LoadGraph("Resource/images/MapOriginal2.png");
	/*math= LoadGraph("Resource/images/1trout.png");*/
	StageCreate();
	StageRoad();
	MapValueInit();
	

}
void MapUpdate(void)
{
	//ステージ読み込み、描画
	/*StageCreate();
	StageRoad();*/

	Put_Road(Get_Tool(),GetCursor1());
}
void MapDraw(void)
{
	DrawRotaGraphF(640, 360, 1.0, 0.0, groundreef, TRUE);
	/*trout[0][0] = DrawRotaGraphF(540, 380, 1.0, 0.0, math, TRUE);
	trout[1][0] = DrawRotaGraphF(615, 380, 1.0, 0.0, math, TRUE);
	trout[2][0] = DrawRotaGraphF(690, 380, 1.0, 0.0, math, TRUE);*/

	MapCreate(GetWood(), GetRock(), GetHole(), Get_Tool(), GetLake(), GetGoal());
}

const CreateStage* GetStage(void)
{
	return&stage;
}
//ステージ生成
void StageRoad(void)
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

void StageCreate(void)
{
	for (stage.vertical = 0; stage.vertical < 7; stage.vertical++)
	{
		for (stage.beside = 0; stage.beside < 12; stage.beside++)
		{
			DrawFormatString(stage.stage_x, stage.stage_y, GetColor(255, 255, 255), "%d", stage.array[stage.beside][stage.vertical]);
			stage.stage_x += 20;
		}
		stage.stage_x = 100;
		stage.stage_y += 20;
	}
}

void MapCreate(const Wood* wood,const Rock* rock,const Hole* hole,const Tool*tool,
               const Lake*lake,const Goal*goal)
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
				/*stage.wood_x[i] = x;
				stage.wood_y[i] = y;*/
				DrawRotaGraphF(ONE_SIDE_LENGTH * x + 200, ONE_SIDE_LENGTH * y + 120, 1.0, 0.0, wood->animation[i], TRUE);
				i++;
				break;

			case 2:
				/*stage.rock_x[j] = x;
				stage.rock_y[j] = y;*/
				DrawRotaGraphF(ONE_SIDE_LENGTH * x + 200, ONE_SIDE_LENGTH * y + 120, 1.0, 0.0, rock->animation[j], TRUE);
				j++;
				break;

			case 3:
				/*stage.hole_x[f] = x;
				stage.hole_y[f] = y;*/
				DrawRotaGraphF(ONE_SIDE_LENGTH * x + 200, ONE_SIDE_LENGTH * y + 120, 1.0, 0.0, hole->image, TRUE);
				f++;
				break;

			case 4:
				/*stage.road_x[g] = x;
				stage.road_y[g] = y;*/
				DrawRotaGraphF(ONE_SIDE_LENGTH * x + 200, ONE_SIDE_LENGTH * y + 120, 1.0, 0.0, tool->road_img, TRUE);
				g++;
				break;


			case 5:
				/*stage.wood_road_x[h] = x;
				stage.wood_road_y[h] = y;*/
				DrawRotaGraphF(ONE_SIDE_LENGTH * x + 200, ONE_SIDE_LENGTH * y + 120, 0.5, 0.0, tool->wood_road_img, TRUE);
				h++;
				break;

			case 6:
				/*stage.lake_x[k] = x;
				stage.lake_y[k] = y;*/
				DrawRotaGraphF(ONE_SIDE_LENGTH * x + 200, ONE_SIDE_LENGTH * y + 120, 1.0, 0.0, lake->image, TRUE);
				k++;
				break;

			case 7:
				/*stage.goal_x[l] = x;
				stage.goal_y[l] = y;*/
				DrawRotaGraphF(ONE_SIDE_LENGTH * x + 200, ONE_SIDE_LENGTH * y + 120, 1.0, 0.0, goal->flag_image, TRUE);
				l++;
				break;
			}

		}
	}

}

void Put_Road(const Tool*tool,const Cursor* cursor)
{
			if (tool->road_flag[cursor->array_x][cursor->array_y] == true)
			{
				stage.array[cursor->array_x][cursor->array_y]= 4;
			}
}

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