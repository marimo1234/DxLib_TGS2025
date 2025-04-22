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
	//zキーが押されると
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
	DrawFormatString(100, 100, GetColor(255, 255, 255), "zでタイトル画面へ");
}

