#pragma once

#include "../SceneType.h"

struct Credits
{
	int credits_background_img;
	int button_se;
};

void CreditsSceneInit(void);
eSceneType CreditsSceneUpdate(void);
void CreditsSceneDraw(void);