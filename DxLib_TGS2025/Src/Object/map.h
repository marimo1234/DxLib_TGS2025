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
};

void MapInit(void);
void MapUpdate(void);
void MapDraw(void);
