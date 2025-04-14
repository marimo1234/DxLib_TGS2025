#include "DxLib.h"
#include "System/System.h"
#include "Utility/InputManager.h"
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
	//DxLib終了
	ShutDown();

	return 0;
}
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    unsigned int Cr;

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    Cr = GetColor(0, 0, 255);
    int red, blue, green;

    for (int x = 0; x < 640; x += 20) {
        for (int y = 0; y < 480; y += 20) {
            red = GetRand(255);
            blue = GetRand(255);
            green = GetRand(0);
            DrawBoxAA(x, y, x + 18, y + 18, GetColor(red, green, blue), TRUE);

        }
    }


    WaitKey();

    DxLib_End();

    return 0;
}