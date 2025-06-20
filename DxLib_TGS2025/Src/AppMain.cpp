#include "DxLib.h"
#include "System/System.h"
#include "Utility/InputManager.h"
#include "Utility/PadInputManager.h"
#include "Scene/SceneManager.h"


//メイン関数
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//起動処理
	if (WakeUp() != TRUE)
	{
		//OutputDebugString→Log.txt出力する関数
		OutputDebugString("アプリケーションの初期化に失敗しました\n");
		return -1;
	}

	//アイコンの設定
	SetWindowIconID(123);
	// ウィンドウタイトルを設定
	SetMainWindowText("Go!Go! RoadMaker");
	// マウスカーソル非表示
	SetMouseDispFlag(FALSE);

	int load_image;
	int mole_image;
	int loadbar[3];
	int car_image;
	load_image = LoadGraph("Resource/images/Loading2.png");
	mole_image = LoadGraph("Resource/images/mole.png");
	loadbar[0]= LoadGraph("Resource/images/LoadBar.png");
	loadbar[1]= LoadGraph("Resource/images/LoadBlackBar.png");
	loadbar[2]= LoadGraph("Resource/images/LoadEmptyBar.png");
	car_image= LoadGraph("Resource/images/car2_right.png");
	

	int fps = 0;
	int i = 0;

	while (!IsSceneManagerInitialized())
	{
		fps++;
		ClearDrawScreen();

		// Loadingの描画
		DrawRotaGraph(650, 260, 1.0, 0.0, load_image, TRUE);
		//バーの描画
		DrawRotaGraph(640, 500, 1.0, 0.0, loadbar[0], TRUE);
		DrawRotaGraph(640 + i * 95, 500, 1.0, 0.0, loadbar[1], TRUE);
		DrawRotaGraph(640, 500, 1.0, 0.0, loadbar[2], TRUE);
		//車の描画
		DrawRotaGraph(260 + i * 95, 500, 0.1, 0.0, car_image, TRUE);

		//モグラの描画
		for (int j = 0; j < 3; j++)
		{
			DrawRotaGraph(1000 + j * 50, 260, 1.0, 0.0, mole_image, TRUE);
		}
		if (fps < 9)
		{
			i++;
		}
		// ここで1つずつ初期化を進める（リソース系含む）
		SceneManagerInitialize();
		DrawFormatString(100, 100, GetColor(255, 255, 255), "%d", fps);
		ScreenFlip();
	}

	

	// パッド入力制御のインスタンスを取得
	PadInputManager* pad_input = PadInputManager::GetInstance();

	int frameCount = 0;
	int fpsTimer = GetNowCount();
	int currentFPS = 0;
	const int FRAME_TIME = 1000 / 60;
	int startTime, deltaTime;

	//メインループ
	//ウィンドウが閉じられたorシーンマネージャー側で終了状態でループが終わる
	while (ProcessMessage() != -1 && IsFinish() != TRUE)
	{
		// フレーム開始時刻を記録
		startTime = GetNowCount();

		//入力の更新
		InputManagerUpdate();
		pad_input->Update();

		//画面の初期化
		ClearDrawScreen();

		//シーンの更新
		SceneManagerUpdate();

		frameCount++;
		int now = GetNowCount();
		if (now - fpsTimer >= 1000)
		{
			currentFPS = frameCount;
			frameCount = 0;
			fpsTimer = now;
		}

		//裏画面の内容を表画面に反映
		ScreenFlip();

		//エスケープキーが押されるとループ終了
		if (GetKeyInputState(KEY_INPUT_ESCAPE) == eRelease)
		{
			break;
		}

		deltaTime = GetNowCount() - startTime;
		if (deltaTime < FRAME_TIME)
		{
			WaitTimer(FRAME_TIME - deltaTime);
		}
	}

	// パッド入力制御の終了処理
	PadInputManager::DeleteInstance();

	//DxLib終了
	ShutDown();

	return 0;
}

