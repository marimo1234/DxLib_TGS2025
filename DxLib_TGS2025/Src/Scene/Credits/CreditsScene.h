#pragma once

#include "../SceneType.h"

struct Credits
{
	int button_se;
};

void CreditsSceneInit(void);
eSceneType CreditsSceneUpdate(void);
void CreditsSceneDraw(void);