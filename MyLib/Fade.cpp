#include "Fade.h"
#include "Time.h"
#include "Easing.h"
#include "DxLib.h"

Fade::Fade() :
	m_isFade(false),
	m_elapsedTime(0),
	m_duration(0),
	m_beginBright(0),
	m_endBright(0)
{
}

void Fade::Update(int screen)
{
	// フェード中でなければ何もしない
	if (!IsFade()) return;

	// 時間経過
	m_elapsedTime += Time::GetInstance()->GetDeltaTime();

	// 経過時間が所要時間を超えたらフェード終了
	if (m_elapsedTime >= m_duration)
	{
		m_isFade = false;
		m_elapsedTime = m_duration;
	}

	// 経過時間から輝度を算出して、スクリーンに反映
	GraphFilter(
		screen,
		DX_GRAPH_FILTER_HSB,
		0, 0,
		0,
		Easing::Lerp(m_beginBright, m_endBright, m_elapsedTime / m_duration)
	);
}

// フェードイン
void Fade::StartFadeIn(float duration, Color color)
{
	m_elapsedTime = m_isFade ? m_duration - m_elapsedTime : 0;
	m_duration = duration;
	m_beginBright = (color == Color::Black) ? BrightBlack : BrightWhite;
	m_endBright = BrightNeutral;
	m_isFade = true;
}

// フェードアウト
void Fade::StartFadeOut(float duration, Color color)
{
	m_elapsedTime = m_isFade ? m_duration - m_elapsedTime : 0;
	m_duration = duration;
	m_beginBright = BrightNeutral;
	m_endBright = (color == Color::Black) ? BrightBlack : BrightWhite;
	m_isFade = true;
}
