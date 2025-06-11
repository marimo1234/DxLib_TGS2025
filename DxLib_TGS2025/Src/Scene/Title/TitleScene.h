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

	int bgm;
	int cursor_se;
	int button_se;
};
void TitleSceneInit(void);
eSceneType TitleSceneUpdate(void);
void TitleSceneDraw(void);

void TitleResourceInit(void);
void TitleCursorUpdate(void);
void Stop_BGM(void);
void Play_Title_BGM(void);

const Title* GetTitle(void);
