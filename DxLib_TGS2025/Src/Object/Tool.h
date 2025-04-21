#pragma once

enum eToolMotionState
{
	PickaxeState1,
	PickaxeState2,
};
void ToolInit(void);
void ToolManagerUpdate(void);
void ToolDraw(void);