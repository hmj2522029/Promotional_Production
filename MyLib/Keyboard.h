#pragma once

class Keyboard
{
private:
	static constexpr int AllKeysState = 256;		//全部のキー

	static char m_KeyCurrentState[AllKeysState];	//今のキー状態
	static char m_keyPreviousState[AllKeysState];	//前のキー状態

	Keyboard() {};
public:
	static void Update();

	//押された瞬間
	static bool isDown(int key) { return !m_keyPreviousState[key] && m_KeyCurrentState[key]; }

	//押されている
	static bool isPress(int key) { return m_KeyCurrentState[key]; }

	//離された瞬間
	static bool isUp(int key) { return m_keyPreviousState[key] && !m_KeyCurrentState[key]; }

	//いずれかのキーが押されている
	static bool isAnyPress();

};