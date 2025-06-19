#pragma once

#include "../SceneType.h"
#include "../../Utility/Geometry.h"


struct StageSelect
{
	bool flag;
	int background_image;
	int Abutton;
	float Abutton_rate;
	float rate_num;
	int car_image;
	int trout_image[3];
	int number_image[6];
	float number_extrate[3][2];
	int number_count;
	int trout_array[3][3];
	Vector2D position;
	int number;
	int array_number;
	int array_x;
	int array_y;
	int cursor_se;
	int button_se;
	
};

void StageSelectSceneInit(void);
eSceneType StageSelectSceneUpdate(void);
void StageSelectSceneDraw(void);
void StageSelectCarMove(void);
void StageSelectNumber(void);
void StageSelectGetNumber(void);
void NumTroutDraw(void);
void SelectButtonDraw(void);
void ChangeNumberExtrate(void);



const StageSelect*GetStageSelect(void);
