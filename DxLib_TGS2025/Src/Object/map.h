 #pragma once

#define ONE_SIDE_LENGTH (80)

//ステージ生成の構造体
struct CreateStage
{
	int array[12][7];		//ステージ配列
	int beside;		//横
	int vertical;		//縦
	int kinds;		//ステージの種類
	int stage_x;
	int stage_y;
	int wood_x[80];
	int wood_y[80];
	int rock_x[80];
	int rock_y[80];
	int hole_x[20];
	int hole_y[20];
	int road_x[80];
	int road_y[20];
	int wood_road_x[20];
	int wood_road_y[20];
	int lake_x[40];
	int lake_y[40];
	int goal_x[5];
	int goal_y[5];
};

void MapInit(void);
void MapUpdate(void);
void MapDraw(void);
void StageRoad(void);
void StageCreate(void);

void MapValueInit(void);
const CreateStage* GetStage(void);