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
	int wood_x[20];
	int wood_y[20];
	int rock_x[20];
	int rock_y[20];
};

void MapInit(void);
void MapUpdate(void);
void MapDraw(void);

const CreateStage* GetStage(void);