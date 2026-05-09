#include "BattleScene.h"
#include "SceneGame.h"
#include "ActionButton.h"
#include "Player.h"
#include "Enemy.h"
#include "Character.h"

void BattleScene::Initialize()
{
	//フォントの読み込み
	AddFontResourceEx("Resource/PixelMplus/PixelMplus12-Regular.ttf", FR_PRIVATE, NULL);
	m_fontHandle = CreateFontToHandle("PixelMplus12", 30, -1);

	m_rootNode = new Node;

	//当たった敵を取得
	m_enemy = m_player->GetTargetEnemy();

	//背景
	m_rootNode->AddChild(new Actor2D("grassland4.jpg", Screen::Center, DrawLayer::BackgroundLayer));

	//枠のUI
	m_rootNode->AddChild(new Actor2D("UI.png", Vector2(225, 535), DrawLayer::UILayer));
	m_rootNode->AddChild(new Actor2D("UI2.png", Vector2(650, 535), DrawLayer::UILayer));
	m_rootNode->AddChild(new Actor2D("UI3.png", Vector2(1065, 535), DrawLayer::UILayer));

	m_state = new BattleState(m_player, m_enemy);
	m_rootNode->AddChild(m_state);

	const Animation2D* anime = m_enemy->GetSprite()->GetAnimation("Idle");
	//敵の表示
	m_drawingEnemy = (new Actor2D(
		*anime,
		m_enemy->GetSprite()->gridSize,
		Screen::Center,
		DrawLayer::EnemyLayer
	));
	//スライムをでかくする
	m_drawingEnemy->SetScale(3.5f);
	m_rootNode->AddChild(m_drawingEnemy);


	//行動ボタン
	m_rootNode->AddChild(new ActionButton(Vector2(75, 535), Player::ActionType::Attack, "sword-wound.png", m_player, m_enemy));
	m_rootNode->AddChild(new ActionButton(Vector2(225, 535), Player::ActionType::Defense, "shield.png", m_player, m_enemy));
	m_rootNode->AddChild(new ActionButton(Vector2(375, 535), Player::ActionType::Escape, "run.png", m_player, m_enemy));


}

void BattleScene::Finalize()
{

	DeleteFontToHandle(m_fontHandle);

	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		delete m_rootNode;
		m_rootNode = nullptr;
	}



}

void BattleScene::Update()
{
	//敵のHP表示
	//Debug::Log("Enemy HP: %d\n", m_enemy ? m_enemy->m_status.GetHp() : 0);


	switch (m_fadeState)
	{
	case FadeState::Fade:

		if(ScreenFade::GetInstance()->IsFade())return;	

		ScreenFade::GetInstance()->StartFadeIn(true);
		m_fadeState = FadeState::Run;
		break;

	case FadeState::Run:


		//勝敗のシーン追加や切り替え
		if (m_enemy->m_status.IsDead() && !m_state->isBattel())	//敵が死んだらプレイヤーの勝ち
		{

			//経験値を獲得
			m_player->m_status.GainExp(m_enemy->GetExpReward());

			//レベルが上がったかどうかの判定
			if (m_player->CheckLevelUp())
			{
				//レベルアップのシーンに切り替える
				//SceneManager::GetInstance()->PushScene());
			}
			else
			{

				ScreenFade::GetInstance()->StartFadeOut(0.5f, true);

				//当たった敵のリセット
				m_player->ResetTargetEnemy();

				Physics2D::GetInstance()->Active();
				SceneManager::GetInstance()->PopScene();


			}



			//SceneManager::GetInstance()->PushScene()

		}
		else if(m_player->m_status.IsDead() && !m_state->isBattel()) //プレイヤーが死んだらプレイヤーの負け
		{
			//シーンゲームに戻す(死亡処理はシーンゲームの方で書く)

			SceneManager::GetInstance()->PopScene();

		}



		break;
	}
 

	m_rootNode->TreeUpdate();

}

void BattleScene::Draw()
{
	if (m_fadeState == FadeState::Fade) return;	//フェード中は描画しない

	m_rootNode->TreeDraw();

	//プレイヤーのステータス表示
	DrawFormatStringToHandle(	//プレイヤーのレベル表示
		610,
		445,
		GetColor(255, 255, 255),
		m_fontHandle,
		"Lv: %d",
		m_player->m_status.GetLevel()
	);	
	DrawFormatStringToHandle(	//プレイヤーのHP表示
		500,
		490,
		GetColor(255, 255, 255),
		m_fontHandle,
		"HP : %d / %d",
		m_player->m_status.GetHp(),
		m_player->m_status.GetMaxHp()
	);
	DrawFormatStringToHandle(	//プレイヤーの攻撃力表示
		500,
		535,
		GetColor(255, 255, 255),
		m_fontHandle,
		"ATK: %d",
		m_player->m_status.GetAttack()
	);
	DrawFormatStringToHandle(	//プレイヤーの防御力表示
		500,
		580,
		GetColor(255, 255, 255),
		m_fontHandle,
		"DEF: %d",
		m_player->m_status.GetDefense()
	);



	//敵のHP表示
	Character::DrawHPBar(
		static_cast<int>(m_drawingEnemy->GetPosition().x - 62),
		static_cast<int>(m_drawingEnemy->GetPosition().y - 50),
		m_enemy->m_status.GetHp(),
		m_enemy->m_status.GetMaxHp(),
		120, 15
	);


}
