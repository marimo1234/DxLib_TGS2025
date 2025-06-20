#include "SceneManager.h"
#include "SceneType.h"
#include "DxLib.h"

#include "../System/System.h"

#include "Title/TitleScene.h"
#include "InGame/InGameScene.h"
#include "StageSelect/StageSelectScene.h"
#include "End/EndScene.h"
#include "Credits/CreditsScene.h"

eSceneType current_scene_type;
int is_end_flag;
static int init_flag = false;

void SceneManagerDraw(void);
void ChangeScene(eSceneType new_scene_type);
void SceneInit(eSceneType new_scene_type);



//シーンマネージャーの初期化
void SceneManagerInitialize(void)
{
	//継続状態にする
	is_end_flag = 0;

	InGameResourceInit();
	TitleResourceInit();
	StageSelectResourceInit();

	if (IsInGameInit() == true)
	{
		//最初のシーンの設定
		ChangeScene(eTitle);
		init_flag = true;
	}
}

bool IsSceneManagerInitialized()
{
	return init_flag;
}

void SceneManagerUpdate(void)
{
	//次のシーン情報を格納する変数
	eSceneType next_scene_type = eEnd;

	//シーンの更新
	switch (current_scene_type)
	{
	case eTitle:
		next_scene_type = TitleSceneUpdate();
		break;
	case eStageSelect:
		next_scene_type = StageSelectSceneUpdate();
		break;
	case eInGame:
		next_scene_type = InGameSceneUpdate();
		break;
	case eEnd:
		next_scene_type = EndSceneUpdate();
		break;
	case eCredits:
		next_scene_type = CreditsSceneUpdate();
		break;
	case eEnd2:
	default:
		break;
	}

	//シーンの描画
	SceneManagerDraw();

	//現在のシーンのタイプと次のシーンのタイプを比べる
	if (current_scene_type != next_scene_type)
	{
		//違っていたら、シーン切り替えを行う
		ChangeScene(next_scene_type);
	}
}

int IsFinish(void)
{
	return is_end_flag;
}

void SceneManagerDraw(void)
{
	switch (current_scene_type)
	{
	case eTitle:
		TitleSceneDraw();
		break;
	case eStageSelect:
		StageSelectSceneDraw();
		break;
	case eInGame:
		InGameSceneDraw();
		break;
	case eEnd:
		EndSceneDraw();
		break;
	case eCredits:
		CreditsSceneDraw();
	case eEnd2:
	default:
		break;
	}
}


void ChangeScene(eSceneType new_scene_type)
{
	//１度だけ実行してほしい内容
	static int is_once = 1;
	if (is_once == 1)
	{
		is_once = 0;
		SceneInit(new_scene_type);
		return;
	}
	//～１度だけ実行してほしい内容


	//２回目以降の呼び出し時↓

	//エンド画面が呼び出されたらループ終了
	if (new_scene_type == eEnd2)
	{
		is_end_flag = 1;
		return;
	}

	//各シーンの初期化
	SceneInit(new_scene_type);

	//現在のシーンタイプの変更
	current_scene_type = new_scene_type;
}

//各シーンの初期化処理
void SceneInit(eSceneType new_scene_type)
{
	switch (new_scene_type)
	{
	case eTitle:
		TitleSceneInit();
		break;
	case eStageSelect:
		StageSelectSceneInit();
		break;
	case eInGame:
		InGameSceneInit();
		break;
	case eEnd:
		EndSceneInit();
		break;
	case eCredits:
		CreditsSceneInit();
		break;
	case eEnd2:
	default:
		break;
	}
}


