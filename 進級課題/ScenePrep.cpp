#include "ScenePrep.h"
#include "SceneGame.h"
#include "PrepPlayerController.h"
#include "SceneSelectionButton.h"
#include "SceneStatus.h"
#include "SceneCredit.h"
#include "HitBox.h"

void ScenePrep::Initialize()
{
	//フォントの読み込み
	AddFontResourceEx("Resource/PixelMplus/PixelMplus12-Regular.ttf", FR_PRIVATE, NULL);
	m_fontHandle = CreateFontToHandle("PixelMplus12", 30, -1);


	m_rootNode = new Node;

	//背景
	m_rootNode->AddChild(new Actor2D("background.jpg", Screen::Center - Vector2(0, 70), DrawLayer::BackgroundLayer));
	m_rootNode->AddChild(new Actor2D("ground.jpg", Screen::Center + Vector2(0, 215), DrawLayer::BackgroundLayer));

	//プレイヤーの演出
	m_playerController = new PrepPlayerController;
	m_rootNode->AddChild(m_playerController);

	//ヒットボックスの生成(地面)
	m_rootNode->AddChild(new HitBox(Screen::Center + Vector2(0, 320), Vector2(1500, 250)));

	//ボタン作成
	m_rootNode->AddChild(new SceneSelectionButton(Screen::Center - Vector2(0, 150), SceneSelectionType::SceneGame, this));
	m_rootNode->AddChild(new SceneSelectionButton(Screen::Center - Vector2(0, 50) , SceneSelectionType::SceneStatus, this));
	m_rootNode->AddChild(new SceneSelectionButton(Screen::Center + Vector2(0, 50), SceneSelectionType::SceneCredits, this));

	//ステータスシーン
	m_sceneStatus = new SceneStatus(m_playerController->GetPlayer());
	m_sceneStatus->Initialize();

	//クレジットシーン
	m_sceneCredit = new SceneCredit();
	m_sceneCredit->Initialize();


	// BGM
	m_bgm = SoundLoader::GetInstance()->LoadAndGetId("sound/待機BGM.mp3");
	ChangeVolumeSoundMem(150, m_bgm);
	PlaySoundMem(m_bgm, DX_PLAYTYPE_LOOP);

}

void ScenePrep::Finalize()
{
	DeleteFontToHandle(m_fontHandle);

	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		delete m_rootNode;
		m_rootNode = nullptr;
	}

	if (m_sceneStatus)
	{
		SceneManager::GetInstance()->RemoveScene(m_sceneStatus);
		m_sceneStatus->Finalize();
		delete m_sceneStatus;
		m_sceneStatus = nullptr;
	}

	if (m_sceneCredit)
	{
		SceneManager::GetInstance()->RemoveScene(m_sceneCredit);
		m_sceneCredit->Finalize();
		delete m_sceneCredit;
		m_sceneCredit = nullptr;
	}


	// BGM
	SoundLoader::GetInstance()->Delete(m_bgm);

}

void ScenePrep::Update()
{


	m_rootNode->TreeUpdate();
}

void ScenePrep::Draw()
{
	m_rootNode->TreeDraw();


}

void ScenePrep::LoadScene(SceneSelectionType type)
{
	switch (type)
	{
	case SceneSelectionType::SceneGame:

		SceneManager::GetInstance()->LoadScene(new SceneGame());

		break;

	case SceneSelectionType::SceneStatus:

		SceneManager::GetInstance()->PushScene(m_sceneStatus);

		break;
	case SceneSelectionType::SceneCredits:
		SceneManager::GetInstance()->PushScene(m_sceneCredit);
		break;

	default:
		break;

	}
}