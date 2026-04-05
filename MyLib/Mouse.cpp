#include "Mouse.h"
#include "DxLib.h"


Vector2 Mouse::m_position = Vector2(0, 0);
Vector2 Mouse::m_prevPosition = Vector2(0, 0);
int Mouse::m_wheel = 0;
int Mouse::m_button = 0;
int Mouse::m_prevButton = 0;

void Mouse::Update()
{
	// 前回のマウスボタンを保存
	m_prevButton = m_button;

	// 現在のマウスボタンを取得
	m_button = GetMouseInput();

	// 前回のマウス位置を保存
	m_prevPosition = m_position;

	// 現在のマウス位置を取得
	int x, y;
	GetMousePoint(&x, &y);
	m_position = Vector2(x, y);

	// マウスホイールの状態を取得
	m_wheel = GetMouseWheelRotVol();
}