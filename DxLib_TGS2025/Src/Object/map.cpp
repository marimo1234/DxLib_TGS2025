#include"DxLib.h"
#include"map.h"

int ground;
int groundreef;
int sea;
void MapInit(void)
{
	groundreef = LoadGraph("Resource/images/GroundReef.png");
	ground = LoadGraph("Resource/images/Ground.png");
	sea = LoadGraph("Resource/images/art_119.png");

}
void MapUpdate(void)
{

}
void MapDraw(int stage)
{
	
	DrawRotaGraphF(540, 380, 1.0, 0.0, sea, TRUE);
	DrawRotaGraphF(530, 390, 0.5 + stage, 0.0, ground, TRUE);
	DrawRotaGraphF(532, 388, 0.5 + stage, 0.0, ground, TRUE);
	DrawRotaGraphF(534, 386, 0.5 + stage, 0.0, ground, TRUE);
	DrawRotaGraphF(536, 384, 0.5 + stage, 0.0, ground, TRUE);
	DrawRotaGraphF(538, 382, 0.5 + stage, 0.0, ground, TRUE);
	DrawRotaGraphF(730, 390, 0.5 + stage, 0.0, ground, TRUE);
	DrawRotaGraphF(732, 388, 0.5 + stage, 0.0, ground, TRUE);
	DrawRotaGraphF(734, 386, 0.5 + stage, 0.0, ground, TRUE);
	DrawRotaGraphF(736, 384, 0.5 + stage, 0.0, ground, TRUE);
	DrawRotaGraphF(738, 382, 0.5 + stage, 0.0, ground, TRUE);
	DrawRotaGraphF(740, 380, 0.5 + stage, 0.0, groundreef, TRUE);
	DrawRotaGraphF(540,380,0.5+stage,0.0, groundreef, TRUE);
}