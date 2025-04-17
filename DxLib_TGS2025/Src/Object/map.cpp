#include"DxLib.h"
#include"map.h"

int ground;

void MapInit(void)
{
	ground = LoadGraph("Resource/GroundReef.png");
}
void MapUpdate(int stage)
{

}
void MapDraw(void)
{
	DrawGraphF(0,0, ground, TRUE);
}