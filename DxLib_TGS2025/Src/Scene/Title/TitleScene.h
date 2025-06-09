#pragma once

#include "../SceneType.h"

struct Title
{
	int image;
	int char_image[3];
	int cursor_image;
	int name_image;
	int char_num;
	float cursor_x;
	float cursor_y;
};
void TitleSceneInit(void);
eSceneType TitleSceneUpdate(void);
void TitleSceneDraw(void);

void TitleCursorUpdate(void);

const Title* GetTitle(void);
