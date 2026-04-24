#include "Sprite.h"
#include "ImageLoader.h"
#include "Time.hpp"
#include "DxLib.h"

#include "Debug.h"

void Sprite::Load()
{
	//最初のテクスチャを覚えておくための箱
	int firstTexture = 0;

	if (m_mode == SpriteMode::Animation)
	{
		for (auto& anime : m_animeationList)
		{
			//Debug::Log("d");

			//アニメーションから画像のパスを取り出してIDを取得する
			anime.textureId = ImageLoader::GetInstance()->LoadAndGetId(anime.textureName);

			//最初の読んだ画像IDを覚えておく
			if (!firstTexture)
			{
				firstTexture = anime.textureId;
			}

		}

	}
	else if (m_mode == SpriteMode::Region)
	{

		for (auto& image : m_regionList)
		{
			//画像パスからIDを取り出す
			image.textureId = ImageLoader::GetInstance()->LoadAndGetId(image.textureName);


			//最初に読んだ画像IDを覚えておく
			if (!firstTexture)
			{
				firstTexture = image.textureId;
			}

		}

	}

	//サイズの指定がない場合は画像からサイズを取得する 
	if (gridSize == gridSize.Zero())
	{
		GetGraphSizeF(firstTexture, &gridSize.x, &gridSize.y);
	}

}

void Sprite::Release()
{

	//アニメーションを破棄
	for (auto& anime : m_animeationList)
	{
		ImageLoader::GetInstance()->Delete(anime.textureId);
	}
	m_animeationList.clear();
	m_currentAnime = nullptr;

	//画像を破棄
	for (auto& image : m_regionList)
	{
		ImageLoader::GetInstance()->Delete(image.textureId); 
	}
	m_regionList.clear();

}

void Sprite::Update()
{
	//アニメーションが終了しているかどうか
	if (isAnimationFinished()) return;

	//アニメーションの経過時間を加算
	m_time += Time::GetInstance()->GetDeltaTime();

	//ループさせる場合
	if (isAnimationFinished() && m_currentAnime->loop)
	{
		//経過時間がアニメーションの総時間を過ぎていたらループさせる
		m_time -= GetTotalTime();
	}

}

void Sprite::Draw(const Transform& transform)
{
	//アニメーションまたは描画させる画像がない場合
	if (m_mode == SpriteMode::None) return;

	//切り抜きの開始位置を計算するための変数とID
	int SrcX = 0;
	int SrcY = 0;
	int ID = 0;

	if (m_mode == SpriteMode::Animation)
	{
		//アニメーション用の描画の切り抜き位置を計算する
		if (isAnimationFinished())
		{
			//アニメーションが終了していたら 最後のコマにする
			SrcX = static_cast<int>((m_currentAnime->gridAmount - 1) * gridSize.x);
			SrcY = static_cast<int>((m_currentAnime->column - 1) * gridSize.y);
		}
		else
		{
			//経過時間で描画するコマを計算する
			SrcX = static_cast<int>(m_time / GetDrawingTime()) * static_cast<int>(gridSize.x);
			SrcY = static_cast<int>((m_currentAnime->column - 1) * gridSize.y);

		}

		ID = m_currentAnime->textureId;
	}
	else if(m_mode == SpriteMode::Region)
	{
		//一コマの画像・切り抜いた画像の切り抜き位置の計算
		SrcX = static_cast<int>(m_currentRegion->position.x);
		SrcY = static_cast<int>(m_currentRegion->position.y);

		ID = m_currentRegion->textureId;

	}


	DrawRectRotaGraph(
		static_cast<int>(transform.position.x),
		static_cast<int>(transform.position.y),
		static_cast<int>(SrcX),
		static_cast<int>(SrcY),
		static_cast<int>(gridSize.x),
		static_cast<int>(gridSize.y),
		transform.scale,
		transform.angle,
		ID,
		true,
		flipX,
		flipY
	);
}

void Sprite::Register(const SpriteRegion& sprite)
{

	//リストに画像を登録
	m_regionList.push_back(sprite);

	//一番最初に登録した画像を現在の画像にする
	m_currentRegion = &m_regionList.front();
	
	m_mode = SpriteMode::Region;
}
void Sprite::Register(const Animation2D& anime)
{
	//リストにアニメーションを登録
	m_animeationList.push_back(anime);

	//一番最初に登録したアニメーションを再生中のアニメーションにする
	m_currentAnime = &m_animeationList.front();

	//アニメーションモードにする
	m_mode = SpriteMode::Animation;
}
void Sprite::Register(const char* textureName)
{
	Register(SpriteRegion(textureName));
}

void Sprite::Play(int index, float time)
{
	// 指定されたアニメーションをリストから取得
	const auto& anime = m_animeationList.at(index);

	// 現在再生中のアニメーションと同じ、且つ再生時間の指定がない
	if (m_currentAnime == &anime && time == 0) return;

	// アニメーションの切り替え
	m_currentAnime = &anime;
	m_time = time;

}
