#pragma once

#include "../SceneType.h"
#include "../../Utility/Geometry.h"


struct StageSelect
{
	int car_fps;
	int move_fps;
	bool flag;

	int background_image;
	int speed_frame;
	int speed_char;
	

	int car_image1;
	int car_image2;
	int trout_image[5];
	int arrow_image[2];
	int stage_image[6];
	int back_minimap;

	int b_back;
	bool car_flag;
	float car_x;
	float car_y;
	int car_num;

	Vector2D position;
	int cursor_se;
	int button_se;
	
};

struct SS_Star 
{
	//スピードスター
	int img[2];
	int num;
	int x[5];
	int y[5];
	int cnt;
	int idx;
};

struct SS_Num
{
	int img[7];
	int hide_img;
	int stg_num;
	float x;
	float y;
	int cnt;
	int idx;
	bool u_flag;
	bool d_flag;
};

void StageSelectSceneInit(void);
eSceneType StageSelectSceneUpdate(void);
void StageSelectSceneDraw(void);
void StageSelectCursorMove(void);
void StageSelectNumber(void);
void NumTroutDraw(void);
void StageSelectResourceInit(void);
//車描画
void Draw_Select_Car(void);
//スピードスタームーブ
void StarMove(void);
//スピードスター描画
void DrawStar(void);




const StageSelect*GetStageSelect(void);
const SS_Num*GetSS_Num(void);
