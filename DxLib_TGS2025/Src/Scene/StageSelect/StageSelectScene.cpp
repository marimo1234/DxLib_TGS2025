#include "StageSelectScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/PadInputManager.h"
#include "DxLib.h"
#include <stdlib.h>

int result_score;		//表示するスコアの値

//リザルト画面初期化
void StageSelectSceneInit(void)
{

}

//リザルトシーンの更新
eSceneType StageSelectSceneUpdate(void)
{

	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetButtonInputState(XINPUT_BUTTON_X) == ePadInputState::ePress)
	{
		return eInGame;	//インゲーム画面へ
	}
	return eStageSelect;
}

//リザルトシーンの描画
void StageSelectSceneDraw(void)
{
	DrawExtendFormatString(470, 360, 2.0, 2.0, GetColor(255, 255, 255), "Xボタンでインゲーム画面へ");
	/*DrawFormatString(100, 100, GetColor(255, 255, 255), "zでタイトル画面へ");*/
}

