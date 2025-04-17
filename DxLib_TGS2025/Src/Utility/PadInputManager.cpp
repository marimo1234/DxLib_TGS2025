#include"DxLib.h"
#include"PadInputManager.h"

// 静的メンバ変数の初期化
PadInputManager* PadInputManager::instance = nullptr;

// インスタンスを取得
PadInputManager* PadInputManager::GetInstance()
{
	if (instance == nullptr)
	{
		// 最初の1回だけオブジェクトを生成する
		instance = new PadInputManager();
	}

	// 実態を返す
	return instance;
}

// インスタンスの削除
void PadInputManager::DeleteInstance()
{
	if (instance != nullptr)
	{
		// メモリの開放
		delete instance;
		instance = nullptr;
	}
}

void PadInputManager::Update()
{
	// ゲームパッドの情報
	XINPUT_STATE input;

	// ゲームパッドの状態を取得
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	// メモリ領域をコピー
	memcpy(old_button, now_button, (sizeof(char) * PAD_BUTTON_MAX));
	for (int i = 0; i < PAD_BUTTON_MAX; i++)
	{
		// 現在押しているボタンの更新
		now_button[i] = input.Buttons[i];
	}

	// 左トリガーの更新
	left_trigger = (int)input.LeftTrigger;

	// 右トリガーの更新
	right_trigger = (int)input.RightTrigger;
}

// ボタンの入力状態を取得
ePadInputState PadInputManager::GetButtonInputState(int button)
{
	// ボタン入力が有効な範囲だったら処理を行う
	if (CheckButtonRange(button))
	{
		if (old_button[button] == TRUE)
		{
			if (now_button[button] == TRUE)
			{
				// 押し続けている
				return ePadInputState::eHold;
			}
			else
			{
				// 離した瞬間
				return ePadInputState::eRelease;
			}
		}
		else
		{
			if (now_button[button] == TRUE)
			{
				// 押した瞬間
				return ePadInputState::ePress;
			}
			else
			{
				// 未入力
				return ePadInputState::eNone;
			}
		}
	}
	// 未入力
	return ePadInputState::eNone;
}

// 左トリガーの値を取得
int PadInputManager::GetLeftTrigger()const
{
	return left_trigger;
}

// 右トリガーの値を取得
int PadInputManager::GetRightTrigger()const
{
	return right_trigger;
}

// 入力が有効な範囲化チェック
bool PadInputManager::CheckButtonRange(int button)
{
	// 現在の入力値がtrueかfalseか返す
	return (0 <= button && button < PAD_BUTTON_MAX);
}