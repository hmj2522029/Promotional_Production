#include "BattleScene.h"
#include "SceneGame.h"
#include "ActionButton.h"
#include "Player.h"
#include "Enemy.h"
#include "Character.h"
#include "ResultData.h"

void BattleScene::Initialize()
{
	//フォントの読み込み
	AddFontResourceEx("Resource/PixelMplus/PixelMplus12-Regular.ttf", FR_PRIVATE, NULL);
	m_fontHandle = CreateFontToHandle("PixelMplus12", 30, -1);
	m_smallFontHandle = CreateFontToHandle("PixelMplus12", 20, -1);

	m_rootNode = new Node;

	//当たった敵を取得
	m_enemy = m_player->GetTargetEnemy();

	m_fadeState = FadeState::Fade;
	m_timer = 0;

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

	m_timer += Time::GetInstance()->GetDeltaTime();

	switch (m_fadeState)
	{
	case FadeState::Fade:

		if(ScreenFade::GetInstance()->IsFade())return;	

		ScreenFade::GetInstance()->StartFadeIn(true);
		m_fadeState = FadeState::Run;
		break;

	case FadeState::Run:

		//戦闘が終わったら
		if (!m_state->isBattel())
		{

			//勝敗のシーン追加や切り替え
			if (m_enemy->m_status.IsDead())	//敵が死んだらプレイヤーの勝ち
			{

				//経験値を獲得
				m_player->m_status.GainExp(m_enemy->GetExpReward());

				//リザルトデータに各データを加算する
				m_resultData->AddEnemies(1);
				m_resultData->AddExp(m_enemy->GetExpReward());
				m_resultData->AddPlayTime(m_timer);	


				ScreenFade::GetInstance()->StartFadeOut(0.5f, true);

				//当たった敵のリセット
				m_player->ResetTargetEnemy();

				SceneManager::GetInstance()->PopScene();



			}
			else if(m_player->m_status.IsDead()) //プレイヤーが死んだらプレイヤーの負け
			{
				//シーンゲームに戻す(死亡処理はシーンゲームの方で書く)

				SceneManager::GetInstance()->PopScene();

			}
			else
			{

				//勝敗に入らなかったら逃げたことにする

				//当たった敵のリセット
				m_player->ResetTargetEnemy();

				ScreenFade::GetInstance()->StartFadeOut(0.5f, true);

				SceneManager::GetInstance()->PopScene();

			}

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
	//敵のレベル表示
	DrawFormatStringToHandle(
		static_cast<int>(m_drawingEnemy->GetPosition().x - 62),
		static_cast<int>(m_drawingEnemy->GetPosition().y - 70),
		GetColor(0, 0, 0),
		m_smallFontHandle,
		"Lv: %d",
		m_enemy->m_status.GetLevel()
	);


}
