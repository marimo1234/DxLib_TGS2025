#include "SceneManager.h"
#include "SceneType.h"

#include "../System/System.h"

#include "Title/TitleScene.h"
#include "InGame/InGameScene.h"
#include "StageSelect/StageSelectScene.h"
#include "Help/HelpScene.h"

eSceneType current_scene_type;
int is_end_flag;

void SceneManagerDraw(void);
void ChangeScene(eSceneType new_scene_type);
void SceneInit(eSceneType new_scene_type);

//シーンマネージャーの初期化
void SceneManagerInitialize(void)
{
	//継続状態にする
	is_end_flag = 0;

	SceneManagerResourceInit();
	//最初のシーンの設定
	ChangeScene(eTitle);
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
	case eHelp:
		next_scene_type = HelpSceneUpdate();
		break;
	case eEnd:
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
	case eHelp:
		HelpSceneDraw();
		break;
	case eEnd:
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
	if (new_scene_type == eEnd)
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
	case eHelp:
		HelpSceneInit();
		break;
	case eEnd:
	default:
		break;
	}
}

//画像、音の読み込み
void SceneManagerResourceInit(void)
{
	InGameResourceInit();
	TitleResourceInit();
}