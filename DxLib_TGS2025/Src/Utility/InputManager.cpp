#include "InputManager.h"
#include "DxLib.h"

#define D_KEYCODE_MAX	(256)

char now_key[D_KEYCODE_MAX];
char old_key[D_KEYCODE_MAX];

int CheckKeycodeRange(int keycode)
{
	if (0 <= keycode && keycode < D_KEYCODE_MAX)
	{
		return TRUE;
	}
	return FALSE;
}

void InputManagerUpdate(void)
{
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));

	GetHitKeyStateAll(now_key);
}

eInputState GetKeyInputState(int keycode)
{
	if (CheckKeycodeRange(keycode) == TRUE)
	{
		if (old_key[keycode] == TRUE)
		{
			if (now_key[keycode] == TRUE)
			{
				return eHold;
			}
			else
			{
				return eRelease;
			}
		}
		else
		{
			if (now_key[keycode] == TRUE)
			{
				return ePress;
			}
		}
	}

	return eNone;
}