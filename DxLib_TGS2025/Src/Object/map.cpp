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
	groundreef = LoadGraph("Resource/images/ChatGPT SOUGEN1.png");
	ground = LoadGraph("Resource/images/ChatGPT sougen.png");
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
		
		/*DrawRotaGraphF(540, 380, 1.0, 0.0, sea, TRUE);
		DrawRotaGraphF(530, 390, 0.1, 0.0, ground, TRUE);
		DrawRotaGraphF(532, 388, 0.1, 0.0, ground, TRUE);
		DrawRotaGraphF(534, 386, 0.1 , 0.0, ground, TRUE);
		DrawRotaGraphF(536, 384, 0.1 , 0.0, ground, TRUE);
		DrawRotaGraphF(538, 382, 0.1, 0.0, ground, TRUE);
        DrawRotaGraphF(630, 390, 0.1, 0.0, ground, TRUE);
		DrawRotaGraphF(632, 388, 0.1, 0.0, ground, TRUE);
		DrawRotaGraphF(634, 386, 0.1, 0.0, ground, TRUE);
		DrawRotaGraphF(636, 384, 0.1, 0.0, ground, TRUE);
		DrawRotaGraphF(638, 382, 0.1, 0.0, ground, TRUE);
		DrawRotaGraphF(730 - 50, 390, 0.1 , 0.0, ground, TRUE);
		DrawRotaGraphF(732 - 50, 388, 0.1 , 0.0, ground, TRUE);
		DrawRotaGraphF(734 - 50, 386, 0.1 , 0.0, ground, TRUE);
		DrawRotaGraphF(736 - 50, 384, 0.1 , 0.0, ground, TRUE);
		DrawRotaGraphF(738 - 50, 382, 0.1 , 0.0, ground, TRUE);
		DrawRotaGraphF(690, 380, 0.1 , 0.0, groundreef, TRUE);*/
		DrawRotaGraphF(640, 380, 0.4, 0.0, groundreef, TRUE);
		/*DrawRotaGraphF(960, 540, 0.4, 0.0, groundreef, TRUE);
		DrawRotaGraphF(960, 180, 0.4, 0.0, groundreef, TRUE);
		DrawRotaGraphF(320, 540, 0.4, 0.0, groundreef, TRUE);*/
		DrawRotaGraphF(625, 380, 0.3 , 0.0, ground, TRUE);
		trout[0][0]= DrawRotaGraphF(540, 380, 1.0, 0.0, math, TRUE);
		trout[1][0] = DrawRotaGraphF(615, 380, 1.0, 0.0, math, TRUE);
		trout[2][0] = DrawRotaGraphF(690, 380, 1.0, 0.0, math, TRUE);
		break;
	case 2:
		/*DrawRotaGraphF(540, 380, 1.0, 0.0, sea, TRUE);
		DrawRotaGraphF(600, 390, 0.3, 0.0, ground, TRUE);
		DrawRotaGraphF(602, 388, 0.3, 0.0, ground, TRUE);
		DrawRotaGraphF(604, 386, 0.3, 0.0, ground, TRUE);
		DrawRotaGraphF(606, 384, 0.3, 0.0, ground, TRUE)*/;
		DrawRotaGraphF(608, 382, 0.3, 0.0, ground, TRUE);
		DrawRotaGraphF(610, 380, 0.3, 0.0, groundreef, TRUE);
		trout[0][0] = DrawRotaGraphF(540, 387, 1.0, 0.0, math, TRUE);
		trout[1][0] = DrawRotaGraphF(615, 387, 1.0, 0.0, math, TRUE);
		trout[2][0] = DrawRotaGraphF(690, 387, 1.0, 0.0, math, TRUE);
		trout[0][1] = DrawRotaGraphF(540, 470, 1.0, 0.0, math, TRUE);
		trout[1][1] = DrawRotaGraphF(615, 470, 1.0, 0.0, math, TRUE);
		trout[2][1] = DrawRotaGraphF(690, 470, 1.0, 0.0, math, TRUE);
		trout[0][2] = DrawRotaGraphF(540, 304, 1.0, 0.0, math, TRUE);
		trout[1][2] = DrawRotaGraphF(615, 304, 1.0, 0.0, math, TRUE);
		trout[2][2] = DrawRotaGraphF(690, 304, 1.0, 0.0, math, TRUE);
	default:
		break;
	}
	/*DrawRotaGraphF(540, 380, 1.0, 0.0, sea, TRUE);
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
	DrawRotaGraphF(540,380,0.5+stage,0.0, groundreef, TRUE);*/
}