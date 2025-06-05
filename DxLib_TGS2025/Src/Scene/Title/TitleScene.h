#pragma once

#include "../SceneType.h"

struct Title
{
	int image;
};
void TitleSceneInit(void);
eSceneType TitleSceneUpdate(void);
void TitleSceneDraw(void);

const Title* GetTitle(void);
