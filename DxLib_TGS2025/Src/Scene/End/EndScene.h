#pragma once

#include "../SceneType.h"

struct End
{
	int image;
	int fps;
	int black;
	int black_count;
	int bgm;
};

void EndSceneInit(void);
eSceneType EndSceneUpdate(void);
void EndSceneDraw(void);
