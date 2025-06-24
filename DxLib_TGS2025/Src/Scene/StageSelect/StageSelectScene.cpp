#include "StageSelectScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/PadInputManager.h"
#include"../InGame/InGameScene.h"
#include"../Title/TitleScene.h"
#include"../../Object/car.h"
#include"../../../Effect/Fade.h"
#include "DxLib.h"
#include <stdlib.h>

#define CAR_SPEED		(1.5f)

int stageselect_init_step = 0;;
static Fade fade;
static bool is_fading = false;

//音がなっていないなら鳴らす
void Play_Sound_StageSelect(int sound, int volume);
//音が鳴っていても条件が合えば鳴らす
void Play_Sound_StageSelect_NC(int sound, int volume);
//タイトルBGMを止める
void Stop_Title_BGM(const Title* title);
//タイトルBGMが流れていなかったら流す
void Play_StageSelect_BGM(const Title* title);
//車移動
void Move_Car(const Car* car);
void Set_Coordinate(int img1, int img2, float x, float y);

StageSelect stageselect;
//ステージセレクト画面初期化
void StageSelectSceneInit(void)
{  

	//fps
	stageselect.car_fps = 0;
	stageselect.move_fps = 0;

	//ポジションの初期化
	stageselect.position.x = 400.0f;
	stageselect.position.y = 255.0f;
	//ステージ番号の初期化
	stageselect.number = 0;
	stageselect.number_count = 0;

	//ステージ配列の初期化
	stageselect.array_number = 0;
	//ステージ配列の添字の初期化
	stageselect.array_x = 0;
	stageselect.array_y = 0;

	//ボタンの画像拡大率の初期化
	stageselect.Abutton_rate = 0.5f;
	stageselect.rate_num = 0.1;

	//車の描画座標
	stageselect.car_x = 0.0f;
	stageselect.car_y = 0.0f;
	stageselect.car_image1 = 0;
	stageselect.car_image2 = 0;
	stageselect.car_num = 0;
	stageselect.car_flag = false;

	stageselect.flag = true;

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			stageselect.number_extrate[i][j] = 0.3f;
		}
	}
	fade.Initialize(true);
	is_fading = true;

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

void StageSelectResourceInit(void)
{
	switch (stageselect_init_step)
	{
	case 0:
		//ボタンの画像
		stageselect.Abutton = LoadGraph("Resource/images/Abutton.png");
		stageselect.b_back = LoadGraph("Resource/images/Bback3.png");
		//カーソルとボタンのSE
		stageselect.cursor_se = LoadSoundMem("Resource/Sounds/stage_select_cursor.mp3");
		stageselect.button_se = LoadSoundMem("Resource/Sounds/stageselect_button.mp3");
		break;
	case 1:
		//画像の取得
	//背景
		stageselect.background_image = LoadGraph("Resource/images/StageSelect2.png");
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
		break;
	default:
		break;
	}
	stageselect_init_step++;
}

//ステージセレクトシーンの更新
eSceneType StageSelectSceneUpdate(void)
{
	if (is_fading)
	{
		fade.Update();
		if (fade.GetEndFlag())
		{
			is_fading = false;
		}
		return eStageSelect;
	}
//車がいる場所の配列番号でステージ番号を取得
	StageSelectGetNumber();
	
	ChangeNumberExtrate();

	Move_Car(GetCar());

	SelectButtonDraw();

	PadInputManager* pad_input = PadInputManager::GetInstance();

	//Aボタンが押されたとき
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress)
	{
		//ステージ番号が-1じゃなければ
		if (stageselect.number != -1)
		{
			stageselect.flag = false;
			Stop_Title_BGM(GetTitle());
			Play_Sound_StageSelect(stageselect.button_se, 80);
			StageSelectNumber();
			return eInGame;	//インゲーム画面へ
		}
	}
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
	{
		Play_Sound_StageSelect(stageselect.button_se, 80);
		return eTitle;
	}

	if (stageselect.flag == true)
	{
		//ステージセレクト画面の車のムーブ
		StageSelectCarMove();
	}
	return eStageSelect;
}

//ステージセレクトシーンの描画
void StageSelectSceneDraw(void)
{
	//背景の描画
	DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, stageselect.background_image, TRUE);
	
	//車描画
	Draw_Select_Car();

	//数字、枠、ボタンの描画
	NumTroutDraw();
	
	DrawRotaGraph(1142.0, 730.0, 0.1, 0.0, stageselect.Abutton, TRUE);
	/*DrawExtendFormatString(470, 360, 2.0, 2.0, GetColor(255, 255, 255), "Aボタンでインゲーム画面へ");*/
	/*DrawFormatString(100, 100, GetColor(255, 255, 255), "zでタイトル画面へ");*/

	fade.Draw();
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
			stageselect.number_count = 0;
	}
	else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_RIGHT) == ePadInputState::ePress)
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
			stageselect.number_count = 0;
		
	}
	else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
	{

		// 十字ボタンの上を押したとき
		if (stageselect.array_y > 0)
		{
			stageselect.array_y--;
			stageselect.position.y = 200.0f * stageselect.array_y + 255.0f;

		}
		else if (stageselect.array_y == 0)
		{
			stageselect.array_y = 1;
			stageselect.position.y = 200.0f * stageselect.array_y + 255.0f;
		}

		// 移動のSE（左とおんなじ音入れてね）
		Play_Sound_StageSelect_NC(stageselect.cursor_se, 80);
		stageselect.number_count = 0;
	}
	else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
	{

		// 十字ボタンの下を押したとき
		if (stageselect.array_y < 1)
		{
			stageselect.array_y++;
			stageselect.position.y = 200.0f * stageselect.array_y + 255.0f;

		}
		else if (stageselect.array_y == 1)
		{
			stageselect.array_y = 0;
			stageselect.position.y = 200.0f * stageselect.array_y + 255.0f;
		}
		// 移動のSE（左とおんなじ音入れてね）
		Play_Sound_StageSelect_NC(stageselect.cursor_se, 80);
		stageselect.number_count = 0;
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
			DrawRotaGraphF(i * 240.0f + 400.0f, j * 200.0f + 255.0f, 0.4, 0.0, stageselect.trout_array[i][j], TRUE);
			//数字の描画
			DrawRotaGraphF(i * 240.0f + 400.0f, j * 200.0f + 230.0f, stageselect.number_extrate[i][j], 0.0, stageselect.number_image[stageselect.array_number], TRUE);
			stageselect.array_number++;
		}
	}

	//車のいる枠が葉っぱつきになる描画
	if (stageselect.array_y != 2)
	{
		DrawRotaGraphF(stageselect.position.x, stageselect.position.y, 0.4, 0.0, stageselect.trout_image[1], TRUE);
		DrawRotaGraphF(stageselect.position.x, stageselect.position.y + 60.0f, stageselect.Abutton_rate, 0.0, stageselect.Abutton, TRUE);
	}

	DrawRotaGraphF(900.0f, 620.0f, 1.0, 0.0, stageselect.b_back, TRUE);
}

//ボタンの描画　大きさが変わる
void SelectButtonDraw(void)
{
	stageselect.number_count++;
	/*if (stageselect.Abutton_rate > 0.5)
	{
		stageselect.rate_num = -0.005f;
	}
	else if (stageselect.Abutton_rate < 0.3)
	{
		stageselect.rate_num = 0.005f;
	}
	stageselect.Abutton_rate += stageselect.rate_num;*/
	/*DrawRotaGraph(640, 340, stageselect.Abutton_rate, 0.0, stageselect.Abutton, TRUE);*/

	if (stageselect.number_count % 60 < 30)
	{
		stageselect.Abutton_rate = 0.4f;
	}
	else
	{
		stageselect.Abutton_rate = 0.0f;
	}

	if (stageselect.number_count > 60)
	{
		stageselect.number_count = 0;
	}
}

void ChangeNumberExtrate(void)
{
	/*stageselect.number_count++;*/
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			stageselect.number_extrate[i][j] = 0.3f;
		}
	}
	stageselect.number_extrate[stageselect.array_x][stageselect.array_y] = 0.4f;
	/*if (stageselect.number_count % 60 < 40)
	{
		stageselect.number_extrate[stageselect.array_x][stageselect.array_y] = 0.4f;
	}
	else
	{
		stageselect.number_extrate[stageselect.array_x][stageselect.array_y] = 0.0f;
	}

	if (stageselect.number_count > 60)
	{
		stageselect.number_count = 0;
	}*/
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

//車移動更新
void Move_Car(const Car*car)
{
	if (stageselect.car_flag == true)
	{
		switch (stageselect.car_num)
		{
		case 0:
			stageselect.car_y += CAR_SPEED;
			if (stageselect.car_y > 730.0f)
			{
				stageselect.car_flag = false;
			}
			break;
		case 1:
			stageselect.car_y += CAR_SPEED;
			if (stageselect.car_y > 730.0f)
			{
				stageselect.car_flag = false;
			}
			break;
		case 2:
			stageselect.car_y -= CAR_SPEED;
			if (stageselect.car_y <-5.0f)
			{
				stageselect.car_flag = false;
			}
			break;
		case 3:
			stageselect.car_y -= CAR_SPEED;
			if (stageselect.car_y < -5.0f)
			{
				stageselect.car_flag = false;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		stageselect.car_fps++;	//fps加算
		if (stageselect.car_fps > 180)		//三秒後
		{
			stageselect.car_num = GetRand(3);	//乱数取得0～3
			switch (stageselect.car_num)
			{
			case 0:
				Set_Coordinate(car->image[3], car->move_image[3], 125.0f, -5.0f);//左上		
				break;
			case 1:
				Set_Coordinate(car->image[3], car->move_image[3], 1142.0f, -5.0f);//右上
				break;
			case 2:
				Set_Coordinate(car->image[2], car->move_image[2], 125.0f, 730.0f);//左下
				break;
			case 3:
				Set_Coordinate(car->image[2], car->move_image[2], 1142.0f, 730.0f);//右下
				break;
			default:
				break;
			}
			stageselect.car_flag = true;	//フラグTRUEに
			stageselect.car_fps = 0;		//fpsリセット
		}
	}
}

//車描画
void Draw_Select_Car(void)
{
	if (stageselect.car_flag == true)
	{
		if (stageselect.move_fps<20)
		{
			DrawRotaGraph(stageselect.car_x, stageselect.car_y, 0.1, 0.0, stageselect.car_image1, TRUE);
			stageselect.move_fps++;
		}
		else
		{
			DrawRotaGraph(stageselect.car_x, stageselect.car_y, 0.1, 0.0, stageselect.car_image2, TRUE);
			stageselect.move_fps++;
			if (stageselect.move_fps > 40)
			{
				stageselect.move_fps = 0;
			}
		}
	}
}

//車の座標代入
void Set_Coordinate(int img1, int img2, float x, float y)
{
	stageselect.car_image1 = img1;//左上
	stageselect.car_image2 = img2;
	stageselect.car_x = x;
	stageselect.car_y = y;
}