#pragma once

struct Animation2D
{
	const char* textureName;	//画像パス
	int textureId;				//画像ID
	int gridAmount;				//コマ数
	int sampleRate;				//1秒間に何コマ進むか
	int column;					//現在の画像の何列目を表示しているか(一つの画像に複数のアニメーションが入っている場合あるため)
	bool loop;					//ループするかどうか(true = ループ : false = 一回で終わり)

	//暗黙的な型変換禁止のためにexplicitをつける
	explicit constexpr Animation2D(
		const char* anime,
		int amount = 1,		
		int rate = 10,		
		bool loop = true,
		int column = 1	
	
	) :
		textureName(anime),
		textureId(0),
		gridAmount(amount),
		sampleRate(rate),
		column(column),
		loop(loop)
	{
	}

};