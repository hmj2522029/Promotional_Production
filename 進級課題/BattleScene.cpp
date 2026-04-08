#include "BattleScene.h"
#include "SceneGame.h"
#include "Player.h"
#include "Enemy.h"

void BattleScene::Initialize()
{

	m_rootNode = new Node;

	m_state = new BattleState(m_player, m_enemy);
	m_rootNode->AddChild(m_state);



}

void BattleScene::Finalize()
{

	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		delete m_rootNode;
		m_rootNode = nullptr;
	}


}

void BattleScene::Update()
{
	switch (m_fadeState)
	{
	case FadeState::Fade:
		if(ScreenFade::GetInstance()->IsFade())return;	

		//当たった敵の取得
		m_enemy = m_player->GetTargetEnemy();

		ScreenFade::GetInstance()->StartFadeIn(true);
		m_fadeState = FadeState::Run;
		break;

	case FadeState::Run:

		if (m_player->m_status.IsDead()|| m_enemy->m_status.IsDead())
		{

			ScreenFade::GetInstance()->StartFadeOut(true, 0.2);

			Physics2D::GetInstance()->Active();
			SceneManager::GetInstance()->PopScene();
		}

		//勝敗のシーン追加や切り替え
		if (m_enemy->m_status.IsDead() && !m_state->isBattel())	//敵が死んだらプレイヤーの勝ち
		{

			//SceneManager::GetInstance()->PushScene()

		}
		else if(m_player->m_status.IsDead() && !m_state->isBattel()) //プレイヤーが死んだらプレイヤーの負け
		{
			//リザルト画面を出す

			//SceneManager::GetInstance()->PushScene()

		}



		break;
	}


}

void BattleScene::Draw()
{


}