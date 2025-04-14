#include "ResultScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"
#include <stdlib.h>

int result_score;		//表示するスコアの値

//リザルト画面初期化
void ResultSceneInit(void)
{

}

//リザルトシーンの更新
eSceneType ResultSceneUpdate(void)
{
	Output_Score();
	//スペースキーが押されると
	if (GetKeyInputState(KEY_INPUT_Z) == ePress)
	{
		//タイトル画面へ
		return eTitle;
	}
	return eResult;
}

//リザルトシーンの描画
void ResultSceneDraw(void)
{
	unsigned int color;		//色の値
	SetFontSize(80);
	//スコアの値が０より小さいとき
	if (result_score < 0)
	{
		color = GetColor(255, 50, 50);
	}
	//スコアの値が0以上
	else
	{
		color = GetColor(100, 100, 230);
	}
	DrawFormatString(300, 200, color, "スコア     %d", result_score); //スコアの表示
	SetFontSize(40);
	DrawString(50, 650, "Z:タイトル画面", GetColor(255, 255, 255));	  //タイトル画面への表示
}

//表示するスコアの変数を渡す
int* Get_score(void)
{
	return &result_score;
}

//スコアの出力
void Output_Score(void)
{
	FILE* fp;
	char High_score[100];
	errno_t err;
	err = fopen_s(&fp, "Resource/Data/HighScore.txt", "r");			//読み取り
	if (err == 0)
	{
		fgets(High_score, 100 - 1, fp);
		fclose(fp);
		DrawFormatString(450, 500, GetColor(100, 255, 100), "ハイスコア   %d", atoi(High_score));	//ハイスコア表示
	}
	else
	{
		DrawFormatString(100, 500, GetColor(255, 255, 255), "err");	//エラー表示
	}
}