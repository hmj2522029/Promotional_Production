#include "SceneLevelUp.h"
#include "Player.h"

void SceneLevelUp::Initialize()
{
	//フォントの読み込み
	AddFontResourceEx("Resource/PixelMplus/PixelMplus12-Regular.ttf", FR_PRIVATE, NULL);
	m_largeFontHandle = CreateFontToHandle("PixelMplus12", 80, -1);
	m_smallFontHandle = CreateFontToHandle("PixelMplus12", 25, -1);
	
	m_rootNode = new Node();

	//背景
	m_rootNode->AddChild(new Actor2D("LevelUp.png", Screen::Center, DrawLayer::UILayer));

	m_tweenScale.Start(3.0f, 1.5f, 1.0f, Easing::Line);

	m_width = GetDrawStringWidthToHandle("LEVEL UP!!", static_cast<int>(strlen("LEVEL UP!!")), m_largeFontHandle);
	m_height = GetFontSizeToHandle(m_largeFontHandle);


}

void SceneLevelUp::Finalize()
{

	DeleteFontToHandle(m_largeFontHandle);
	DeleteFontToHandle(m_smallFontHandle);

	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		delete m_rootNode;
		m_rootNode = nullptr;
	}
	 

}

void SceneLevelUp::Update()
{
	m_tweenScale.Update();

	m_timer += Time::GetInstance()->GetDeltaTime();

	switch (m_state)
	{
	case State::LevelUpText:

		if (m_timer > 2.5f)
		{
			//プレイヤーのレベルアップする前にプレイヤーステータスを保存する
			m_previousStatus = PreviousStatus(
				m_player->m_status.GetLevel(),
				m_player->m_status.GetMaxHp(),
				m_player->m_status.GetAttack(),
				m_player->m_status.GetDefense()
			);

			m_player->LevelUp();

			m_state = State::LevelUpTable;
			m_timer = 0;

		}
		break;

	case State::LevelUpTable:

		if (m_timer > 1.0f)
		{

			m_state = State::Wait;

		}

		break;
		
	case State::Wait:

		if (Keyboard::isAnyPress() && m_timer > 5.5f)
		{
			//次のレベルアップのためにリセット
			m_tweenScale.Start(3.0f, 1.5f, 1.0f, Easing::Line);
			m_state = State::LevelUpText;
			m_timer = 0;

			//レベルアップフラグのリセット
			m_player->ResetLevelUpFlag();

			Physics2D::GetInstance()->Active();
			 
			SceneManager::GetInstance()->PopScene();

		}
		break;
	}


	m_rootNode->TreeUpdate();
}

void SceneLevelUp::Draw()
{

	if (m_state == State::LevelUpText)
	{
		float Scale = m_tweenScale.GetValue();

		//影（黒）
		DrawStringToHandle(
			static_cast<int>(Screen::Center.x - m_width / 2) + 2,
			static_cast<int>(Screen::Center.y - m_height / 2) + 2 ,
			"LEVEL UP!!",
			GetColor(0, 0, 0),
			m_largeFontHandle
		);

		DrawStringToHandle(
			static_cast<int>(Screen::Center.x - m_width / 2),
			static_cast<int>(Screen::Center.y - m_height / 2),
			"LEVEL UP!!",
			GetColor(255, 215, 0),
			m_largeFontHandle
		);

	}
	else
	{
		if (m_timer > 1.0f)
		{

			m_rootNode->TreeDraw();

			//レベル表示
			DrawFormatStringToHandle(	
				static_cast<int>(Screen::Center.x) - 130,
				static_cast<int>(Screen::Center.y) - 100,
				GetColor(255, 255, 255),
				m_smallFontHandle,
				"Lv      →      (+%d)",
				m_player->m_status.GetLevel() - m_previousStatus.Level
			);
			NumberDrawer::DrawNumberTextFont(
				Vector2(
					static_cast<int>(Screen::Center.x) - 35,
					static_cast<int>(Screen::Center.y) - 100
				),
				m_previousStatus.Level,
				m_smallFontHandle,
				Align::Right
			);
			NumberDrawer::DrawNumberTextFont(
				Vector2(
					static_cast<int>(Screen::Center.x) + 70,
					static_cast<int>(Screen::Center.y) - 100
				),
				m_player->m_status.GetLevel(),
				m_smallFontHandle,
				Align::Right
			);

		}
		if (m_timer > 2.0f)
		{
			//HP表示
			DrawFormatStringToHandle(
				static_cast<int>(Screen::Center.x) - 130,
				static_cast<int>(Screen::Center.y) - 50,
				GetColor(255, 255, 255),
				m_smallFontHandle,
				"Hp      →      (+%d)",
				m_player->m_status.GetMaxHp() - m_previousStatus.MaxHp
			);
			NumberDrawer::DrawNumberTextFont(
				Vector2(
					static_cast<int>(Screen::Center.x) - 35,
					static_cast<int>(Screen::Center.y) - 50
				),
				m_previousStatus.MaxHp,
				m_smallFontHandle,
				Align::Right
			);
			NumberDrawer::DrawNumberTextFont(
				Vector2(
					static_cast<int>(Screen::Center.x) + 70,
					static_cast<int>(Screen::Center.y) - 50
				),
				m_player->m_status.GetMaxHp(),
				m_smallFontHandle,
				Align::Right
			);
		}
		if (m_timer > 3.0f)
		{
			//ATK表示
			DrawFormatStringToHandle(
				static_cast<int>(Screen::Center.x) - 130,
				static_cast<int>(Screen::Center.y),
				GetColor(255, 255, 255),
				m_smallFontHandle,
				"ATK     →      (+%d)",
				m_player->m_status.GetAttack() - m_previousStatus.Attack
			);
			NumberDrawer::DrawNumberTextFont(
				Vector2(
					static_cast<int>(Screen::Center.x) - 35,
					static_cast<int>(Screen::Center.y)
				),
				m_previousStatus.Attack,
				m_smallFontHandle,
				Align::Right
			);
			NumberDrawer::DrawNumberTextFont(
				Vector2(
					static_cast<int>(Screen::Center.x) + 70,
					static_cast<int>(Screen::Center.y)
				),
				m_player->m_status.GetAttack(),
				m_smallFontHandle,
				Align::Right
			);
		}
		if (m_timer > 4.0f)
		{
			//DEF表示
			DrawFormatStringToHandle(
				static_cast<int>(Screen::Center.x) - 130,
				static_cast<int>(Screen::Center.y) + 50,
				GetColor(255, 255, 255),
				m_smallFontHandle,
				"DEF     →      (+%d)",
				m_player->m_status.GetDefense() - m_previousStatus.Defense
			);
			NumberDrawer::DrawNumberTextFont(
				Vector2(
					static_cast<int>(Screen::Center.x) - 35,
					static_cast<int>(Screen::Center.y) + 50
				),
				m_previousStatus.Defense,
				m_smallFontHandle,
				Align::Right
			);
			NumberDrawer::DrawNumberTextFont(
				Vector2(
					static_cast<int>(Screen::Center.x) + 70 ,
					static_cast<int>(Screen::Center.y) + 50),
				m_player->m_status.GetDefense(),
				m_smallFontHandle,
				Align::Right
			);

		}


		if (m_timer > 5.0f)
		{
			DrawStringToHandle(
				static_cast<int>(Screen::Center.x) - 125,
				static_cast<int>(Screen::Center.y) + 200,
				"「キーを押して続行」",
				GetColor(255, 255, 255),
				m_smallFontHandle,
				GetColor(0, 0, 0)
			);

		}

	}

}
