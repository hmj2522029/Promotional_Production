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

			//プレイヤーが逃げれた戦闘終了
			if (m_player->isRanAway())
			{
				//次の状態を保存
				m_nextSituation = Situation::EndBattle;

				//待機させる
				m_situation = Situation::StandBy;

				break;
			}

			//敵が死んだら戦闘終了
			if (m_enemy->m_status.IsDead())
			{
				//次の状態を保存
				m_nextSituation = Situation::EndBattle;

				//待機させる
				m_situation = Situation::StandBy;


				break;
			}

			//敵の行動をリセット
			m_enemy->ResetAction();

			//もし敵が防御していたら防御を解除する
			if (m_enemy->m_status.IsDefending())
			{
				m_enemy->m_status.EndDefend();
			}

			//次の状態を保存
			m_nextSituation= Situation::EnemyTure;

			//待機させる
			m_situation = Situation::StandBy;
		}



		break;

	case Situation::EnemyTure:

		//行動をしたら敵のターンにする
		if (m_enemy->isAction())
		{

			//敵か逃げるたら戦闘終了
			if (m_enemy->isRanAway())
			{
				//次の状態を保存
				m_nextSituation = Situation::EndBattle;

				//待機させる
				m_situation = Situation::StandBy;

				break;

			}


			//プレイヤーが死んだら戦闘終了
			if (m_player->m_status.IsDead())
			{

				//次の状態を保存
				m_nextSituation = Situation::EndBattle;

				//待機させる
				m_situation = Situation::StandBy;

				break;
			}

			//プレイヤーの行動をリセット
			m_player->ResetAction();

			//もしプレイヤーが防御していたら防御を解除する
			if (m_player->m_status.IsDefending())
			{
				m_player->m_status.EndDefend();
			}

			//次の状態を保存
			m_nextSituation = Situation::PlayerTure;

			//待機させる
			m_situation = Situation::StandBy;
		}


		//敵が行動していなかったら
		if (!m_enemy->isAction())
		{
			//敵の行動をランダムに選ぶ
			int ActionSelection = GetRand(100);

			if (ActionSelection < 70)	//0から70(70%)
			{
				m_battlecommand.AttackCommand(m_enemy, m_player);

				m_player->PlayDamageSE();	//ダメージSEを再生

			}
			else if(ActionSelection < 90)	//70から90(20%) 
			{
				m_battlecommand.DefenseCommand(m_enemy);

				m_enemy->PlayDefenseSE();	//防御SEを再生

			}
			else //90から100(10%)
			{
				m_battlecommand.EscapeCommand(m_enemy);

				m_enemy->PlayEscapeSE();	//逃走SEを再生

			}

		}


		break;

	case Situation::EndBattle:

		//逃げるリセット
		m_player->ResetRanAway();

		//プレイヤーの行動をリセット
		m_player->ResetAction();


		//シーンの切り替えはBattleSceneで行う
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


