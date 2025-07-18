﻿#pragma once

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
	int Abutton;
	float Abutton_rate;
	float rate_num;

	int car_image1;
	int car_image2;
	int trout_image[5];
	int number_image[6];
	int arrow_image[2];
	int stage_image[6];
	int back_minimap;

	int b_back;
	bool car_flag;
	float car_x;
	float car_y;
	int car_num;
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
void StageSelectCursorMove(void);
void StageSelectNumber(void);
void StageSelectGetNumber(void);
void NumTroutDraw(void);
void SelectButtonDraw(void);
void ChangeNumberExtrate(void);
void StageSelectResourceInit(void);
//車描画
void Draw_Select_Car(void);




const StageSelect*GetStageSelect(void);
