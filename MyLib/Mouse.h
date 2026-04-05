#pragma once
#include "Vector2.h"

class Mouse
{
private:
	static Vector2 m_position;		// マウスの現の位置
	static Vector2 m_prevPosition;  // マウスの前の位置
	static int m_wheel;				// マウスホイールの回転量
	static int m_button;			// 現のフレームのマウスボタンの状態
	static int m_prevButton;		// 前のフレームのマウスボタンの状態

	Mouse() {};

public:
	// マウスの状態を更新
	static void Update();

	// マウスの位置を取得
	static Vector2 GetPosition() { return m_position; }

	// マウスの移動量を取得
	static Vector2 GetDelta() { return m_position - m_prevPosition; }

	// マウスホイールの回転量を取得
	static int GetWheel() { return m_wheel; }

	//マウスボタンが押された瞬間
	static bool IsButtonDown(int button) { return (m_button & button) && !(m_prevButton & button); }

	//マウスボタンが離された瞬間
	static bool IsButtonUp(int button) { return !(m_button & button) && (m_prevButton & button); }

	//マウスボタンが押されているか
	static bool IsButtonPressed(int button) { return (m_button & button); }

	//いずれかのマウスボタンが押されているか
	static bool IsAnyButtonPressed() { return m_button; }

};