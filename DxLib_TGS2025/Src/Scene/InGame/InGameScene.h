#pragma once

#include "../SceneType.h"

void InGameSceneInit(void);
eSceneType InGameSceneUpdate(void);
void HitAction(int index, int* score, int* heart);
void NoHitAction(int index);
void InGameSceneDraw(void);
void Put_Score(int* Score);
void Input_File(void);