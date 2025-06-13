#pragma once

#include "../SceneType.h"

struct Credits
{
	int credits_background_img;
	int B_back;
	int button_se;
	float title_x;
	float title_y;
	float url_x;
	float url_y;
};

void CreditsSceneInit(void);
eSceneType CreditsSceneUpdate(void);
void CreditsSceneDraw(void);