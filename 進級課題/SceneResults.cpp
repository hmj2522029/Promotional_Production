#include "SceneResults.h"
#include "ScenePrep.h"
#include "ResultData.h"
#include "TotalData.h"

void SceneResults::Initialize()
{
	//時間の計測
	m_totalSeconds = static_cast<int>(m_resultData->GetPlayTime());	//プレイ時間を秒数で取得
	m_hours = m_totalSeconds / 3600;								//時間
	m_minutes = (m_totalSeconds % 3600) / 60;						//分
	m_seconds = m_totalSeconds % 60;								//秒

	//フォント読み込み
	AddFontResourceEx("Resource/PixelMplus/PixelMplus12-Regular.ttf", FR_PRIVATE, NULL);
	m_largeFontHandle = CreateFontToHandle("PixelMplus12", 30, -1);
	m_smallFontHandle = CreateFontToHandle("PixelMplus12", 25, -1);

	m_rootNode = new Node();

	//背景
	m_rootNode->AddChild(new Actor2D("Result.png", Screen::Center ,DrawLayer::UILayer));

	//SEの読み込み
	m_se = SoundLoader::GetInstance()->LoadAndGetId("sound/ピコ音.mp3");
	ChangeVolumeSoundMem(200, m_se);


	m_step = 0;
	m_timer = 0;
	m_isEnding = false;

}

void SceneResults::Finalize()
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

void SceneResults::Update()
{
	m_timer += Time::GetInstance()->GetDeltaTime();

	m_rootNode->TreeUpdate();

	if (m_timer > 5.5f && Keyboard::isAnyPress() )
	{

		TotalData::GetInstance()->AddData(m_resultData);

		m_isEnding = true;

		SceneManager::GetInstance()->LoadScene(new ScenePrep());

	}

	if(!m_isEnding && m_step < m_timings.size() && m_timer > m_timings[m_step])
	{
		PlaySoundMem(m_se, DX_PLAYTYPE_BACK);
		m_step++;

		if (m_step >= m_timings.size())
		{
			m_step = static_cast<int>(m_timings.size()); 
		}

	}

}

void SceneResults::Draw()
{
	if (m_timer > 0.5f) m_rootNode->TreeDraw();


	if (m_timer > 1.0f)
	{


		//プレイヤーが何メートル進んだかを表示
		DrawStringToHandle(
			static_cast<int>(Screen::Center.x) - 150,
			static_cast<int>(Screen::Center.y) - 100 ,
			"距離:                 m",
			GetColor(255, 255, 255),
			m_smallFontHandle,
			GetColor(0, 0, 0)
		);
		NumberDrawer::DrawNumberTextFont(
			Vector2(
				static_cast<int>(Screen::Center.x) + 120,
				static_cast<int>(Screen::Center.y) - 100
			),
			m_resultData->GetDistance(),
			m_smallFontHandle,
			Align::Right
		);
	}
	if (m_timer > 2.0f)
	{

		//獲得した経験値を表示
		DrawFormatStringToHandle(
			static_cast<int>(Screen::Center.x) - 150,
			static_cast<int>(Screen::Center.y) - 50,
			GetColor(255, 255, 255),
			m_smallFontHandle,
			"経験値:"
		);
		NumberDrawer::DrawNumberTextFont(
			Vector2(
				static_cast<int>(Screen::Center.x) + 120,
				static_cast<int>(Screen::Center.y) - 50
			),
			m_resultData->GetExp(),
			m_smallFontHandle,
			Align::Right
		);
	}
	if (m_timer > 3.0f)
	{

		//倒した敵の数を表示
		DrawFormatStringToHandle(
			static_cast<int>(Screen::Center.x) - 150,
			static_cast<int>(Screen::Center.y),
			GetColor(255, 255, 255),
			m_smallFontHandle,
			"撃破:                 匹"
		);
		NumberDrawer::DrawNumberTextFont(
			Vector2(
				static_cast<int>(Screen::Center.x) + 120,
				static_cast<int>(Screen::Center.y)
			),
			m_resultData->GetEnemies(),
			m_smallFontHandle,
			Align::Right
		);
	}
	if (m_timer > 4.0f)
	{

		//プレイ時間を表示
		DrawFormatStringToHandle(
			static_cast<int>(Screen::Center.x) - 150,
			static_cast<int>(Screen::Center.y) + 50,
			GetColor(255, 255, 255),
			m_smallFontHandle, 
			"プレイ時間:     %02d:%02d:%02d",
			m_hours,
			m_minutes,
			m_seconds
		);
	}


	if (m_timer > 5.0f)
	{
		DrawStringToHandle(
			static_cast<int>(Screen::Center.x) - 155,
			static_cast<int>(Screen::Center.y) + 150,
			"「キーを押して戻る」",
			GetColor(255, 255, 255),
			m_largeFontHandle,
			GetColor(0, 0, 0)
		);
	}

}