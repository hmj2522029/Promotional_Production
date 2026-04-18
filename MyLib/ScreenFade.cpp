#include "ScreenFade.h"
#include "Screen.h"
#include "Time.h"
#include "Easing.h"
#include "Math.hpp"
#include "DxLib.h"

#include "Debug.h"

ScreenFade::ScreenFade() :
	m_isFade(false),
	m_executed(false)
{
}

void ScreenFade::Update(int screen)
{
	//Tweenの更新
	m_brightness.Update();

	// フェード中でなければ何もしない
	if (!IsFade()) return;

	//Debug::Log("Brightness: %f\n", m_brightness.GetValue());

	// Tweenの再生が終わったらフェード終了
	if (!m_brightness.IsPlaying())
	{
		m_isFade = false; 
		m_executed = false;
	}


	// Tweenで輝度を算出して、スクリーンに反映
	GraphFilter(
		screen,
		DX_GRAPH_FILTER_HSB,
		0, 0,
		0,
		static_cast<int>(m_brightness.GetValue())
	);
}

// フェードイン
void ScreenFade::StartFadeIn(bool once, float duration, Color color)
{
	// フェードインは一回だけ通す(trueなら)
	if (once)
	{
		if (m_executed) return;

		m_executed = true;
	}

	// フェード開始時の輝度
	float beginBright = static_cast<float>((color == Color::Black) ? BrightBlack : BrightWhite);

	// フェード終了時の輝度
	float endBright = static_cast<float>(BrightNeutral);

	// Tweenの設定
	m_brightness.Start(duration, beginBright, endBright, Easing::EasingType::InOutCubic);
	m_isFade = true;

}

// フェードアウト
void ScreenFade::StartFadeOut(bool once, float duration, Color color)
{
	// フェードインは一回だけ通す(trueなら)
	if (once)
	{
		if (m_executed) return;

		m_executed = true;
	}

	// フェード開始時の輝度
	float beginBright = static_cast<float>(BrightNeutral);

	// フェード終了時の輝度
	float endBright = static_cast<float>((color == Color::Black) ? BrightBlack : BrightWhite);

	// Tweenの設定
	m_brightness.Start(duration, beginBright, endBright, Easing::EasingType::InOutCubic);
	m_isFade = true;
}
