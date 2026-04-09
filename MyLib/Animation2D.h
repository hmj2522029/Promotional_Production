#pragma once

struct Animation2D
{
	const char* textureName;	//画像パス
	int textureId;				//画像ID
	int gridAmount;				//コマ数
	int sampleRate;				//1秒間に何コマ進むか
	bool loop;					//ループするかどうか(true = ループ : false = 一回で終わり)

	explicit constexpr Animation2D(
		const char* anime,
		int amount = 1,		//一旦コマ1の画像として設定する(rateとloopも)
		int rate = 0,		
		bool loop = false	
	
	) :
		textureName(anime),
		textureId(0),
		gridAmount(amount),
		sampleRate(rate),
		loop(loop)
	{
	}


};