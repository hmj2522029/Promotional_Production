#include "Sprite.h"
#include "ImageLoader.h"
#include "Time.h"
#include "DxLib.h"

void Sprite::Load()
{
	//最初のテクスチャを覚えておくための箱
	int firstTexture = 0;

	for (auto& anime : m_animeationList)
	{
		//アニメーションから画像のパスを取り出してIDを取得する
		anime.textureId = ImageLoader::GetInstance()->LoadAndGetId(anime.textureName);

		//最初の読んだ画像IDを覚えておく
		if (!firstTexture)
		{
			firstTexture = anime.textureId;
		}

	}

	//サイズの指定がない場合、画像から取得する
	if (gridSize == gridSize.Zero())
	{
		GetGraphSizeF(firstTexture, &gridSize.x, &gridSize.y);
	}

}

void Sprite::Release()
{

	for (auto& anime : m_animeationList)
	{
		ImageLoader::GetInstance()->Delete(anime.textureId);
	}
	m_animeationList.clear();
	m_currentAnime = nullptr;

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
	//再生中のアニメーションがない
	if (!m_currentAnime) return;

	//描画するコマ計算
	int index = 0;

	if (isAnimationFinished())
	{
		//アニメーションが終了していたら最後のコマにする
		index = m_currentAnime->gridAmount - 1;
	}
	else
	{
		//経過時間で描画するコマを計算する
		index = static_cast<int>(m_time / GetDrawingTime());

	}

	DrawRectRotaGraph(
		static_cast<int>(transform.position.x),
		static_cast<int>(transform.position.y),
		static_cast<int>(gridSize.x * index),
		static_cast<int>(0),
		gridSize.x,
		gridSize.y,
		transform.scale,
		transform.angle,
		m_currentAnime->textureId,
		true,
		flipX,
		flipY
	);
}

void Sprite::Register(const char* texturename)
{
	Register(Animation2D(texturename));
}
void Sprite::Register(const Animation2D& anime)
{
	//リストにアニメーションを登録
	m_animeationList.push_back(anime);

	//一番最初に登録したアニメーションを再生中のアニメーションにする
	m_currentAnime = &m_animeationList.front();
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