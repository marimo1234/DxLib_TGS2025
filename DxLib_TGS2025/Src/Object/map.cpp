#include"DxLib.h"
#include"map.h"
#define x 256
#define y 256

int ground;
int groundreef;
int sea;
int trout[x][y];
int math;
void MapInit(void)
{
	groundreef = LoadGraph("Resource/images/MapOriginal - ÉRÉsÅ[.png");
	ground = LoadGraph("Resource/images/Map2.png");
	sea = LoadGraph("Resource/images/art_119.png");
	math= LoadGraph("Resource/images/1trout.png");

}
void MapUpdate(void)
{

}
void MapDraw(int stage)
{
	stage = 1;
	switch (stage)
	{
	case 1:
		
		
		DrawRotaGraphF(600, 374, 0.7, 0.0, ground, TRUE);
		DrawRotaGraphF(620, 380, 0.4, 0.0, groundreef, TRUE);
		trout[0][0]= DrawRotaGraphF(540, 380, 1.0, 0.0, math, TRUE);
		trout[1][0] = DrawRotaGraphF(615, 380, 1.0, 0.0, math, TRUE);
		trout[2][0] = DrawRotaGraphF(690, 380, 1.0, 0.0, math, TRUE);
		break;
	case 2:
		
	default:
		break;
	}
	
}