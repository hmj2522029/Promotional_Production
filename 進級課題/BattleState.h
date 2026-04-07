#pragma once
#include "MyLib.h"

class Player;
class Enemy;
class BattleCommand;


class BattleState : public Node
{
private:
	static constexpr float WAITING_TIME = 2.0f;	//待機時間

	//状態
	enum class Situation
	{
		PlayerTure,	//プレイヤーのターン
		EnemyTure,	//敵のターン
		EndBattle,	//戦闘終了
		StandBy		//待機
	};
	Situation m_nextSituation;	//次の状態

	Situation m_situation;	
	BattleCommand* m_battlecommand;
	Player* m_player;
	Enemy* m_enemy;

	bool m_isBattle;		//戦闘中か	
	float m_standByTime;	//待機時間

protected:

	void Update() override;

public:

	BattleState(Player* player, Enemy* enemy);


	//戦闘中かどうか
	bool isBattel() const { return m_isBattle; }	
	
	//待機時間のリセット
	void ResetTime() { m_standByTime = WAITING_TIME; }

};