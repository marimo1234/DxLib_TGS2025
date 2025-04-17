#include"DxLib.h"
#include"map.h"

int ground;

void MapInit(void)
{
	ground = LoadGraph("Resource/GroundReef.png");
}
void MapUpdate(void)
{

}
void MapDraw(void)
{
	DrawGraphF(320,240, ground, TRUE);
}