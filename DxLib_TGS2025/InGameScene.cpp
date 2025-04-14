#include "InGameScene.h"

#include "../../Object/Player.h"
#include "../../Object/Obstacle.h"
#include "../Result/ResultScene.h"
#include "DxLib.h"

#include <math.h>
#include <stdlib.h>

#define D_SCROOL_SPEED		(200.0f)
#define HEART_X		(60.0f)
#define HEART_Y		(40.0f)

void HitCheck(const Player* player, const Obstacle* obstacle, int index);
int NowScore(const Player* player);
void PlayBgm(void);

int background;			//背景画像描画のハンドル
int heart[5];			//残機画像のハンドル
int heart_damage;		//残機（ダメージ）のハンドル
int InGameBGM = 0;		//インゲームのBGMハンドル
float scrool_x;			//横スクロール
float heart_x = HEART_X;	//残機の位置（X）
float heart_y = HEART_Y;	//残機の位置（Y）
int Before_Hit[10];		//前の当たり判定
int Now_Hit[10];		//今の当たり判定
int Obstacle_SE = 0;		//スライムに当たった時になる音のハンドル
int score;				//スコア
int heart_num;			//残機の数

void InGameSceneInit(void)
{
	//背景画像の読み込み
	background = LoadGraph("Resource/Images/background.png");

	//残機画像の読み込み
	for (heart_num = 0; heart_num < 5; heart_num++)
	{
		heart[heart_num] = LoadGraph("Resource/Images/heart.png");		//残機の画像読み込み
	}
	heart_damage = LoadGraph("Resource/Images/heart_damage.png");		//残機（ダメージ）の画像読み込み
	heart_num = 0;

	//bgm,seの読み込み
	InGameBGM = LoadSoundMem("Resource/BGM/Night_City_Safari.mp3");		//インゲームBGM
	Obstacle_SE = LoadSoundMem("Resource/SE/Hit.mp3");					//スライムに当たった時
	PlayBgm();

	//プレイヤーの初期化
	PlayerInit();
	//障害物の初期化
	ObstacleManagerInit();

	scrool_x = 0.0f;
	score = 0;
}

eSceneType InGameSceneUpdate()
{
	//プレイヤーの更新
	PlayerUpdate();
	//障害物の更新
	ObstacleManagerUpdate();

	//プレイヤーが移動した分だけ背景をずらす
	scrool_x -= GetPlayer()->velocity.x;
	if (scrool_x <= -1280.0f)
	{
		scrool_x += 1280.0f;
	}

	/*当たり判定の計算（プレイヤーと障害物）*/
	for (int i = 0; i < D_OBSTACLE_MAX; i++)
	{
		HitCheck(GetPlayer(), GetObstacle(i), i);
	}

	if (heart_num > 4)
	{
		Input_File();
		Put_Score(Get_score());
		StopSoundMem(InGameBGM);
		return eResult;
	}

	return eInGame;
}

void InGameSceneDraw(void)
{
	//背景画像の描画
	DrawGraphF(scrool_x, 0, background, TRUE);
	DrawGraphF(1280.0f + scrool_x, 0, background, TRUE);

	//残機の描画
	for (int i = 0; i < 5; i++)
	{
		DrawRotaGraphF(heart_x + heart_x * i, heart_y, 0.15, 0.0, heart[i], TRUE);
	}

	//スコアの計算と表示
	score += NowScore(GetPlayer());
	SetFontSize(40);
	DrawFormatString(100, 200, GetColor(255, 255, 255), "現在のスコア");
	SetFontSize(60);
	DrawFormatString(400, 180, GetColor(0, 255, 255), "%d", score);

	//障害物の描画
	ObstacleManagerDraw();

	//プレイヤーの描画
	PlayerDraw();
}


//矩形同士の当たり判定の計算部分
void HitCheck(const Player* player, const Obstacle* obstacle, int index)
{
	if (obstacle->is_active == TRUE)
	{
		float dx = fabsf(player->position.x - obstacle->position.x);
		float dy = fabsf(player->position.y - obstacle->position.y);

		float bx = (player->box_size.x + obstacle->box_size.x) * 0.5f;
		float by = (player->box_size.y + obstacle->box_size.y) * 0.5f;

		if ((dx < bx) && (dy < by))
		{
			HitAction(index, &score, &heart[heart_num]);
		}
		else
		{
			NoHitAction(index);
		}
	}
}

//インゲームBGM再生
void PlayBgm(void)
{
	PlaySoundMem(InGameBGM, DX_PLAYTYPE_LOOP);
}

//当たった時
void HitAction(int index, int* score, int* heart)
{
	Before_Hit[index] = Now_Hit[index];
	Now_Hit[index] = 1;

	if (Before_Hit[index] == 0 && Now_Hit[index] == 1)
	{
		HitAction_Player(&index);
		if (index != 9)
		{
			PlaySoundMem(Obstacle_SE, DX_PLAYTYPE_BACK);
			*score -= 3000;
			*heart = heart_damage;
			heart_num++;
		}
	}
}

//当たっていないとき
void NoHitAction(int index)
{
	Before_Hit[index] = Now_Hit[index];
	Now_Hit[index] = 0;
}

//スコア計算
int NowScore(const Player* player)
{

	double score = 0;
	score += player->velocity.x * 0.5;

	return (int)score;
}

//スコアの値を代入
void Put_Score(int* Score)
{
	*Score = score;
}

//ファイルへのハイスコア入力
void Input_File(void)
{
	FILE* fp;
	char F_score[100];
	errno_t err;

	err = fopen_s(&fp, "Resource/Data/HighScore.txt", "r");
	if (err == 0)
	{
		fgets(F_score, 100 - 1, fp);
		fclose(fp);
		if (score > atoi(F_score))
		{
			err = fopen_s(&fp, "Resource/Data/HighScore.txt", "w");
			if (err == 0)
			{
				fprintf(fp, "%d", score);
				fclose(fp);
			}
		}
	}
}