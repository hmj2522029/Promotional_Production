#include "Keyboard.h"
#include "DxLib.h"
#include <cstring>

char Keyboard::m_KeyCurrentState[Keyboard::AllKeysState] = {};
char Keyboard::m_keyPreviousState[Keyboard::AllKeysState] = {};

void Keyboard::Update()
{
	//コピー
	std::memcpy(
		m_keyPreviousState,			//コピー先
		m_KeyCurrentState,			//コピー元
		sizeof(char) * AllKeysState	//コピーするバイト数
	);

	GetHitKeyStateAll(m_KeyCurrentState);

}

bool Keyboard::isAnyPress()
{
	//検索
	return std::memchr(
		m_KeyCurrentState,			//検索元
		1,							//探す値(押されているやつを探すから1)
		sizeof(char) * AllKeysState	//検索するバイト数
	);
}