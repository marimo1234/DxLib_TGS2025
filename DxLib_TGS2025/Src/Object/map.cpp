#include"DxLib.h"
#include"map.h"

int ground;
int sea;
void MapInit(void)
{
	ground = LoadGraph("Resource/images/GroundReef.png");
	sea = LoadGraph("Resource/images/art_119.png");
}
void MapUpdate(void)
{

}
void MapDraw(int stage)
{
	DrawRotaGraphF(640, 380, 1.0, 0.0, sea, TRUE);
	DrawRotaGraphF(640,380,0.5+stage,0.0, ground, TRUE);
}