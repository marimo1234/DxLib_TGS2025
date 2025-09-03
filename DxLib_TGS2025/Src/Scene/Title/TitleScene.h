#pragma once

#include "../SceneType.h"

struct Title
{
	int image;
	int char_image[3];
	int cursor_image;
	int control_image;
	int name_image[27];
	int name_num;
	int name_count;
	int char_num;
	float cursor_x;
	float cursor_y;
	int mole_image[8];
	int mole_num;
	int mole_count;
	int mole_move;
	int mole_active;

	int bgm;
	int cursor_se;
	int button_se;

	float er[3]; // 拡大率　extrate


};
void TitleSceneInit(void);
eSceneType TitleSceneUpdate(void);
void TitleSceneDraw(void);
void TitleMoleDraw(void);
void TitleNameAnimation(void);

void TitleResourceInit(void);
void TitleCursorUpdate(void);
void Stop_BGM(void);
void Play_Title_BGM(void);

const Title* GetTitle(void);
