#pragma once

enum eInputState
{
	eNone,
	ePress,
	eRelease,
	eHold,
};

void InputManagerUpdate(void);
eInputState GetKeyInputState(int keycode);
