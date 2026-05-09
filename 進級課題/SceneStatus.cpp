#include "SceneStatus.h"
#include "Player.h"

void SceneStatus::Initialize()
{

	//フォントの読み込み
	AddFontResourceEx("Resource/PixelMplus/PixelMplus12-Regular.ttf", FR_PRIVATE, NULL);
	m_largeFontHandle = CreateFontToHandle("PixelMplus12", 35, -1);
	m_smallFontHandle = CreateFontToHandle("PixelMplus12", 25, -1);

	m_rootNode = new Node();

	//背景
	m_rootNode->AddChild(new Actor2D("status.png", Screen::Center, DrawLayer::UILayer));

	//キャラクター表示(プレイヤー)
	const Animation2D* anime = m_player->GetSprite()->GetAnimation("Idle");
	Actor2D* player = (new Actor2D(
		*anime,
		m_player->GetSprite()->gridSize,
		Screen::Center + Vector2(0, -130), 
		DrawLayer::UILayer
	));
	player->SetScale(2.0f);
	m_rootNode->AddChild(player);

}

void SceneStatus::Finalize()
{

	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		delete m_rootNode;
		m_rootNode = nullptr;
	}


}

void SceneStatus::Update()
{


	//ステータス画面から戻る
	if (Keyboard::isDown(KEY_INPUT_X))
	{

		Physics2D::GetInstance()->Active();
		SceneManager::GetInstance()->PopScene();
	}



	m_rootNode->TreeUpdate();

}

void SceneStatus::Draw()
{
	m_rootNode->TreeDraw();

	//プレイヤーのステータスを描画
		//プレイヤーのステータス表示
	DrawFormatStringToHandle(	//プレイヤーのレベル表示
		Screen::Center.x - 45,
		Screen::Center.y - 80,
		GetColor(255, 255, 255),
		m_largeFontHandle,
		"Lv: %d",
		m_player->m_status.GetLevel()
	);


	DrawFormatStringToHandle(	//プレイヤーのHP表示
		Screen::Center.x - 100,
		Screen::Center.y - 20,
		GetColor(255, 255, 255),
		m_smallFontHandle,
		"HP :        / %d",
		m_player->m_status.GetMaxHp()
	);
	NumberDrawer::DrawNumberTextFont(
		Vector2(Screen::Center.x + 40, Screen::Center.y - 20) ,
		m_player->m_status.GetHp(),
		m_smallFontHandle,
		Align::Right
	);
	DrawFormatStringToHandle(	//プレイヤーの攻撃力表示
		Screen::Center.x - 100,
		Screen::Center.y + 25,
		GetColor(255, 255, 255),
		m_smallFontHandle,
		"ATK:"
	);
	NumberDrawer::DrawNumberTextFont(
		Vector2(Screen::Center.x + 110, Screen::Center.y + 25),
		m_player->m_status.GetAttack(),
		m_smallFontHandle,
		Align::Right
	);

	DrawFormatStringToHandle(	//プレイヤーの防御力表示
		Screen::Center.x - 100,
		Screen::Center.y + 70,
		GetColor(255, 255, 255),
		m_smallFontHandle,
		"DEF:"
	);
	NumberDrawer::DrawNumberTextFont(
		Vector2(Screen::Center.x + 110, Screen::Center.y + 70),
		m_player->m_status.GetDefense(),
		m_smallFontHandle,
		Align::Right
	);





}