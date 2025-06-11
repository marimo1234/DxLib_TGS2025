#include "EndScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

End end;
//ヘルプシーン初期化
void EndSceneInit(void)
{
	end.image= LoadGraph("Resource/Images/EndScene_image.png");
	end.fps = 0;
	
}

//ヘルプシーン更新
eSceneType EndSceneUpdate(void)
{
	end.fps++;
	if (GetKeyInputState(KEY_INPUT_Z) == ePress)
	{
		return eInGame;								//インゲームへ
	}
	if (GetKeyInputState(KEY_INPUT_X) == ePress)
	{
		return eTitle;								//タイトル画面へ
	}

	if (end.fps > 300)
	{
		return eEnd2;
	}

	return eEnd;


}


void EndSceneDraw(void)
{
	DrawRotaGraphF(640.0f, 360.0f, 1.0, 0.0, end.image, TRUE);
	//SetFontSize(40);
	//DrawString(1000, 550, "Z:ゲーム開始\nX:タイトル\n", GetColor(255, 255, 255));			//ゲーム開始とタイトルへの表示
	//SetFontSize(16);
}