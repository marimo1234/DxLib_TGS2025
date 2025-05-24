 #pragma once



//ステージ生成の構造体
struct CreateStage
{
	int array[12][7];		//ステージ配列
	int beside;		//横
	int vertical;		//縦
	int kinds;		//ステージの種類
	int stage_x;
	int stage_y;
	int trout_image;
	int start;

	int wood_x[80];
	int wood_y[80];
	int rock_x[80];
	int rock_y[80];
	int mole_x[20];
	int mole_y[20];
	int road_x[80];
	int road_y[20];
	int wood_road_x[20];
	int wood_road_y[20];
	int lake_x[40];
	int lake_y[40];
	int goal_x[5];
	int goal_y[5];

	int wood_count;
	int rock_count;
	int rock_count_flag;
	int mole_count;
};


void MapInit(void);
void MapUpdate(void);
void MapDraw(void);
void StageLoad(void);

void MapValueInit(void);
void MapReset(void);
void MapTroutDraw(void);
const CreateStage* GetStage(void);
