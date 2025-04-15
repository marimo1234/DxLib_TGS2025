#pragma once

#include "../Utility/Geometry.h"

struct Player
{
	Position2D position;
	Size2D box_size;		//‹éŒ`‚Ì‘å‚«‚³
	Vector2D velocity;
	int image;
	int is_jump;
};

void PlayerInit(void);
void PlayerUpdate(void);
void PlayerDraw(void);


