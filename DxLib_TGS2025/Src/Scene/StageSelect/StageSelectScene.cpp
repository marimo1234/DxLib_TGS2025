#include "StageSelectScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/PadInputManager.h"
#include"../InGame/InGameScene.h"

#include "DxLib.h"
#include <stdlib.h>

int result_score;		//表示するスコアの値


StageSelect stageselect;
//リザルト画面初期化
void StageSelectSceneInit(void)
{
	stageselect.background_image = 0;
	stageselect.position.x=0.0f;
	stageselect.position.y=0.0f;
	stageselect.number = 0;
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
	/*DrawRotaGraph(stageselect.position.x, stageselect.position.y, 0.0, 1.0, stageselect.background_image, TRUE);*/
	DrawExtendFormatString(470, 360, 2.0, 2.0, GetColor(255, 255, 255), "Xボタンでインゲーム画面へ");
	/*DrawFormatString(100, 100, GetColor(255, 255, 255), "zでタイトル画面へ");*/
}

const StageSelect* GetStageSelect(void)
{
	return &stageselect;
}


