#include "Tween.h"
#include "Time.h"
#include "Easing.h"
#include "Math.hpp"
#include "DxLib.h"

Tween::Tween() :
	m_type(Easing::EasingType::Line),	//一旦普通のイージング
	m_isInterpolation(false),
	m_value(0),
	m_time(0),
	m_duration(0),
	m_start(0),
	m_end(0)			
{
}

void Tween::Update()
{
	// 補間中でなければ何もしない
	if (!m_isInterpolation) return;

	// 時間経過 
	m_time += Time::GetInstance()->GetDeltaTime();

	// 経過時間が所要時間を超えたらフェード終了
	if (m_time >= m_duration)
	{
		m_isInterpolation = false;
		m_time = m_duration;	// 経過時間を所要時間に合わせる(オーバーしている分を補正する)
	}

	float t = m_time / m_duration;
	float eased = t;

	switch (m_type)
	{
	case Easing::EasingType::Line:
		//Lineはそのままだから
		break;
	case Easing::EasingType::InCubic:

		eased = Easing::EaseInCubic(t);

		break;
	case Easing::EasingType::OutCubic:

		eased = Easing::EaseOutCubic(t);

		break;
	case Easing::EasingType::InOutCubic:

		eased = Easing::EaseInOutCubic(t);

		break;
	}

	m_value = Math::Lerp(m_start, m_end, eased);

}

void Tween::Start(float duration, float start, float end, Easing::EasingType type)
{
	m_time = m_isInterpolation ? m_duration - m_time : 0;	// 補間中なら残り時間から開始、そうでなければ0から開始
	m_duration = duration;
	m_start = start;
	m_end = end;
	m_type = type;
	m_isInterpolation = true;
}



