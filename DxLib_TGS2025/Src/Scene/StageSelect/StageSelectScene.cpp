#include "StageSelectScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/PadInputManager.h"
#include"../InGame/InGameScene.h"
#include"../Title/TitleScene.h"

#include "DxLib.h"
#include <stdlib.h>

int result_score;		//表示するスコアの値

//音がなっていないなら鳴らす
void Play_Sound_StageSelect(int sound, int volume);
//音が鳴っていても条件が合えば鳴らす
void Play_Sound_StageSelect_NC(int sound, int volume);
//タイトルBGMを止める
void Stop_Title_BGM(const Title* title);
//タイトルBGMが流れていなかったら流す
void Play_StageSelect_BGM(const Title* title);



StageSelect stageselect;
//リザルト画面初期化
void StageSelectSceneInit(void)
{  
	//ポジションの初期化
	stageselect.position.x = 400.0f;
	stageselect.position.y = 235.0f;
	//ステージ番号の初期化
	stageselect.number = 0;
	//ステージ配列の初期化
	stageselect.array_number = 0;
	//ステージ配列の添字の初期化
	stageselect.array_x = 0;
	stageselect.array_y = 0;

	//ボタンの画像拡大率の初期化
	stageselect.Abutton_rate = 0.15f;
	stageselect.rate_num = 0.1;

	//画像の取得
	//背景
	stageselect.background_image = LoadGraph("Resource/images/StageSelect.png");
	//マスの画像
	stageselect.trout_image[0] = LoadGraph("Resource/images/StageTrout.png");
	stageselect.trout_image[1] = LoadGraph("Resource/images/StageTrout2.png");
	stageselect.trout_image[2] = LoadGraph("Resource/images/BackTrout2.png");
	//数字の画像
	stageselect.number_image[0] = LoadGraph("Resource/images/1.png");
	stageselect.number_image[1] = LoadGraph("Resource/images/2.png");
	stageselect.number_image[2] = LoadGraph("Resource/images/3.png");
	stageselect.number_image[3] = LoadGraph("Resource/images/4.png");
	stageselect.number_image[4] = LoadGraph("Resource/images/5.png");
	stageselect.number_image[5] = LoadGraph("Resource/images/6.png");
	//車の画像
	stageselect.car_image = LoadGraph("Resource/images/car2_right.png");
	//ボタンの画像
	stageselect.Abutton = LoadGraph("Resource/images/Abutton.png");

	//カーソルとボタンのSE
	stageselect.cursor_se = LoadSoundMem("Resource/Sounds/stage_select_cursor.mp3");
	stageselect.button_se = LoadSoundMem("Resource/Sounds/stageselect_button.mp3");

	Play_StageSelect_BGM(GetTitle());

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
	//ボタンの描画
	SelectButtonDraw();

	PadInputManager* pad_input = PadInputManager::GetInstance();

	//Aボタンが押されたとき
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		//ステージ番号が-1じゃなければ
		if (stageselect.number != -1 && stageselect.number != 6)
		{
			Stop_Title_BGM(GetTitle());
			Play_Sound_StageSelect(stageselect.button_se, 80);
			StageSelectNumber();
			return eInGame;	//インゲーム画面へ
		}
		else if (stageselect.number == 6)
		{
			Play_Sound_StageSelect(stageselect.button_se, 80);
			return eTitle;
		}
	}
	return eStageSelect;
}

//ステージセレクトシーンの描画
void StageSelectSceneDraw(void)
{
	//背景の描画
	DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, stageselect.background_image, TRUE);
	//数字、枠、車の描画
	NumTroutDraw();
	
	
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
			// 移動のSE（もし使うならここに入れてね）
			Play_Sound_StageSelect_NC(stageselect.cursor_se, 80);
		}

		
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
			// 移動のSE（左とおんなじ音入れてね）
			Play_Sound_StageSelect_NC(stageselect.cursor_se, 80);
		}
		
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
	case 5:
		stageselect.number = eSix;
		break;
	}
}

//ステージ番号を持っている時
void StageSelectGetNumber(void)
{
	//0～2までの番号
	if (stageselect.array_y == 0)
	{
		stageselect.number = stageselect.array_x;
	}
	//3～5までの番号
	else if (stageselect.array_y == 1)
	{
		stageselect.number = stageselect.array_x + 3;
	}
	//6番
	else if (stageselect.array_y == 2)
	{
		stageselect.number = 6;
	}
	else 
	{
		stageselect.number = -1;
	}
}

//数字、枠、車の描画
void NumTroutDraw(void)
{
	//数字と枠の描画
	stageselect.array_number = 0;
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			//X座標が280.0ｆ（余白）+端から中心までの120.0ｆ
			//Y座標が135.0ｆ（余白）+端から中心までの100.0f
			//枠の描画
			DrawRotaGraphF(i * 240.0f + 400.0f, j * 200.0f + 235.0f, 0.4, 0.0, stageselect.trout_array[i][j], TRUE);
			//数字の描画
			DrawRotaGraphF(i * 240.0f + 400.0f, j * 200.0f + 210.0f, 0.4, 0.0, stageselect.number_image[stageselect.array_number], TRUE);
			stageselect.array_number++;
		}
	}

	//車のいる枠が葉っぱつきになる描画
	if (stageselect.array_y != 2)
	{
		DrawRotaGraph(stageselect.position.x, stageselect.position.y, 0.4, 0.0, stageselect.trout_image[1], TRUE);
		/*DrawRotaGraph(stageselect.position.x, stageselect.position.y + 50.0f, 0.1, 0.0, stageselect.car_image, TRUE);*/
		DrawRotaGraph(stageselect.position.x, stageselect.position.y + 60.0f, stageselect.Abutton_rate, 0.0, stageselect.Abutton, TRUE);

	}
	//BACKの枠だけ描画する画像を変える
	else if (stageselect.array_y == 2)
	{
		DrawRotaGraph(stageselect.position.x, stageselect.position.y, 1.0, 0.0, stageselect.trout_image[2], TRUE);
		/*DrawRotaGraph(stageselect.position.x, stageselect.position.y, 0.1, 0.0, stageselect.car_image, TRUE);*/
		DrawRotaGraph(stageselect.position.x, stageselect.position.y, stageselect.Abutton_rate, 0.0, stageselect.Abutton, TRUE);
	}


}

//ボタンの描画　大きさが変わる
void SelectButtonDraw(void)
{
	
	if (stageselect.Abutton_rate > 0.15)
	{
		stageselect.rate_num = -0.0008f;
	}
	else if (stageselect.Abutton_rate < 0.10)
	{
		stageselect.rate_num = 0.0008f;
	}
	stageselect.Abutton_rate += stageselect.rate_num;
	/*DrawRotaGraph(640, 340, stageselect.Abutton_rate, 0.0, stageselect.Abutton, TRUE);*/
}

//音がなっていないなら鳴らす
void Play_Sound_StageSelect(int sound, int volume)
{
	if (CheckSoundMem(sound) == 0)
	{
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);
		ChangeVolumeSoundMem(volume, sound);
	}

}

//音が鳴っていても条件が合えば鳴らす
void Play_Sound_StageSelect_NC(int sound, int volume)
{
	PlaySoundMem(sound, DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(volume, sound);
}

//タイトルのBGMを止める
void Stop_Title_BGM(const Title* title)
{
	StopSoundMem(title->bgm);
}

//タイトルのBGMがなっていなかったら流す
void Play_StageSelect_BGM(const Title* title)
{
	if (CheckSoundMem(title->bgm) == 0)
	{
		ChangeVolumeSoundMem(100, title->bgm);
		PlaySoundMem(title->bgm, DX_PLAYTYPE_BACK);
	}
}