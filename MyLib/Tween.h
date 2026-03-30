#pragma once
#include "Easing.h"

class Tween
{
private:

	Easing::EasingType m_type;	//イージングのタイプ

	bool m_isInterpolation; // 補間中かどうか
	float	m_value;			//補間した値
	float m_time;			// 経過時間
	float m_duration;		// 所要時間
	float m_start;			//開始値
	float m_end;			//終了値


public:

	Tween();

	void Update();

	// 補間の設定(Setting(所要時間, 開始値, 終了値, イージングのタイプ))
	void Start(float duration, float start, float end, Easing::EasingType type);

	//補間した値
	float GetValue() const { return m_value; }

	// 補間中かどうか
	bool IsPlaying() { return m_isInterpolation; }

};