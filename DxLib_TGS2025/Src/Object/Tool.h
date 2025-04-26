#pragma once
#include "../Scene/InGame/InGameScene.h"



enum eToolMotionState
{
	PickaxeState1,
	PickaxeState2,
};

enum eToolState
{
	eRoad,
	eLog,
	eAx,
	ePickaxe,
};

struct Tool
{
	int item_number;
};

void ToolInit(void);
void ToolManagerUpdate(void);
void ToolDraw(void);
void Move_Frame(void);
void Put_Road(void);
void Draw_Road(void);
void Tool_Start(const InGame* ingame);
const Tool* Get_Tool(void);

