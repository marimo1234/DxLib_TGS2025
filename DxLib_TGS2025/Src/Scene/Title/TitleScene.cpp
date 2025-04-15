#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"
#include <math.h>

int title_image;		//タイトル画像のハンドル

//タイトルシーンの初期化
void TitleSceneInit(void)
{
	//画像の読み込み
	//title_image = LoadGraph("Resource/Images/Title.png");	//タイトル画像

	//seの読み込み
	//select_SE = LoadSoundMem("Resource/SE/select.mp3");		//セレクトサウンド
	//decision_SE = LoadSoundMem("Resource/SE/decision.mp3");	//決定サウンド
}


//タイトルシーンの更新
eSceneType TitleSceneUpdate(void)
{
	//スペースキーが押された瞬間に、各画面に遷移する
	if (GetKeyInputState(KEY_INPUT_SPACE) == ePress)
	{
		return eInGame;	//インゲーム画面へ
	}
	return eTitle;
}

//タイトルシーン描画
void TitleSceneDraw(void)
{
	//DrawGraph(0, 0, title_image, TRUE);								//背景
	DrawFormatString(100, 100, GetColor(255, 255, 255), "スペースでインゲーム画面へ");
}