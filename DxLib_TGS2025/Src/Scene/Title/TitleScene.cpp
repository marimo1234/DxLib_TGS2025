#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"
#include <math.h>

int title_image;		//タイトル画像のハンドル
int cursor_number;		//カーソルの番号
int cursor_y;			//縦位置
int cursor_image;		//カーソル画像のハンドル
int select_SE;			//セレクトのサウンドハンドル
int decision_SE;		//決定のサウンドハンドル

void SelectCursor();
void Select_Sound();

//タイトルシーンの初期化
void TitleSceneInit(void)
{
	//画像の読み込み
	title_image = LoadGraph("Resource/Images/Title.png");	//タイトル画像
	cursor_image = LoadGraph("Resource/Images/cursor.png");	//カーソル画像

	//seの読み込み
	select_SE = LoadSoundMem("Resource/SE/select.mp3");		//セレクトサウンド
	decision_SE = LoadSoundMem("Resource/SE/decision.mp3");	//決定サウンド

	//カーソルの初期位置の設定
	cursor_number = 0;
	cursor_y = 350;

}


//タイトルシーンの更新
eSceneType TitleSceneUpdate(void)
{
	//カーソル位置の変更
	SelectCursor();

	//スペースキーが押された瞬間に、各画面に遷移する
	if (GetKeyInputState(KEY_INPUT_SPACE) == ePress)
	{
		//決定したときの音（バックグラウンドで再生）
		PlaySoundMem(decision_SE, DX_PLAYTYPE_BACK);
		switch (cursor_number)
		{
		case 0:
			return eInGame;		//インゲーム画面へ
		case 1:
			return eHelp;		//ヘルプ画面へ
		case 2:
			return eEnd;		//終了
		default:
			break;
		}
	}
	return eTitle;
}

//タイトルシーン描画
void TitleSceneDraw(void)
{
	DrawGraph(0, 0, title_image, TRUE);								//背景
	DrawRotaGraph(750, cursor_y, 0.5, 0.0, cursor_image, TRUE);		//カーソル
}

//カーソルの位置変更
void SelectCursor()
{
	//矢印↑が押されたら
	if (GetKeyInputState(KEY_INPUT_UP) == ePress)
	{
		Select_Sound();
		cursor_number--;
		if (cursor_number < 0)
		{
			cursor_number = 2;
		}
	}
	//矢印↓が押されたら
	if (GetKeyInputState(KEY_INPUT_DOWN) == ePress)
	{
		Select_Sound();
		cursor_number++;
		cursor_number = cursor_number % 3;
	}

	//カーソルの座標を設定
	cursor_y = 360 + (cursor_number * 85);
}

//選択の音
void Select_Sound(void)
{
	//再生（バックグラウンド）
	PlaySoundMem(select_SE, DX_PLAYTYPE_BACK);
}