#include "HelpScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

//ヘルプシーン初期化
void HelpSceneInit(void)
{

}

//ヘルプシーン更新
eSceneType HelpSceneUpdate(void)
{
	if (GetKeyInputState(KEY_INPUT_Z) == ePress)
	{
		return eInGame;								//インゲームへ
	}
	if (GetKeyInputState(KEY_INPUT_X) == ePress)
	{
		return eTitle;								//タイトル画面へ
	}
	return eHelp;
}


void HelpSceneDraw(void)
{
	SetFontSize(40);
	DrawString(1000, 550, "Z:ゲーム開始\nX:タイトル\n", GetColor(255, 255, 255));			//ゲーム開始とタイトルへの表示
	SetFontSize(16);
}