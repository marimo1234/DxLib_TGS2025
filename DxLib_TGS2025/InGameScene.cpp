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

int background;			//�w�i�摜�`��̃n���h��
int heart[5];			//�c�@�摜�̃n���h��
int heart_damage;		//�c�@�i�_���[�W�j�̃n���h��
int InGameBGM = 0;		//�C���Q�[����BGM�n���h��
float scrool_x;			//���X�N���[��
float heart_x = HEART_X;	//�c�@�̈ʒu�iX�j
float heart_y = HEART_Y;	//�c�@�̈ʒu�iY�j
int Before_Hit[10];		//�O�̓����蔻��
int Now_Hit[10];		//���̓����蔻��
int Obstacle_SE = 0;		//�X���C���ɓ����������ɂȂ鉹�̃n���h��
int score;				//�X�R�A
int heart_num;			//�c�@�̐�

void InGameSceneInit(void)
{
	//�w�i�摜�̓ǂݍ���
	background = LoadGraph("Resource/Images/background.png");

	//�c�@�摜�̓ǂݍ���
	for (heart_num = 0; heart_num < 5; heart_num++)
	{
		heart[heart_num] = LoadGraph("Resource/Images/heart.png");		//�c�@�̉摜�ǂݍ���
	}
	heart_damage = LoadGraph("Resource/Images/heart_damage.png");		//�c�@�i�_���[�W�j�̉摜�ǂݍ���
	heart_num = 0;

	//bgm,se�̓ǂݍ���
	InGameBGM = LoadSoundMem("Resource/BGM/Night_City_Safari.mp3");		//�C���Q�[��BGM
	Obstacle_SE = LoadSoundMem("Resource/SE/Hit.mp3");					//�X���C���ɓ���������
	PlayBgm();

	//�v���C���[�̏�����
	PlayerInit();
	//��Q���̏�����
	ObstacleManagerInit();

	scrool_x = 0.0f;
	score = 0;
}

eSceneType InGameSceneUpdate()
{
	//�v���C���[�̍X�V
	PlayerUpdate();
	//��Q���̍X�V
	ObstacleManagerUpdate();

	//�v���C���[���ړ������������w�i�����炷
	scrool_x -= GetPlayer()->velocity.x;
	if (scrool_x <= -1280.0f)
	{
		scrool_x += 1280.0f;
	}

	/*�����蔻��̌v�Z�i�v���C���[�Ə�Q���j*/
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
	//�w�i�摜�̕`��
	DrawGraphF(scrool_x, 0, background, TRUE);
	DrawGraphF(1280.0f + scrool_x, 0, background, TRUE);

	//�c�@�̕`��
	for (int i = 0; i < 5; i++)
	{
		DrawRotaGraphF(heart_x + heart_x * i, heart_y, 0.15, 0.0, heart[i], TRUE);
	}

	//�X�R�A�̌v�Z�ƕ\��
	score += NowScore(GetPlayer());
	SetFontSize(40);
	DrawFormatString(100, 200, GetColor(255, 255, 255), "���݂̃X�R�A");
	SetFontSize(60);
	DrawFormatString(400, 180, GetColor(0, 255, 255), "%d", score);

	//��Q���̕`��
	ObstacleManagerDraw();

	//�v���C���[�̕`��
	PlayerDraw();
}


//��`���m�̓����蔻��̌v�Z����
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

//�C���Q�[��BGM�Đ�
void PlayBgm(void)
{
	PlaySoundMem(InGameBGM, DX_PLAYTYPE_LOOP);
}

//����������
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

//�������Ă��Ȃ��Ƃ�
void NoHitAction(int index)
{
	Before_Hit[index] = Now_Hit[index];
	Now_Hit[index] = 0;
}

//�X�R�A�v�Z
int NowScore(const Player* player)
{

	double score = 0;
	score += player->velocity.x * 0.5;

	return (int)score;
}

//�X�R�A�̒l����
void Put_Score(int* Score)
{
	*Score = score;
}

//�t�@�C���ւ̃n�C�X�R�A����
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