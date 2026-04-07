#include "BattleState.h"
#include "BattleCommand.h"
#include "Enemy.h"
#include "Player.h"

BattleState::BattleState(Player* player, Enemy* enemy) :
	m_isBattle(true),
	m_standByTime(WAITING_TIME),
	m_nextSituation(Situation::PlayerTure),	//一旦次の状態をプレイヤーターンにする
	m_situation(Situation::PlayerTure),
	m_battlecommand(),
	m_player(player),
	m_enemy(enemy)
{}

void BattleState::Update()
{
	
	switch (m_situation)
	{
	case Situation::PlayerTure:

		//行動したら敵のターンにする
		if (m_player->isAction())
		{
			//敵が死んだら戦闘終了
			if (m_enemy->m_status.IsDead())
			{
				//次の状態を保存
				m_nextSituation = Situation::EndBattle;

				m_situation = Situation::StandBy;
			}

			//敵の行動をリセット
			m_enemy->ResetAction();

			//次の状態を保存
			m_nextSituation= Situation::EnemyTure;

			m_situation = Situation::StandBy;
		}



		break;

	case Situation::EnemyTure:

		//行動をしたら敵のターンにする
		if (m_enemy->isAction())
		{

			//プレイヤーが死んだら戦闘終了
			if (m_player->m_status.IsDead())
			{
				//次の状態を保存
				m_nextSituation = Situation::EndBattle;

				m_situation = Situation::StandBy;
			}

			//プレイヤーの行動をリセット
			m_player->ResetAction();

			//次の状態を保存
			m_nextSituation = Situation::PlayerTure;

			m_situation = Situation::StandBy;
		}


		//敵の行動をランダムに選ぶ
		static int ActionSelection = GetRand(100);

		if (ActionSelection > 70)	//0から70(70%)
		{
			m_battlecommand->AttackCommand(m_enemy, m_player);
		}
		else if(ActionSelection > 90)	//70から90(20%) 
		{
			m_battlecommand->DefenseCommand(m_enemy);
		}
		else //90から100(10%)
		{
			m_battlecommand->EscapeCommand(m_enemy);
		}


		break;

	case Situation::EndBattle:

		//勝利判定
		if (m_player->m_status.IsDead())	//プレイヤーが死んでいたら敵の勝ち
		{
			


		}
		else if(m_enemy->m_status.IsDead())	//敵が死んだらプレイヤーの勝ち
		{

		}


		m_isBattle = false;

		break;

	case Situation::StandBy:

		m_standByTime -= Time::GetInstance()->GetDeltaTime();

		if (m_standByTime >= 0) return;

		//待機時間をリセットさせる
		ResetTime();

		//次の状態にする
		m_situation = m_nextSituation;
		break;
	}

}


