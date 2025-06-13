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
	load_image = LoadGraph("Resource/images/Loading2.png");
	mole_image = LoadGraph("Resource/images/mole.png");

	//画面の初期化
	ClearDrawScreen();

	DrawRotaGraph(640, 360, 1.0, 0.0, load_image, TRUE);
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph(990+i*50, 360, 1.0, 0.0, mole_image, TRUE);
	}

	ScreenFlip();

	//シーンマネージャーの初期化
	SceneManagerInitialize();

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

