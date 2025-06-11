#pragma once

#include "../SceneType.h"

struct End
{
	int image;
	int fps;
};

void EndSceneInit(void);
eSceneType EndSceneUpdate(void);
void EndSceneDraw(void);
