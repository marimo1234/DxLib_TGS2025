#include"DxLib.h"
#include"map.h"
#include "../Object/WoodRock.h"
#include "../Object/Obstacle.h"
#include "../Object/Tool.h"


CreateStage stage;

int ground;
int groundreef;
int sea;
int trout[256][256];
int math;

void MapCreate(const Wood* wood, const Rock*rock, const Hole* hole,const Tool*tool);

void MapInit(void)
{
	groundreef = LoadGraph("Resource/images/MapOriginal2.png");
	/*math= LoadGraph("Resource/images/1trout.png");*/

}
void MapUpdate(void)
{

}
void MapDraw(void)
{
	DrawRotaGraphF(640, 360, 1.0, 0.0, groundreef, TRUE);
	/*trout[0][0] = DrawRotaGraphF(540, 380, 1.0, 0.0, math, TRUE);
	trout[1][0] = DrawRotaGraphF(615, 380, 1.0, 0.0, math, TRUE);
	trout[2][0] = DrawRotaGraphF(690, 380, 1.0, 0.0, math, TRUE);*/

	MapCreate(GetWood(),GetRock(),GetHole(),Get_Tool());
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

void MapCreate(const Wood* wood,const Rock* rock,const Hole* hole,const Tool*tool)
{
	int i = 0;		//木
	int j = 0;		//岩
	int f = 0;		//穴
	int g = 0;		//道
	int h = 0;		//丸太の道
	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 12; x++)
		{
			switch (stage.array[x][y])
			{
			case 1:
				stage.wood_x[i] = x;
				stage.wood_y[i] = y;
				DrawRotaGraphF(ONE_SIDE_LENGTH * x + 200, ONE_SIDE_LENGTH * y + 120, 1.0, 0.0, wood->animation[i], TRUE);
				i++;
				break;

			case 2:
				stage.rock_x[j] = x;
				stage.rock_y[j] = y;
				DrawRotaGraphF(ONE_SIDE_LENGTH * x + 200, ONE_SIDE_LENGTH * y + 120, 1.0, 0.0, rock->animation[j], TRUE);
				j++;
				break;

			case 3:
				stage.hole_x[f] = x;
				stage.hole_y[f] = y;
				DrawRotaGraphF(ONE_SIDE_LENGTH * x + 200, ONE_SIDE_LENGTH * y + 120, 1.0, 0.0, hole->image, TRUE);
				f++;
				break;

			case 4:
				stage.hole_x[g] = x;
				stage.road_y[g] = y;
				DrawRotaGraphF(ONE_SIDE_LENGTH * x + 200, ONE_SIDE_LENGTH * y + 120, 1.0, 0.0, tool->road_img, TRUE);
				g++;
				break;


			case 5:
				stage.wood_road_x[h] = x;
				stage.wood_road_y[h] = y;
				DrawRotaGraphF(ONE_SIDE_LENGTH * x + 200, ONE_SIDE_LENGTH * y + 120, 0.5, 0.0, tool->wood_road_img, TRUE);
				h++;
				break;
			}

		}
	}

}