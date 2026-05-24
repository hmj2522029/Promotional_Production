#include "SceneCredit.h"

void SceneCredit::Initialize()
{
	//フォントの読み込み
	AddFontResourceEx("Resource/PixelMplus/PixelMplus12-Regular.ttf", FR_PRIVATE, NULL);
	m_fontHandle = CreateFontToHandle("PixelMplus12", 25, -1);

	m_rootNode = new Node();

	Actor2D* Frame = new Actor2D("UI.png", Screen::Center, DrawLayer::UILayer);
	m_rootNode->AddChild(Frame);
	Frame->SetScale(2.0f);

}

void SceneCredit::Finalize()
{

	DeleteFontToHandle(m_fontHandle);

	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		delete m_rootNode;
		m_rootNode = nullptr;
	}

}

void SceneCredit::Update()
{

	if (Keyboard::isDown(KEY_INPUT_R))
	{
		SceneManager::GetInstance()->PopScene();
	}

	m_rootNode->TreeUpdate();

}

void SceneCredit::Draw()
{
	m_rootNode->TreeDraw();

	DrawStringToHandle(
		static_cast<int>(Screen::Center.x) - 385,
		static_cast<int>(Screen::Center.y) - 170,
		"Icon 'Sword Wound' by Lorc - Game-icons.net (CC BY 3.0)",
		GetColor(255, 255, 255),
		m_fontHandle,
		GetColor(0, 0, 0)
	);

	DrawStringToHandle(
		static_cast<int>(Screen::Center.x) - 385,
		static_cast<int>(Screen::Center.y) - 120,
		"Icon 'Run' by Lorc - Game-icons.net (CC BY 3.0)",
		GetColor(255, 255, 255),
		m_fontHandle,
		GetColor(0, 0, 0)
	);

	DrawStringToHandle(
		static_cast<int>(Screen::Center.x) - 385,
		static_cast<int>(Screen::Center.y) - 70,
		"Icon 'Shield' by sbed - Game-icons.net (CC BY 3.0)",
		GetColor(255, 255, 255),
		m_fontHandle,
		GetColor(0, 0, 0)
	);

	DrawStringToHandle(
		static_cast<int>(Screen::Center.x) - 50,
		static_cast<int>(Screen::Center.y) + 150,
		"戻る [R]",
		GetColor(255, 255, 255),
		m_fontHandle,
		GetColor(0, 0, 0)
	);

}