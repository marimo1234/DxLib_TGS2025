#include "StageSelectScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/PadInputManager.h"
#include"../InGame/InGameScene.h"

#include "DxLib.h"
#include <stdlib.h>

int result_score;		//表示するスコアの値


void Play_Sound_StageSelect(int sound, int volume);

void Play_Sound_StageSelect_NC(int sound, int volume);



StageSelect stageselect;
//リザルト画面初期化
void StageSelectSceneInit(void)
{  
	//ポジションの初期化
	stageselect.position.x = 400.0f;
	stageselect.position.y = 435.0f;
	//ステージ番号の初期化
	stageselect.number = 0;
	//ステージ配列の初期化
	stageselect.array_number = 0;
	//ステージ配列の添字の初期化
	stageselect.array_x = 0;
	stageselect.array_y = 1;

	stageselect.Abottom_rate = 1.0f;
	stageselect.rate_num = 0.1;

	//画像の取得
	stageselect.background_image = LoadGraph("Resource/images/StageSelect.png");
	stageselect.trout_image[0] = LoadGraph("Resource/images/StageTrout.png");
	stageselect.trout_image[1] = LoadGraph("Resource/images/StageTrout2.png");
	stageselect.trout_image[2] = LoadGraph("Resource/images/BackTrout2.png");

	stageselect.number_image[0] = LoadGraph("Resource/images/1.png");
	stageselect.number_image[1] = LoadGraph("Resource/images/2.png");
	stageselect.number_image[2] = LoadGraph("Resource/images/3.png");
	stageselect.number_image[3] = LoadGraph("Resource/images/4.png");
	stageselect.number_image[4] = LoadGraph("Resource/images/5.png");

	stageselect.car_image = LoadGraph("Resource/images/car2_right.png");

	stageselect.Abottom = LoadGraph("Resource/images/Abottom.png");

	stageselect.cursor_se = LoadSoundMem("Resource/Sounds/stage_select_cursor.mp3");
	stageselect.button_se = LoadSoundMem("Resource/Sounds/stageselect_button.mp3");

	//配列にデフォルトの枠を入れる
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			stageselect.trout_array[i][j] = stageselect.trout_image[0];
		}
	} 
}

//ステージセレクトシーンの更新
eSceneType StageSelectSceneUpdate(void)
{
	//ステージセレクト画面の車のムーブ
	StageSelectCarMove();

	//車がいる場所の配列番号でステージ番号を取得
	StageSelectGetNumber();


	PadInputManager* pad_input = PadInputManager::GetInstance();

	//Aボタンが押されたとき
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		//ステージ番号が-1じゃなければ
		if (stageselect.number != -1 && stageselect.number != 5)
		{
			Play_Sound_StageSelect(stageselect.button_se, 80);
			StageSelectNumber();
			return eInGame;	//インゲーム画面へ
		}
		else if (stageselect.number == 5)
		{
			Play_Sound_StageSelect(stageselect.button_se, 80);
			return eTitle;
		}
	}
	return eStageSelect;
}

//リザルトシーンの描画
void StageSelectSceneDraw(void)
{
	//背景の描画
	DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, stageselect.background_image, TRUE);

	//数字と枠の描画（左下は何もなし）
	stageselect.array_number = 0;
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			//X座標が280.0ｆ（余白）+端から中心までの120.0ｆ
			//Y座標が135.0ｆ（余白）+端から中心までの100.0f
			DrawRotaGraphF(i * 240.0f + 400.0f, j * 200.0f + 235.0f, 0.4, 0.0, stageselect.trout_array[i][j], TRUE);
			if (!(i == 0 && j == 1))
			{
				DrawRotaGraphF(i * 240.0f + 400.0f, j * 200.0f + 235.0f, 0.4, 0.0, stageselect.number_image[stageselect.array_number], TRUE);
				stageselect.array_number++;
			}
		}
	}
	//車のいる枠が葉っぱつきになる描画
	if (stageselect.array_y != 2)
	{
		DrawRotaGraph(stageselect.position.x, stageselect.position.y, 0.4, 0.0, stageselect.trout_image[1], TRUE);
	}
	else if (stageselect.array_y == 2)
	{
		DrawRotaGraph(stageselect.position.x, stageselect.position.y, 1.0, 0.0, stageselect.trout_image[2], TRUE);
	}

	
	//択んでいる位置に車を描画
	DrawRotaGraph(stageselect.position.x, stageselect.position.y, 0.15, 0.0, stageselect.car_image, TRUE);

	if (stageselect.Abottom_rate > 1.3)
	{
		stageselect.rate_num = -0.005f;
	}
	else if (stageselect.Abottom_rate < 1.0)
	{
		stageselect.rate_num = 0.005f;
	}
	stageselect.Abottom_rate += stageselect.rate_num;
	DrawRotaGraph(640, 340, stageselect.Abottom_rate, 0.0, stageselect.Abottom, TRUE);
	/*DrawExtendFormatString(470, 360, 2.0, 2.0, GetColor(255, 255, 255), "Aボタンでインゲーム画面へ");*/
	/*DrawFormatString(100, 100, GetColor(255, 255, 255), "zでタイトル画面へ");*/
}

//StageSelectを取得
const StageSelect* GetStageSelect(void)
{
	return &stageselect;
}

////ステージセレクト画面の車のムーブ
void StageSelectCarMove(void)
{

	PadInputManager* pad_input = PadInputManager::GetInstance();

	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_LEFT) == ePadInputState::ePress)
	{

		if (stageselect.array_y != 2)
		{
			// 十字ボタンの左を押したとき
			if (stageselect.array_x > 0)
			{
				stageselect.array_x--;
				stageselect.position.x = 240.0f * stageselect.array_x + 400.0f;

			}
			else if (stageselect.array_x == 0)
			{
				stageselect.array_x = 2;
				stageselect.position.x = 240.0f * stageselect.array_x + 400.0f;
			}
		}

		// 移動のSE（もし使うならここに入れてね）
		Play_Sound_StageSelect_NC(stageselect.cursor_se, 80);
	}
	else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
	{

		if (stageselect.array_y != 2)
		{
			// 十字ボタンの右を押したとき
			if (stageselect.array_x < 2)
			{
				stageselect.array_x++;
				stageselect.position.x = 240.0f * stageselect.array_x + 400.0f;

			}
			else if (stageselect.array_x == 2)
			{
				stageselect.array_x = 0;
				stageselect.position.x = 240.0f * stageselect.array_x + 400.0f;
			}
		}
		// 移動のSE（左とおんなじ音入れてね）
		Play_Sound_StageSelect_NC(stageselect.cursor_se, 80);
	}
	else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
	{

		// 十字ボタンの上を押したとき
		if (stageselect.array_y > 0 && stageselect.array_y != 2)
		{
			stageselect.array_y--;
			stageselect.position.y = 200.0f * stageselect.array_y + 235.0f;

		}
		else if (stageselect.array_y == 0)
		{
			stageselect.array_y = 2;
			stageselect.position.x = 920.0f;
			stageselect.position.y = 605.0f;
		}
		else if (stageselect.array_y == 2)
		{
			stageselect.array_x = 2;
			stageselect.array_y--;
			stageselect.position.x = 240.0f * stageselect.array_x + 400.0f;
			stageselect.position.y = 200.0f * stageselect.array_y + 235.0f;
		}

		// 移動のSE（左とおんなじ音入れてね）
		Play_Sound_StageSelect_NC(stageselect.cursor_se, 80);
	}
	else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
	{

		// 十字ボタンの下を押したとき
		if (stageselect.array_y < 1)
		{
			stageselect.array_y++;
			stageselect.position.y = 200.0f * stageselect.array_y + 235.0f;

		}
		else if (stageselect.array_y == 1)
		{
			stageselect.array_y = 2;
			stageselect.position.x = 920.0f;
			stageselect.position.y = 605.0f;

		}
		else if (stageselect.array_y == 2)
		{
			stageselect.array_x = 2;
			stageselect.array_y = 0;
			stageselect.position.x = 240.0f * stageselect.array_x + 400.0f;
			stageselect.position.y = 200.0f * stageselect.array_y + 235.0f;
		}
		// 移動のSE（左とおんなじ音入れてね）
		Play_Sound_StageSelect_NC(stageselect.cursor_se, 80);
	}
}
//ステージ番号の分岐
void StageSelectNumber(void)
{
	switch (stageselect.number)
	{
	case 0:
		stageselect.number = eOne;
		break;
	case 1:
		stageselect.number = eTwo;
		break;
	case 2:
		stageselect.number = eThree;
		break;
	case 3:
		stageselect.number = eFour;
		break;
	case 4:
		stageselect.number = eFive;
		break;
	}
}

//ステージ番号を持っている時
void StageSelectGetNumber(void)
{
	if (stageselect.array_y == 0)
	{
		stageselect.number = stageselect.array_x;
	}
	else if (stageselect.array_y == 1 && stageselect.array_x != 0)
	{
		stageselect.number = stageselect.array_x + 2;
	}
	else if (stageselect.array_y == 2)
	{
		stageselect.number = 5;
	}
	else 
	{
		stageselect.number = -1;
	}
}

void Play_Sound_StageSelect(int sound, int volume)
{
	if (CheckSoundMem(sound) == 0)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);
		ChangeVolumeSoundMem(volume, sound);
	}

}

void Play_Sound_StageSelect_NC(int sound, int volume)
{
	PlaySoundMem(sound, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(volume, sound);
}
