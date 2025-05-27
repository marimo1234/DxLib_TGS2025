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
	stageselect.position.x = 400.0f;
	stageselect.position.y = 435.0f;
	stageselect.number = 0;
	stageselect.array_number = 0;
	stageselect.array_x = 0;
	stageselect.array_y = 0;


	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			stageselect.torut_array[i][j] = -1;
		}
	}


	stageselect.background_image = LoadGraph("Resource/images/StageSelect.png");
	stageselect.trout_image[0] = LoadGraph("Resource/images/StageTrout.png");
	stageselect.trout_image[1] = LoadGraph("Resource/images/StageTrout2.png");


    stageselect.number_image[0] = LoadGraph("Resource/images/1.png");
    stageselect.number_image[1] = LoadGraph("Resource/images/2.png");
    stageselect.number_image[2] = LoadGraph("Resource/images/3.png");
    stageselect.number_image[3] = LoadGraph("Resource/images/4.png");
    stageselect.number_image[4] = LoadGraph("Resource/images/5.png");

	stageselect.car_image= LoadGraph("Resource/images/car2_right.png");
	
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
	stageselect.array_number = 0;
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			//X座標が280.0ｆ（余白）+端から中心までの120.0ｆ
			//Y座標が135.0ｆ（余白）+端から中心までの100.0f
			DrawRotaGraphF(400.0f + i * 240.0f, 235.0f + j * 200.0f, 0.4, 0.0, stageselect.trout_image[0], TRUE);
			if (!(i == 0 && j == 1))
			{
				DrawRotaGraphF(400.0f + i * 240.0f, 235.0f + j * 200.0f, 0.4, 0.0, stageselect.number_image[stageselect.array_number], TRUE);
				stageselect.array_number++;
			}
		}
	}

	DrawRotaGraph(400.0f, 435.0f, 0.2, 0.0, stageselect.car_image, TRUE);
	
	DrawExtendFormatString(470, 360, 2.0, 2.0, GetColor(255, 255, 255), "Xボタンでインゲーム画面へ");
	/*DrawFormatString(100, 100, GetColor(255, 255, 255), "zでタイトル画面へ");*/
}

const StageSelect* GetStageSelect(void)
{
	return &stageselect;
}


void CursolButtonMovement(void)
{

	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::ePress)
	{

		// 十字ボタンの左を押したとき
		if (stageselect.array_x > 0)
		{
			stageselect.array_x--;
			stageselect.position.x = 240.0f * stageselect.array_x + 200.0f;

		}
		else if (stageselect.array_x == 0)
		{
			stageselect.array_x = 2;
			stageselect.position.x = 240.0f * stageselect.array_x + 200.0f;
		}

		// 移動のSE（もし使うならここに入れてね）

	}
	else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
	{
		// 十字ボタンの右を押したとき
		if (stageselect.array_x < 2)
		{
			stageselect.array_x++;
			stageselect.position.x = 240.0f * stageselect.array_x + 200.0f;

		}
		else if (stageselect.array_x == 2)
		{
			stageselect.array_x = 0;
			stageselect.position.x = 240.0f * stageselect.array_x + 200.0f;
		}
		// 移動のSE（左とおんなじ音入れてね）

	}
	else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
	{
		// 十字ボタンの上を押したとき
		if (stageselect.array_y > 0)
		{
			stageselect.array_y--;
			stageselect.position.y = 200.0f * stageselect.array_y + 120.0f;

		}
		else if (stageselect.array_y == 0)
		{
			stageselect.array_y = 1;
			stageselect.position.y = 200.0f * stageselect.array_y + 120.0f;
		}
		// 移動のSE（左とおんなじ音入れてね）

	}
	else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
	{
		// 十字ボタンの下を押したとき
		if (stageselect.array_y < 1)
		{
			stageselect.array_y++;
			stageselect.position.y = 200.0f * stageselect.array_y + 120.0f;

		}
		else if (stageselect.array_y == 1)
		{
			stageselect.array_y = 0;
			stageselect.position.y = 200.0f * stageselect.array_y + 120.0f;
		}
		// 移動のSE（左とおんなじ音入れてね）

	}
}