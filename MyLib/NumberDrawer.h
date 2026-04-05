#pragma once
#include "DxLib.h"
#include "Vector2.h"

enum class Align
{
	Left,
	Center,
	Right
};

class NumberDrawer
{
private:
	NumberDrawer() {};

	static int ApplyAlign(int baseX, int totalWidth, Align align);	// 揃え位置を適用してX座標を計算
	static int DigitCalculation(int number); // 桁数計算
	static float GetNumberWidth(int number, Vector2 charSize, int padding, float scale); // 数字の幅を取得

public:

	static void DrawNumberTextFont(	//通常フォント
		Vector2 position,					// 描画位置
		int number,							// 描画する数値
		int fontHandle,						// フォントハンドル
		Align align = Align::Left,			// 揃え位置
		int color = GetColor(255, 255, 255),// 文字色
		int edgeColor = GetColor(0, 0, 0)	// 縁取り色
	);

	static void DrawNumberSpriteFont(	// 画像フォント
		Vector2 position,			// 描画位置
		int number,					// 描画する数値
		int texture,				// 画像フォント
		Vector2 charSize,			// 1文字のサイズ
		int padding = 0,			// 文字の余白
		float scale = 1.0f,			// 拡大率
		Align align = Align::Left	// 揃え位置
	);

};