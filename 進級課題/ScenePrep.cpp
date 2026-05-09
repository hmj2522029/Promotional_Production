#include "ScenePrep.h"
#include "Player.h"
#include "SceneGame.h"
#include "SceneStatus.h"

void ScenePrep::Initialize()
{
	//ƒtƒHƒ“ƒg‚Ì“Ç‚Ýž‚Ý
	AddFontResourceEx("Resource/PixelMplus/PixelMplus12-Regular.ttf", FR_PRIVATE, NULL);
	m_fontHandle = CreateFontToHandle("PixelMplus12", 30, -1);


	m_rootNode = new Node;

	//”wŒi
	m_rootNode->AddChild(new Actor2D("background.jpg", Screen::Center - Vector2(0, 70), DrawLayer::BackgroundLayer));
	m_rootNode->AddChild(new Actor2D("ground.jpg", Screen::Center + Vector2(0, 215), DrawLayer::BackgroundLayer));


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

	case SceneSelectionType::SceneCredits:
		//SceneManager::GetInstance()->PushScene(new SceneCredits());
		break;

	default:
		break;

	}
}