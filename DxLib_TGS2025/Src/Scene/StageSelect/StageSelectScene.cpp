#include "StageSelectScene.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/PadInputManager.h"
#include"../InGame/InGameScene.h"
#include"../Title/TitleScene.h"
#include"../../Object/car.h"
#include"../../../Effect/Fade.h"
#include "DxLib.h"
#include <stdlib.h>


//車のスピード
#define CAR_SPEED		(1.5f)

//星のポジション
#define STAR_POS_X (580)
#define STAR_POS_Y (508)

//枠、数字の固定座標
#define SELECT_TROUT_X (390.0)
#define SELECT_TROUT_Y (350.0)
//ステージ番号が動くときの枚フレームの変化量
#define NUM_MOVE_VALUE (12.0)
//ステージ番号が動く範囲
#define SS_NUM_Y_MIN (242.0)
#define SS_NUM_Y_MAX (458.0)


//マップの固定座標
#define SELECT_MAP_X (760.0)
#define SELECT_MAP_Y (350.0)
//ステージ番号が動くときの枚フレームの変化量
#define MAP_MOVE_VALUE (26.4)
//マップが動く範囲
#define SS_MAP_Y_MIN (112.0)
#define SS_MAP_Y_MAX (588.0)


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
//ステージ番号ムーブフラグ
void SS_NumberFlag(bool &flag);
//ステージ番号のムーブ
void SS_NumberMove(void);
//ミニマップのムーブ
void SS_MapMove(void);
//スピードCARのアニメーション
void SS_SpcarAnim(void);


StageSelect stg_sel;
SS_Star ss_star;
SS_Num ss_num;
SS_Map ss_map;
SS_SpeedCar ss_spcar;

//ステージセレクト画面初期化
void StageSelectSceneInit(void)
{

	//fps
	stg_sel.car_fps = 0;
	stg_sel.move_fps = 0;

	//ポジションの初期化
	stg_sel.position.x = 400.0f;
	stg_sel.position.y = 255.0f;
	//ステージ番号の初期化
	ss_num.stg_num = 0;

	//車の描画座標
	stg_sel.car_x = 0.0f;
	stg_sel.car_y = 0.0f;
	stg_sel.car_image1 = 0;
	stg_sel.car_image2 = 0;
	stg_sel.car_num = 0;
	stg_sel.car_flag = false;

	stg_sel.flag = true;

	//スターの変数を初期化
	ss_star.num = 0;
	ss_star.cnt = 0;
	ss_star.idx = 0;

	//番号の初期化
	ss_num.x = SELECT_TROUT_X;
	ss_num.y = SELECT_TROUT_Y;
	ss_num.u_flag = false;
	ss_num.d_flag = false;
	ss_num.stg_num = 0;

	//ミニマップの初期化
	ss_map.x = SELECT_MAP_X;
	ss_map.y = SELECT_MAP_Y;

	//スピードCARの初期化
	ss_spcar.anim = ss_spcar.img[0];
	ss_spcar.sw_cnt = 30;
	ss_spcar.idx = 0;

	for (int i = 0; i < 5; i++)
	{
		ss_star.x[i] = STAR_POS_X + i * 35;
		ss_star.y[i] = STAR_POS_Y;
	}


	fade.Initialize(true);
	is_fading = true;



	Play_StageSelect_BGM(GetTitle());
}

void StageSelectResourceInit(void)
{
	switch (stageselect_init_step)
	{
	case 2:
		stg_sel.b_back = LoadGraph("Resource/images/Bback3.png");
		//カーソルとボタンのSE
		stg_sel.cursor_se = LoadSoundMem("Resource/Sounds/stage_select_cursor.mp3");
		stg_sel.button_se = LoadSoundMem("Resource/Sounds/stageselect_button.mp3");

		stg_sel.car_up_img[0] = LoadGraph("Resource/images/car2_up.png");
		stg_sel.car_up_img[1] = LoadGraph("Resource/images/car2_up2.png");
		stg_sel.car_down_img[0] = LoadGraph("Resource/images/car2_down.png");
		stg_sel.car_down_img[1] = LoadGraph("Resource/images/car2_down2.png");
		break;
	case 6:
		//画像の取得
	//背景
		stg_sel.background_image = LoadGraph("Resource/images/StageSelect3.png");
		// スピードの画像
		stg_sel.speed_frame = LoadGraph("Resource/images/Speedframe2.png");
		//スピードの文字画像
		stg_sel.speed_char = LoadGraph("Resource/images/SpeedCharImage.png");
		//スピードCARの画像
		ss_spcar.img[0]= LoadGraph("Resource/images/car2_right.png");
		ss_spcar.img[1]= LoadGraph("Resource/images/car2_right2.png");
		ss_spcar.img[2]= LoadGraph("Resource/images/car2_right3.png");
		ss_spcar.img[3]= LoadGraph("Resource/images/car2_right4.png");

		//マスの画像
		stg_sel.trout_image[0] = LoadGraph("Resource/images/StageTrout.png");
		stg_sel.trout_image[1] = LoadGraph("Resource/images/StageTrout2.png");
		stg_sel.trout_image[2] = LoadGraph("Resource/images/BackTrout2.png");
		stg_sel.trout_image[3] = LoadGraph("Resource/images/StageTrout1.png");
		stg_sel.trout_image[4] = LoadGraph("Resource/images/StageTrout3.png");

		//数字の画像
		LoadDivGraph("Resource/images/StageSelect_Num.png", 6, 6, 1, 220, 270, ss_num.img);

		//数字を隠す背景画像
		ss_num.hide_img= LoadGraph("Resource/images/bg_hide_num02.png");

		//ステージの画像
		ss_map.img[0] = LoadGraph("Resource/images/stage01.png");
		ss_map.img[1] = LoadGraph("Resource/images/stage02.png");
		ss_map.img[2] = LoadGraph("Resource/images/stage03.png");
		ss_map.img[3] = LoadGraph("Resource/images/stage04.png");
		ss_map.img[4] = LoadGraph("Resource/images/stage05.png");
		ss_map.img[5] = LoadGraph("Resource/images/stage06.png");
		ss_map.hide_img = LoadGraph("Resource/images/bg_hide_map.png");

		stg_sel.arrow_image[0] = LoadGraph("Resource/images/StageSelect_button.png");
		stg_sel.arrow_image[1] = LoadGraph("Resource/images/StageSelect_button2.png");

		//ミニマップの画像
		stg_sel.back_minimap = LoadGraph("Resource/images/BG_MiniMap2.png");
		

		//　星の画像
		ss_star.img[0] = LoadGraph("Resource/images/ss_star0.png");
		ss_star.img[1] = LoadGraph("Resource/images/ss_star1.png");

		break;
	default:
		break;
	}
	stageselect_init_step++;
}

//ステージセレクトシーンの更新
eSceneType StageSelectSceneUpdate(void)
{	
	//車のムーブ更新
	Move_Car(GetCar());

	//スピードスタームーブ
	StarMove();

	//ステージ番号のムーブ
	SS_NumberMove();

	//ミニマップのムーブ
	SS_MapMove();
	
	//スピードCARのアニメーション
	SS_SpcarAnim();

	//フェード処理
	if (is_fading)
	{
		fade.Update();
		if (fade.GetEndFlag())
		{
			is_fading = false;
		}
		return eStageSelect;
	}

	PadInputManager* pad_input = PadInputManager::GetInstance();

	//Aボタンが押されたとき
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_A) == ePadInputState::ePress &&
		ss_num.d_flag == false && ss_num.u_flag == false)
	{
		//ステージ番号が-1じゃなければ
		if (ss_num.stg_num != -1)
		{
			stg_sel.flag = false;
			Stop_Title_BGM(GetTitle());
			Play_Sound_StageSelect(stg_sel.button_se, 80);
			StageSelectNumber();
			return eInGame;	//インゲーム画面へ
		}
	}
	if (pad_input->GetButtonInputState(XINPUT_BUTTON_B) == ePadInputState::ePress)
	{
		Play_Sound_StageSelect(stg_sel.button_se, 80);
		return eTitle;
	}

	if (stg_sel.flag == true)
	{
		//ステージセレクト画面の車のムーブ
		StageSelectCursorMove();
	}
	return eStageSelect;
}

//ステージセレクトシーンの描画
void StageSelectSceneDraw(void)
{
	//背景の描画
	DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, stg_sel.background_image, TRUE);

	DrawRotaGraphF(635.0f, 420.0f, 0.78, 0.0, stg_sel.back_minimap, TRUE);
	
	//数字、枠の描画
	NumTroutDraw();

	//車描画
	Draw_Select_Car();

	//Bで戻る画像の描画
	DrawRotaGraphF(1170.0, 670.0, 0.8, 0.0, stg_sel.b_back, TRUE);

	fade.Draw();

	//DrawFormatString(300, 300, GetColor(255, 0, 255), "%f\n%f\n%d\n%d\n", stg_sel.car_x,stg_sel.car_y, stg_sel.car_flag, stg_sel.move_fps);
}

//StageSelectを取得
const StageSelect* GetStageSelect(void)
{
	return &stg_sel;
}

//SS_Numを取得
const SS_Num* GetSS_Num(void)
{
	return &ss_num;
}

//ステージセレクト画面のカーソルのムーブ
void StageSelectCursorMove(void)
{

	PadInputManager* pad_input = PadInputManager::GetInstance();


	if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_UP) == ePadInputState::ePress)
	{
		if (ss_num.stg_num > 0)
		{
			//星の元の位置に戻す（空の星が跳ねたままになることを防ぐ）
			for (int i = 0; i < 5; i++)
			{
				ss_star.y[i] = STAR_POS_Y;
			}

			//星のインデックスとカウントを初期化
			ss_star.idx = 0;
			ss_star.cnt = 0;

			//Down中じゃなかったら
			if (ss_num.d_flag == false)
			{
				//Upフラグをtrueに
				SS_NumberFlag(ss_num.u_flag);
			}

			// 移動のSE（左とおんなじ音入れてね）
			Play_Sound_StageSelect_NC(stg_sel.cursor_se, 80);
		}
	}
	else if (pad_input->GetButtonInputState(XINPUT_BUTTON_DPAD_DOWN) == ePadInputState::ePress)
	{
		if (ss_num.stg_num < 5)
		{
			//星の元の位置に戻す（空の星が跳ねたままになることを防ぐ）
			for (int i = 0; i < 5; i++)
			{
				ss_star.y[i] = STAR_POS_Y;
			}

			//星のインデックスとカウントを初期化
			ss_star.idx = 0;
			ss_star.cnt = 0;

			//Up中じゃなかったら
			if (ss_num.u_flag == false)
			{
				//Downフラグをtrueに
				SS_NumberFlag(ss_num.d_flag);
			}

			// 移動のSE（左とおんなじ音)入れてね）
			Play_Sound_StageSelect_NC(stg_sel.cursor_se, 80);
		}
	}
}

//ステージ番号の分岐
void StageSelectNumber(void)
{
	switch (ss_num.stg_num)
	{
	case 0:
		ss_num.stg_num = eOne;
		break;
	case 1:
		ss_num.stg_num = eTwo;
		break;
	case 2:
		ss_num.stg_num = eThree;
		break;
	case 3:
		ss_num.stg_num = eFour;
		break;
	case 4:
		ss_num.stg_num = eFive;
		break;
	case 5:
		ss_num.stg_num = eSix;
		break;
	}
}

//数字、枠、車の描画
void NumTroutDraw(void)
{	
	//現在のステージの一つ前のステージ番号
	int pre_map = ss_num.stg_num - 1;
	//ミニマップの描画
	//一つ前のミニマップ
	if (ss_num.d_flag == false)
	{
		DrawRotaGraphF(ss_map.x, ss_map.y - 238.0f, 0.33, 0.0, ss_map.img[pre_map], TRUE);
	}
	//一つ後のミニマップ
	else if (ss_num.u_flag == false)
	{
		DrawRotaGraphF(ss_map.x, ss_map.y + 238.0f, 0.33, 0.0, ss_map.img[ss_num.stg_num + 1], TRUE);
	}
	DrawRotaGraphF(ss_map.x, ss_map.y, 0.33, 0.0, ss_map.img[ss_num.stg_num], TRUE);
	//ミニマップを隠す背景の描画（ミニマップの部分だけくりぬいてる）
	DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, ss_map.hide_img, TRUE);
	//ミニマップの枠の描画
	DrawRotaGraphF(SELECT_MAP_X, SELECT_MAP_Y, 0.33, 0.0, stg_sel.trout_image[4], TRUE);
	

	//現在のステージの一つ前のステージ番号
	int pre_num = ss_num.stg_num - 1;

	//数字の描画
	//一つ前のステージ番号
	if (ss_num.d_flag == false)
	{
		DrawRotaGraphF(ss_num.x, ss_num.y - 108.0f, 0.4, 0.0, ss_num.img[pre_num], TRUE);
	}
	//一つ後のステージ番号
	else if (ss_num.u_flag == false)
	{
		DrawRotaGraphF(ss_num.x, ss_num.y + 108.0f, 0.4, 0.0, ss_num.img[ss_num.stg_num + 1], TRUE);
	}
	//現在のステージ番号
	DrawRotaGraphF(ss_num.x, ss_num.y, 0.4, 0.0, ss_num.img[ss_num.stg_num], TRUE);

	//数字を隠す背景の描画（数字の部分だけくりぬいてる）
	DrawRotaGraphF(SELECT_TROUT_X, SELECT_TROUT_Y, 1.0, 0.0, ss_num.hide_img, TRUE);


	//数字枠の描画
	DrawRotaGraphF(SELECT_TROUT_X, SELECT_TROUT_Y, 0.25, 0.0, stg_sel.trout_image[3], TRUE);
	//矢印の描画（上または下にない時は描画しない）
	if (ss_num.stg_num != 0)
	{
		DrawRotaGraph(SELECT_TROUT_X, 250.0, 0.9, 0.0, stg_sel.arrow_image[0], TRUE);
	}
	if (ss_num.stg_num != 5)
	{
		DrawRotaGraph(SELECT_TROUT_X, 450.0, 0.9, 0.0, stg_sel.arrow_image[1], TRUE);
	}

	//スピード枠の描画
	DrawRotaGraph(630, 550, 0.7, 0.0, stg_sel.speed_frame, TRUE);

	//スピードの文字描画
	DrawRotaGraph(470, 508, 0.5, 0.0, stg_sel.speed_char, TRUE);

	//スピードCARの描画
	DrawRotaGraph(355, 508, 0.06, 0.0, ss_spcar.anim, TRUE);

	//スピードスターの描画
	DrawStar();

	//ステージの概要コメント
	switch (ss_num.stg_num)
	{
	case 0:

		DrawExtendFormatString(325, 540, 1.4, 1.5, GetColor(0, 0, 0), "チュートリアルステージ ");
		DrawExtendFormatString(325, 575, 1.4, 1.5, GetColor(0, 0, 0), "はじめてはこのステージからやろう！ ");
		break;
	case 1:
		DrawExtendFormatString(325, 540, 1.4, 1.5, GetColor(0, 0, 0), "初心者向けステージ ");
		DrawExtendFormatString(325, 575, 1.4, 1.5, GetColor(0, 0, 0), "チュートリアルステージの次はこのステージをやろう！ ");
		break;
	case 2:
		DrawExtendFormatString(325, 540, 1.4, 1.5, GetColor(0, 0, 0), "資材集めのステージ ");
		DrawExtendFormatString(325, 575, 1.4, 1.5, GetColor(0, 0, 0), "車に追いつかれないように気を付けて資材を集めよう！ ");
		break;
	case 3:
		DrawExtendFormatString(325, 540, 1.4, 1.5, GetColor(0, 0, 0), "水陸交互のステージ ");
		DrawExtendFormatString(325, 575, 1.4, 1.5, GetColor(0, 0, 0), "作る道の切り替えが重要！混乱しないで道を繋げよう！ ");
		break;
	case 4:
		DrawExtendFormatString(325, 540, 1.4, 1.5, GetColor(0, 0, 0), "水辺のステージ ");
		DrawExtendFormatString(325, 575, 1.4, 1.5, GetColor(0, 0, 0), "車が早くなってるからミスをしないよう気を付けよう！ ");
		break;
	case 5:
		DrawExtendFormatString(325, 540, 1.4, 1.5, GetColor(0, 0, 0), "最難関ステージ ");
		DrawExtendFormatString(325, 575, 1.4, 1.5, GetColor(0, 0, 0), "車が最速で走るから、道繋ぎと資材集めを交互にやろう！ ");
		break;
	}
	//DrawFormatString(100, 50, GetColor(255, 255, 255), "%d %d \n %f %f", ss_num.d_flag, ss_num.u_flag,ss_num.x,ss_num.y);
}

//スピードスタームーブ
void StarMove(void)
{
	//アニメーションカウント
	ss_star.cnt++;

	//インデックス以外の星を元の位置に戻す(一つずつ元の位置に戻るように）
	for (int i = 0; i < 5; i++)
	{
		if (i != ss_star.idx && ss_star.y[i] < STAR_POS_Y)
		{
			ss_star.y[i] += 3;
		}
	}

	//UpフラグとDownフラグがfalseの時（ss_star.yの-値が残らないように）
	if (ss_num.u_flag == false && ss_num.d_flag == false)
	{
		//インデックスが星の数を越えていなければ
		if (ss_star.idx < 5)
		{
			//余りが0の時、横の星にうつる
			if (ss_star.cnt % 5 == 0)
			{
				ss_star.idx++;
			}

			//余りが0以外の時
			if (ss_star.cnt % 5 > 0)
			{
				//上に跳ねる
				ss_star.y[ss_star.idx] -= 3;
			}
		}
	}

	//200フレーム経った後にリセット
	if (ss_star.cnt > 150)
	{
		ss_star.cnt = 0;
		ss_star.idx = 0;
	}


	//ステージごとの色付きの星の数
	switch (ss_num.stg_num)
	{
	case 0:
		ss_star.num = 1;
		break;
	case 1: case 2:
		ss_star.num = 2;
		break;
	case 3: case 4:
		ss_star.num = 3;
		break;
	case 5:
		ss_star.num = 4;
		break;
	}
}

//スピードスターの描画
void DrawStar(void)
{
	//空のスターの描画
	for (int i = 0; i < 5; i++)
	{
		DrawRotaGraph(ss_star.x[i], ss_star.y[i], 0.35, 0.0, ss_star.img[0], TRUE);
	}
	//色付きスターの描画
	for (int i = 0; i < ss_star.num; i++)
	{
		DrawRotaGraph(ss_star.x[i], ss_star.y[i], 0.35, 0.0, ss_star.img[1], TRUE);
	}
}

//ステージ番号ムーブフラグ
void SS_NumberFlag(bool &flag)
{
	flag = true;
}

//ステージ番号ムーブ
void SS_NumberMove(void)
{
	//上キーを押したとき数字を一つ減らして上方向にスライドする
	if (ss_num.u_flag == true && ss_num.y < SS_NUM_Y_MAX)
	{
		ss_num.y += NUM_MOVE_VALUE;
	}
	//下キーを押したとき数字を一つ増やして下方向にスライドする
	else if (ss_num.d_flag == true&& ss_num.y > SS_NUM_Y_MIN)
	{
		ss_num.y -= NUM_MOVE_VALUE;
	}
	//ボタンが押されていない時フラグをfalseにして座標を元に戻す
	else
	{
		ss_num.d_flag = false;
		ss_num.u_flag = false;
		//数字が増えたらStageNumber変数もインクリメントする
		if (ss_num.y <= SS_NUM_Y_MIN)
		{
			ss_num.stg_num++;
		}
		//数字が減ったらStageNumber変数もデクリメントする
		if (ss_num.y >= SS_NUM_Y_MAX)
		{
			ss_num.stg_num--;
		}
		ss_num.y = SELECT_TROUT_Y;
		
	}

}

//ミニマップムーブ
void SS_MapMove(void)
{
	//上キーを押したとき数字を一つ減らして上方向にスライドする
	if (ss_num.u_flag == true && ss_map.y < SS_MAP_Y_MAX)
	{
		ss_map.y += MAP_MOVE_VALUE;
	}
	//下キーを押したとき数字を一つ増やして下方向にスライドする
	else if (ss_num.d_flag == true && ss_map.y > SS_MAP_Y_MIN)
	{
		ss_map.y -= MAP_MOVE_VALUE;
	}
	//ボタンが押されていない時フラグをfalseにして座標を元に戻す
	else
	{
		ss_map.y = SELECT_MAP_Y;
	}

}

//スピードCARのアニメーション
void SS_SpcarAnim(void)
{
	ss_spcar.cnt++;
	
	//スピードCARの画像切り替え
	ss_spcar.anim = ss_spcar.img[ss_spcar.idx];

	//カウントが0じゃなければsw_cnt(sw → switch)経つたびに画像を切り替える
	if (ss_spcar.cnt != 0 && ss_spcar.cnt % ss_spcar.sw_cnt == 0 
		&& ss_spcar.idx < 4)
	{
		ss_spcar.idx++;
	}

	//画像が4枚だから sw_cnt*4 をMAXにする
	int cnt_max = ss_spcar.sw_cnt * 4;

	if (ss_spcar.cnt > cnt_max)
	{
		ss_spcar.idx = 0;
		ss_spcar.cnt = 0;
	}
	
	//ステージごとのアニメーション速度の変化
	switch (ss_num.stg_num)
	{
	case 0:
		ss_spcar.sw_cnt = 20;
		break;
	case 1: case 2:
		ss_spcar.sw_cnt = 15;
		break;
	case 3: case 4:
		ss_spcar.sw_cnt = 10;
		break;
	case 5:
		ss_spcar.sw_cnt = 5;
		break;
	}
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
	if (stg_sel.car_flag == true)
	{
		switch (stg_sel.car_num)
		{
		case 0:
			stg_sel.car_y += CAR_SPEED;
			if (stg_sel.car_y > 730.0f)
			{
				stg_sel.car_flag = false;
			}
			break;
		case 1:
			stg_sel.car_y += CAR_SPEED;
			if (stg_sel.car_y > 730.0f)
			{
				stg_sel.car_flag = false;
			}
			break;
		case 2:
			stg_sel.car_y -= CAR_SPEED;
			if (stg_sel.car_y <-5.0f)
			{
				stg_sel.car_flag = false;
			}
			break;
		case 3:
			stg_sel.car_y -= CAR_SPEED;
			if (stg_sel.car_y < -5.0f)
			{
				stg_sel.car_flag = false;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		stg_sel.car_fps++;	//fps加算
		if (stg_sel.car_fps > 180)		//三秒後
		{
			stg_sel.car_num = GetRand(3);	//乱数取得0～3
			switch (stg_sel.car_num)
			{
			case 0:
				Set_Coordinate(stg_sel.car_down_img[0], stg_sel.car_down_img[1], 125.0f, -5.0f);//左上		
				break;
			case 1:
				Set_Coordinate(stg_sel.car_down_img[0], stg_sel.car_down_img[1], 1142.0f, -5.0f);//右上
				break;
			case 2:
				Set_Coordinate(stg_sel.car_up_img[0], stg_sel.car_up_img[1], 125.0f, 730.0f);//左下
				break;
			case 3:
				Set_Coordinate(stg_sel.car_up_img[0], stg_sel.car_up_img[1], 1142.0f, 730.0f);//右下
				break;
			default:
				break;
			}
			stg_sel.car_flag = true;	//フラグTRUEに
			stg_sel.car_fps = 0;		//fpsリセット
		}
	}
}

//車描画
void Draw_Select_Car(void)
{
	if (stg_sel.car_flag == true)
	{
		if (stg_sel.move_fps<20)
		{
			DrawRotaGraph(stg_sel.car_x, stg_sel.car_y, 0.1, 0.0, stg_sel.car_image1, TRUE);
			stg_sel.move_fps++;
		}
		else
		{
			DrawRotaGraph(stg_sel.car_x, stg_sel.car_y, 0.1, 0.0, stg_sel.car_image2, TRUE);
			stg_sel.move_fps++;
			if (stg_sel.move_fps > 40)
			{
				stg_sel.move_fps = 0;
			}
		}
	}
}

//車の座標代入
void Set_Coordinate(int img1, int img2, float x, float y)
{
	stg_sel.car_image1 = img1;//左上
	stg_sel.car_image2 = img2;
	stg_sel.car_x = x;
	stg_sel.car_y = y;
}