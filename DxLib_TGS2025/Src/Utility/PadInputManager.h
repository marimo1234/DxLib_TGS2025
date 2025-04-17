#pragma once

#define PAD_BUTTON_MAX (16)            // ゲームパッドのボタンの最大数
#define PAD_STICK_MAX  (32767.0f)      // スティックを傾けたときの最大数

enum class ePadInputState : unsigned char
{
	eNone,        // 未入力
	ePress,       // ボタンを押した瞬間
	eRelease,     // ボタンを押した瞬間
	eHold,        // ボタンを押し続けている
};