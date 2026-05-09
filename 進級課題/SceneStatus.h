#pragma once
#include "MyLib.h"

class Player;

class SceneStatus : public SceneBase
{
private:
	static constexpr float TransitionDuration = 1.0f;	//画面遷移の時間

	Node* m_rootNode;
	Player* m_player;

	int m_largeFontHandle;	//大きいフォントハンドル
	int m_smallFontHandle;	//小さいフォントハンドル


public:

	SceneStatus(Player* player) :
		m_rootNode(nullptr),
		m_player(player),
		m_largeFontHandle(0),
		m_smallFontHandle(0)
	{
	}


	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;


};