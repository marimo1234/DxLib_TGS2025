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
	stageselect.position.x = 0.0f;
	stageselect.position.y = 0.0f;
	stageselect.number = 0;

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			stageselect.torut_array[i][j] = -1;
		}
	}


	stageselect.background_image = LoadGraph("Resource/images/StageSelect.png");
	stageselect.trout_image[0] = LoadGraph("Resource/images/StageTrout.png");
	/*stageselect.trout_image[1] = LoadGraph("Resource/images/StageSelect.png");*/


    stageselect.number_image[0] = LoadGraph("Resource/images/1.png");
    stageselect.number_image[1] = LoadGraph("Resource/images/2.png");
    stageselect.number_image[2] = LoadGraph("Resource/images/3.png");
    stageselect.number_image[3] = LoadGraph("Resource/images/4.png");
    stageselect.number_image[4] = LoadGraph("Resource/images/5.png");
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
	DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, stageselect.background_image, TRUE);
	for (int i = 0; i < 6; i++)
	{
		DrawRotaGraphF(400.0f, 360.0f, 0.3, 0.0, stageselect.trout_image[0], TRUE);
	}
	
	DrawRotaGraphF(640.0f, 360.0f, 0.3, 0.0, stageselect.number_image[0], TRUE);
	DrawExtendFormatString(470, 360, 2.0, 2.0, GetColor(255, 255, 255), "Xボタンでインゲーム画面へ");
	/*DrawFormatString(100, 100, GetColor(255, 255, 255), "zでタイトル画面へ");*/
}

const StageSelect* GetStageSelect(void)
{
	return &stageselect;
}


