#pragma once
#include "Vector2.h"
#include <functional>

class Button
{
private:
	Vector2 m_size;						// ボタンのサイズ
	int m_mouseButton;					// クリックに使用するマウスボタン
	bool m_isPressed;					// ボタンが押されているかどうか
	std::function<void()> m_onClick;	// クリックされたときの処理(呼ばれる関数(void))

	bool IsMouseOver(const Vector2 pos);			// マウスがボタンの上にあるかどうかを判定する関数

public:

	Button(const Vector2& size, int mouseButton, std::function<void()> onClick);

	void Update(const Vector2 pos);
	void Draw(const Vector2 pos);

};