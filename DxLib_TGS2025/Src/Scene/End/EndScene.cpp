#include "EndScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

void Play_Sound_End(int sound, int volume);

End end;
int black_count1 = end.fps / 3;
int black_count2 = 0;
int black_count3 = 0;
int fps2=0;
int fps3=0;
//ヘルプシーン初期化
void EndSceneInit(void)
{
	end.image= LoadGraph("Resource/Images/EndScene_image.png");
	end.fps = 0;
	end.black= LoadGraph("Resource/Images/end_black.png");
	end.black_count = 0;
	end.bgm= LoadSoundMem("Resource/Sounds/End.mp3");
	Play_Sound_End(end.bgm, 130);
}

//ヘルプシーン更新
eSceneType EndSceneUpdate(void)
{
	end.fps++;

	if (end.fps > 300)
	{
		return eEnd2;
	}

	return eEnd;


}


void EndSceneDraw(void)
{
	
	black_count1 = end.fps / 3;
	DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, end.image, TRUE);
	if (end.fps >= 1)
	{
		DrawRotaGraph(840 + 110 * black_count1, 200, 1.0, 0.0, end.black, TRUE);
	}
	else
	{
		DrawRotaGraph(750 + 110 * black_count1, 200, 1.0, 0.0, end.black, TRUE);
	}
	if (end.fps >= 35)
	{
		fps2++;
		black_count2 = fps2 / 3;
		DrawRotaGraph(850 + 110 * black_count2, 350, 0.75, 0.0, end.black, TRUE);
	}
	else
	{
		DrawRotaGraph(750 + 110 * black_count2, 350, 0.75, 0.0, end.black, TRUE);
	}
	if (end.fps >= 50)
	{
		fps3++;
		black_count3 = fps3 / 3;
		DrawRotaGraph(650 + 110 * black_count3, 550, 1.0, 0.0, end.black, TRUE);
	}
	else
	{
		DrawRotaGraph(850 + 110 * black_count3, 550, 1.0, 0.0, end.black, TRUE);
	}
	//DrawFormatString(100, 100, GetColor(255, 255, 255), "%d", end.black_count);
	//SetFontSize(40);
	//DrawString(1000, 550, "Z:ゲーム開始\nX:タイトル\n", GetColor(255, 255, 255));			//ゲーム開始とタイトルへの表示
	//SetFontSize(16);
}

void Play_Sound_End(int sound, int volume)
{

	if (CheckSoundMem(sound) == 0)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);
		ChangeVolumeSoundMem(volume, sound);
	}
}