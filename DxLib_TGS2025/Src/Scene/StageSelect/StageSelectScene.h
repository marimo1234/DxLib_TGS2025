#pragma once

#include "../SceneType.h"
#include "../../Utility/Geometry.h"


struct StageSelect
{
	int background_image;
	int Abottom;
	float Abottom_rate;
	float rate_num;
	int car_image;
	int trout_image[3];
	int number_image[5];
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



const StageSelect*GetStageSelect(void);
