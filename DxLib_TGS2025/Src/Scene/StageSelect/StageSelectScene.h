#pragma once

#include "../SceneType.h"
#include "../../Utility/Geometry.h"


struct StageSelect
{
	int background_image;
	int trout_image[2];
	int number_image[5];
	int torut_array[3][2];
	Vector2D position;
	int number;
};

void StageSelectSceneInit(void);
eSceneType StageSelectSceneUpdate(void);
void StageSelectSceneDraw(void);

const StageSelect*GetStageSelect(void);
