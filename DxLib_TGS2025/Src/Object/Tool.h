#pragma once

enum eToolMotionState
{
	PickaxeState1,
	PickaxeState2,
};
void ToolInit(void);
void ToolManagerUpdate(void);
void ToolDraw(void);
void Move_Frame(void);
void Put_Road(void);
void Draw_Road(void);