#include "Button.h"
#include "Mouse.h"
#include "DxLib.h"

Button::Button(const Vector2& size, int mouseButton, std::function<void()> onClick) :
	m_size(size),
	m_mouseButton(mouseButton),
	m_isPressed(false),
	m_onClick(onClick)
{
}

bool Button::IsMouseOver(const Vector2 pos)
{

	Vector2 mousePos = Mouse::GetPosition();

	// ボタンの範囲内にマウスがあるかどうかを判定
	if (pos.x - m_size.x / 2 <= mousePos.x && mousePos.x <= pos.x + m_size.x / 2 &&
		pos.y - m_size.y / 2 <= mousePos.y && mousePos.y <= pos.y + m_size.y / 2)
	{
		return true;
	}
	return false;

}

void Button::Update(const Vector2 pos)
{
	//指定されたボタンを押したときにマウスがボタンの上にあるかどうかを判定
	if (Mouse::IsButtonDown(m_mouseButton))
	{
		m_isPressed = IsMouseOver(pos);
	}

	//指定されたボタンを離したときに、マウスがボタンの上にあるかどうかを判定
	if (Mouse::IsButtonUp(m_mouseButton) && m_isPressed)
	{
		m_isPressed = false;
		if (IsMouseOver(pos))
		{
			m_onClick();
		}
	}


}

void Button::Draw(const Vector2 pos)
{
	// ボタンの枠を描画
	DrawBoxAA(
		pos.x - m_size.x / 2,
		pos.y - m_size.y / 2,
		pos.x + m_size.x / 2,
		pos.y + m_size.y / 2,
		GetColor(0, 0, 255),
		false
	);
}