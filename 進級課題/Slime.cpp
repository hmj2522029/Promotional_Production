#include "Slime.h"
#include "Camera.h"

Slime::Slime(const TileContext& tile, Camera* camera) :
	Enemy(DrawLayer::EnemyLayer, Tag::Enemy, Rigidbody2D::Type::Dynamic, Convert(LoadKeyValueFile("Data/Enemy/Slime/Status.txt"))),
	m_camera(camera),
	m_tileContext(tile),
	m_size(0, 0),
	m_offsetCol(0, 0),
	m_offsetPos(0, 0)
{

	m_size = Vector2(18, 18);
	m_offsetPos = Vector2(m_tileContext.tileSize / 2, m_tileContext.tileSize - (m_size.y / 2));

	m_collider = new BoxCollider(m_size, m_offsetCol);
	m_transform.position = (m_tileContext.pos - m_camera->GetPosition() + m_offsetPos);

	SetDrawOrder(DrawLayer::EnemyLayer);

	// Sprite起動
	m_sprite = new Sprite();
	for (const auto& anime : AnimeData)
	{
		m_sprite->Register(anime);
	}
	m_sprite->gridSize = GridSize;

	m_transform.scale = 2.0f;	//スライムは小さいので、少し大きくする

}

void Slime::Update()
{

	m_transform.position = (m_tileContext.pos - m_camera->GetPosition() + m_offsetPos);

	if(m_status.IsDead())
	{
		//アニメーションを死亡モーションにする
		Anime anime = Anime::Die;

		//アニメーションを再生する
		m_sprite->Play(static_cast<int>(anime), 0.0f);

		//死亡モーションが終わったら消す
		if(m_sprite->isAnimationFinished())	Destroy();

		return;
	}
	else
	{
		//アニメーションを待機モーションにする
		Anime anime = Anime::Idle;

		//アニメーションを再生する
		m_sprite->Play(static_cast<int>(anime), 0.0f);
	}



	//オブジェクト画面外に出たら消す
	if (m_transform.position.x + m_tileContext.tileSize <= Screen::Left)
	{
		Destroy();
	}

	//アニメーションの再生
}

void Slime::Draw()
{

	Actor2D::Draw();
}