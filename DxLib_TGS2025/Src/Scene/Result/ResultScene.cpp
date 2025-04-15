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
	
}

