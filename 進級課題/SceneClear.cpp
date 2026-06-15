#include "SceneClear.h"
#include "SceneTitle.h"
#include "TotalData.h"

void SceneClear::Initialize()
{
	//リザルトのデータをTotalDataに保存する
	TotalData::GetInstance()->AddData(m_resultData);

	//時間の計測
	m_totalSeconds = static_cast<int>(TotalData::GetInstance()->GetTotalPlayTime());	//プレイ時間を秒数で取得
	m_hours = m_totalSeconds / 3600;			//時間
	m_minutes = (m_totalSeconds % 3600) / 60;	//分
	m_seconds = m_totalSeconds % 60;			//秒

	//フォント読み込み
	AddFontResourceEx("Resource/PixelMplus/PixelMplus12-Regular.ttf", FR_PRIVATE, NULL);
	m_largeFontHandle = CreateFontToHandle("PixelMplus12", 30, -1);
	m_smallFontHandle = CreateFontToHandle("PixelMplus12", 25, -1);


	m_rootNode = new Node();

	//背景
	m_rootNode->AddChild(new Actor2D("Clear.png", Screen::Center, DrawLayer::UILayer));

	//SEの読み込み
	m_se = SoundLoader::GetInstance()->LoadAndGetId("sound/ピコ音.mp3");

	m_step = 0;
	m_isEnding = false;
	m_timer = 0;

}

void SceneClear::Finalize()
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

void SceneClear::Update()
{

	m_timer += Time::GetInstance()->GetDeltaTime();

	m_rootNode->TreeUpdate();

	if (m_timer > 5.5f && Keyboard::isAnyPress())
	{
		m_isEnding = true;

		SceneManager::GetInstance()->LoadScene(new SceneTitle());
	}

	if (!m_isEnding && m_step < m_timings.size() && m_timer > m_timings[m_step])
	{
		PlaySoundMem(m_se, DX_PLAYTYPE_BACK);
		m_step++;

		if (m_step >= m_timings.size())
		{
			m_step = static_cast<int>(m_timings.size());
		}

	}



}

void SceneClear::Draw()
{
	if (m_timer > 0.5f) m_rootNode->TreeDraw();


	if (m_timer > 1.0f)
	{
		//プレイヤーが何メートル進んだかを表示
		DrawStringToHandle(
			static_cast<int>(Screen::Center.x) - 170,
			static_cast<int>(Screen::Center.y) - 100,
			"総距離:                   m",
			GetColor(255, 255, 255),
			m_smallFontHandle,
			GetColor(0, 0, 0)
		);
		NumberDrawer::DrawNumberTextFont(
			Vector2(
				static_cast<int>(Screen::Center.x) + 150,
				static_cast<int>(Screen::Center.y) - 100
			),
			TotalData::GetInstance()->GetTotalDistance(),
			m_smallFontHandle,
			Align::Right
		);
	}
	if (m_timer > 2.0f)
	{
		//獲得した経験値を表示
		DrawFormatStringToHandle(
			static_cast<int>(Screen::Center.x) - 170,
			static_cast<int>(Screen::Center.y) - 50,
			GetColor(255, 255, 255),
			m_smallFontHandle,
			"総経験値:"
		);
		NumberDrawer::DrawNumberTextFont(
			Vector2(
				static_cast<int>(Screen::Center.x) + 150,
				static_cast<int>(Screen::Center.y) - 50
			),
			TotalData::GetInstance()->GetTotalExp(),
			m_smallFontHandle,
			Align::Right
		);
	}
	if (m_timer > 3.0f)
	{
		//倒した敵の数を表示
		DrawFormatStringToHandle(
			static_cast<int>(Screen::Center.x) - 170,
			static_cast<int>(Screen::Center.y),
			GetColor(255, 255, 255),
			m_smallFontHandle,
			"総撃破:                   匹"
		);
		NumberDrawer::DrawNumberTextFont(
			Vector2(
				static_cast<int>(Screen::Center.x) + 150,
				static_cast<int>(Screen::Center.y)
			),
			TotalData::GetInstance()->GetTotalEnemies(),
			m_smallFontHandle,
			Align::Right
		);
	}
	if (m_timer > 4.0f)
	{
		//プレイ時間を表示
		DrawFormatStringToHandle(
			static_cast<int>(Screen::Center.x) - 170,
			static_cast<int>(Screen::Center.y) + 50,
			GetColor(255, 255, 255),
			m_smallFontHandle,
			"総プレイ時間:       %02d:%02d:%02d",
			m_hours,
			m_minutes,
			m_seconds
		);
	}


	if (m_timer > 5.0f)
	{
		DrawStringToHandle(
			static_cast<int>(Screen::Center.x) - 155,
			static_cast<int>(Screen::Center.y) + 180,
			"「キーを押して戻る」",
			GetColor(255, 255, 255),
			m_largeFontHandle,
			GetColor(0, 0, 0)
		);
	}


}