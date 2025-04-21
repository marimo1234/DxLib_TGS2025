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

	//シーンマネージャーの初期化
	SceneManagerInitialize();

	// パッド入力制御のインスタンスを取得
	PadInputManager* pad_input = PadInputManager::GetInstance();

	//ローカル変数定義
	float fixed_time = 0.0f;	//フレーム経過時間(s)

	//メインループ
	//ウィンドウが閉じられたorシーンマネージャー側で終了状態でループが終わる
	while (ProcessMessage() != -1 && IsFinish() != TRUE)
	{
		//１フレーム当たりの時間を計算
		CalcFrameTime();
		//１フレーム当たりの時間を加算する
		fixed_time += GetDeltaSecond();

		//６０fpsを疑似再現
		if (fixed_time >= (1.0f / 60.0f))
		{
			fixed_time = 0.0f;	//クリア

			//入力の更新
			InputManagerUpdate();
			pad_input->Update();

			//画面の初期化
			ClearDrawScreen();

			//シーンの更新
			SceneManagerUpdate();

			//裏画面の内容を表画面に反映
			ScreenFlip();

			//エスケープキーが押されるとループ終了
			if (GetKeyInputState(KEY_INPUT_ESCAPE) == eRelease)
			{
				break;
			}
		}
	}

	// パッド入力制御の終了処理
	PadInputManager::DeleteInstance();

	//DxLib終了
	ShutDown();

	return 0;
}

