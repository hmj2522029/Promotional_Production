#pragma once
#include "BattleState.h"
#include "MyLib.h"

class Player;
class Enemy;

class BattleScene : public SceneBase
{
private:

	enum class FadeState
	{
		Fade,		//フェード中
		Run,		//実行中

	};

	
	Node* m_rootNode;
	FadeState m_fadeState;	//フェード状態
	Player* m_player;		//プレイヤー
	Enemy* m_enemy;			//当たった敵

	BattleState* m_state;	//状態


public:

	BattleScene(Player* player) :
		m_rootNode(nullptr),
		m_fadeState(FadeState::Fade),
		m_player(player),
		m_enemy(nullptr),
		m_state(nullptr)
	{
	}
	
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;

};