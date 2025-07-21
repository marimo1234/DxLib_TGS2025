 #pragma once



//ステージ生成の構造体
struct CreateStage
{
	int number;
	int array[12][7];		//ステージ配列
	int beside;		//横
	int vertical;		//縦
	int kinds;		//ステージの種類
	int char_count;
	int stage_x;
	int stage_y;
	bool start;
	bool menu_flag;

	int trout_image;
	int mountain_image;		//崖画像
	int no_admittance;
	int wood_x[84];
	int wood_y[84];
	int rock_x[84];
	int rock_y[84];
	int mole_x[84];
	int mole_y[84];
	int road_x[84];
	int road_y[84];
	int wood_road_x[84];
	int wood_road_y[84];
	/*int lake_x[84];
	int lake_y[84];*/
	int goal_x[5];
	int goal_y[5];
	int woodmole_x[84];
	int woodmole_y[84];

	
	int rock_count;
	int rock_count_flag;
	int mole_count;

	int wood_count;
	int wood_count_flag;
	int woodmole_count;
	
	

	bool mitibiki_flag;
	
};


void MapInit(void);
void MapUpdate(void);
void MapDraw(void);
void MapResourceInit(void);
//void StageLoad(void);

void MapValueInit(void);
void MapReset(void);
const CreateStage* GetStage(void);
