#include"DxLib.h"
#include"map.h"

int ground;

void MapInit(void)
{
	ground = LoadGraph("Resource/images/GroundReef.png");
}
void MapUpdate(void)
{

}
void MapDraw(int stage)
{
	
	DrawRotaGraphF(640,380,0.5+stage,0.0, ground, TRUE);
}