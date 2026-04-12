#pragma once
#include "Vector2.h"
#include "Animation2D.h"
#include "SpriteRegion.h"
#include "Transform.h"
#include <vector>

class Sprite
{

private:

	enum class SpriteMode
	{
		None,
		Animation,
		Region
	};

	std::vector <Animation2D> m_animeationList;	//複数のアニメーションを保持する配列(例 待機とか走るを入れる)
	const Animation2D* m_currentAnime;			//現在再生中のアニメーション

	std::vector <SpriteRegion> m_regionList;	
	const SpriteRegion* m_currentRegion;		//一コマの画像または切り抜いた画像を保持する変数

	float m_time;	//アニメーションが開始してからの時間(今のコマ番号を計算するため)
	SpriteMode m_mode;
	
public:

	Vector2 gridSize;	//一コマのサイズ
	bool flipX;			//左右反転
	bool flipY;			//上下反転

	Sprite() :
		m_currentAnime(nullptr),
		m_currentRegion(nullptr),
		m_time(0),
		m_mode(SpriteMode::None),
		flipX(false),
		flipY(false)
	{}

	~Sprite()
	{
		//破棄
		Release();
	}

	void Load();
	void Update();
	void Release();
	void Draw(const Transform& transform);

	//登録
	void Register(const SpriteRegion& sprite);		//一コマ画像用を登録するの関数
	void Register(const Animation2D& anime);		//アニメーションを登録する関数

	//再生
	void Play(int index, float time);

	//アニメーションの一コマの描画時間を取得
	float GetDrawingTime()
	{
		return m_currentAnime ? 1.0f / m_currentAnime->sampleRate : 0;
	}

	//アニメーションの総時間を取得
	float GetTotalTime()
	{
		return m_currentAnime ? m_currentAnime->gridAmount * GetDrawingTime() : 0;
	}

	//アニメーションが終了したかどうか
	bool isAnimationFinished()
	{
	 	return m_currentAnime ? GetTotalTime() <= m_time : true;
	}


};