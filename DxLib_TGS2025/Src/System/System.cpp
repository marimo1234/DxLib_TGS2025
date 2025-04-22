﻿#include "System.h"
#include "ProjectConfig.h"
#include "DxLib.h"

LONGLONG old_time;
LONGLONG now_time;
float delta_second;


int WakeUp(void)
{
	//Log.txtの生成をしない
	SetOutApplicationLogValidFlag(TRUE);
	//ウィンドウモードで起動
	ChangeWindowMode(TRUE);
	//ウィンドウサイズを決める
	SetGraphMode(D_WINDOW_SIZE_X, D_WINDOW_SIZE_Y, D_COLOR_BIT);
	//ウィンドウがアクティブでなくても動く
	SetAlwaysRunFlag(TRUE);
	//Dxライブラリ初期化
	if (DxLib_Init() == -1)
	{
		//以上を通知
		return FALSE;
	}
	//裏画面から描画を始める
	SetDrawScreen(DX_SCREEN_BACK);


	//グローバル変数の初期化
	old_time = 0LL;
	now_time = 0LL;
	delta_second = 0.0f;

	//正常に起動できたことを通知する
	return TRUE;
}


void ShutDown(void)
{
	//Dxライブラリ使用を終了
	DxLib_End();
}