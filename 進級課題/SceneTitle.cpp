#include "SceneTitle.h"
#include "ScenePrep.h"

void SceneTitle::Initialize()
{
	m_rootNode = new Node();

	AddFontResourceEx("Resource/PixelMplus/PixelMplus12-Regular.ttf", FR_PRIVATE, NULL);
	m_fontHandle = CreateFontToHandle("PixelMplus12", 45, -1);

	//”wŒi
	m_rootNode->AddChild(new Actor2D("background.jpg", Screen::Center - Vector2(0, 70), DrawLayer::BackgroundLayer));
	m_rootNode->AddChild(new Actor2D("ground.jpg", Screen::Center + Vector2(0, 215), DrawLayer::BackgroundLayer));

	//ƒ^ƒCƒgƒ‹
	m_rootNode->AddChild(new Actor2D("title.png", Screen::Center - Vector2(0, 120), DrawLayer::UILayer));


}

void SceneTitle::Finalize()
{
	DeleteFontToHandle(m_fontHandle);

	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		delete m_rootNode;
		m_rootNode = nullptr;
	}

}

void SceneTitle::Update()
{
	if (m_waitTransitionTime > 0)
	{
		m_waitTransitionTime -= Time::GetInstance()->GetDeltaTime();
	}

	if (m_waitTransitionTime <= 0 && (Keyboard::isAnyPress() || Mouse::IsAnyButtonPressed()))
	{
		SceneManager::GetInstance()->LoadScene(new ScenePrep);
	}


	m_rootNode->TreeUpdate();
}

void SceneTitle::Draw()
{
	m_rootNode->TreeDraw();

	DrawStringToHandle(
		static_cast<int>(Screen::BottomCenter.x) - 150, static_cast<int>(Screen::BottomCenter.y) - 150,
		"Press Any Key",
		GetColor(255, 255, 255),
		m_fontHandle,
		GetColor(0, 0, 0)
	);


}

