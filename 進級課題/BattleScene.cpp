#include "BattleScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "SceneGame.h"

void BattleScene::Initialize()
{
	//カメラを止める
	m_camera->Stop();

	// 戦闘開始のログを表示
	Debug::Log("Battle Start! Player HP: %d, Enemy HP: %d\n", m_player->m_status.GetHp(), m_enemy->m_status.GetHp());
}

void BattleScene::Finalize()
{
	// 戦闘終了のログを表示
	Debug::Log("Battle End! Player HP: %d, Enemy HP: %d\n", m_player->m_status.GetHp(), m_enemy->m_status.GetHp());
}

void BattleScene::Update()
{

	if (m_player->m_status.IsDead()|| m_enemy->m_status.IsDead())
	{
		//カメラを動かす
		m_camera->Move();

		SceneManager::GetInstance()->PopScene();
		Physics2D::GetInstance()->Active();
	}
}

void BattleScene::Draw()
{
	// 戦闘中のログを表示
	Debug::Log("Battle Update! Player HP: %d, Enemy HP: %d\n", m_player->m_status.GetHp(), m_enemy->m_status.GetHp());
}