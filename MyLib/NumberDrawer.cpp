#include "NumberDrawer.h"
#include <string>

void NumberDrawer::DrawNumberTextFont(Vector2 position, int number, int fontHandle, Align align, int color, int edgeColor)
{

	// 数字を文字列に変換
	std::string numberStr = std::to_string(number);

	// 文字列の幅を計算
	int totalWidth = GetDrawStringWidthToHandle(
		numberStr.c_str(),					// 文字列
		static_cast<int>(numberStr.size()),	// 文字列の長さ
		fontHandle							// フォントハンドル
	);

	// 揃え位置を適用してX座標を計算
	int startX = ApplyAlign(static_cast<int>(position.x), totalWidth, align);

	// 文字列を描画
	DrawStringToHandle(
		static_cast<int>(startX),		// X座標
		static_cast<int>(position.y),	// Y座標
		numberStr.c_str(),				// 文字列
		color,							// 文字色
		fontHandle,						// フォントハンドル
		edgeColor						// 縁取り色
	);
}

void NumberDrawer::DrawNumberSpriteFont(Vector2 position, int number, int texture, Vector2 charSize, int padding, float scale, Align align)
{
	//揃え位置を適用してX座標を計算
	int startX = ApplyAlign(
		static_cast<int>(position.x),
		static_cast<int>(GetNumberWidth(number, charSize, padding, scale)),
		align
	);


	int score = number;
	int digit = DigitCalculation(number) - 1;	//左から何文字目か(文字をずらすため)
	do
	{
		int value = score % 10;	// 一の位の値を取り出す(例 123なら321と3から描画する)

		//この式は左から描画する時の式(右からなら式は異なる)
		float x = startX + digit * (charSize.x * scale + padding);

		DrawRectGraph(
			static_cast<int>(x),	// X座標
			static_cast<int>(position.y),			// Y座標
			static_cast<int>(charSize.x) * value,	// 画像の切り取り開始位置のX座標
			0,										// 画像の切り取り開始位置のY座標
			static_cast<int>(charSize.x),			// 画像の幅(切り取りサイズ)
			static_cast<int>(charSize.y),			// 画像の高さ(切り取りサイズ)
			texture,	// 画像ハンドル
			true		// 透過を有効にするか
		);

		score /= 10;	// スコアの桁下げ
		digit--;		// 次の桁へ(左から描画するから)
	} while (score > 0);


}

int NumberDrawer::ApplyAlign(int baseX, int totalWidth, Align align)
{
	switch (align)
	{
	case Align::Left:
		return baseX;

	case Align::Center:
		return baseX - totalWidth / 2;

	case Align::Right:
		return baseX - totalWidth;

	default:
		return baseX;
	}
}

int NumberDrawer::DigitCalculation(int number)
{
	int digitCount = 0;
	int tempNumber = number;

	do
	{	// 少なくとも1回はループする(0も桁数の１に含ますため)
		digitCount++;
		tempNumber /= 10;
	} while (tempNumber > 0);

	return digitCount;
}

float NumberDrawer::GetNumberWidth(int number, Vector2 charSize, int padding, float scale)
{
	int digitCount = DigitCalculation(number);

	// 全体の幅を計算
	float fullWidth = charSize.x * digitCount * scale;		 // 文字部分の幅
	float totalPadding = padding * (digitCount - 1) * scale; // 余白部分の幅(余白は桁数の-1しか入らないため)

	return fullWidth + totalPadding;
}