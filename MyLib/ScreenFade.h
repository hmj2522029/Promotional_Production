#pragma once
#include "Tween.h"


class ScreenFade
{
private:
	static constexpr int BrightBlack = -255;	// 黒
	static constexpr int BrightWhite = 255;		// 白
	static constexpr int BrightNeutral = 0;		// 通常


	Tween m_brightness;		
	bool m_isFade;			// フェード中かどうか

	ScreenFade();

public:
	// シングルトン
	static ScreenFade* GetInstance()
	{
		static ScreenFade instance;
		return &instance;
	}

	enum class Color
	{
		Black,
		White,
	};

	void Update(int screen);

	// フェードイン(見えない → 見える)
	void StartFadeIn(float duration = 0.5f, Color color = Color::Black);

	// フェードアウト(見える → 見えない)
	void StartFadeOut(float duration = 0.5f, Color color = Color::Black);

	// フェード中かどうか
	bool IsFade() const { return m_isFade; }
};
