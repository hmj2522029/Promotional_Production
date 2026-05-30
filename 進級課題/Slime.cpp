#include "Slime.h"
#include "Camera.h"

Slime::Slime(const TileContext& tile) :
	Enemy(
		DrawLayer::EnemyLayer,
		Tag::Enemy, 
		Rigidbody2D::Type::Dynamic, 
		Convert(LoadKeyValueFile("Data/Enemy/Slime/Status.txt")),
		StatusIncreaseValue{ UpHpMax, UpHpMin, UpAttackMax, UpAttackMin, UpDefenseMax, UpDefenseMin, UpExpReward },
		EnemyLevelParam{ Multiplier, MinOffset, MaxOffset },
		static_cast<int>(tile.pos.x / tile.tileSize),	//距離(メートル)
		LevelPerDistance
		),
	m_tileContext(tile),
	m_size(0, 0),
	m_offsetCol(0, 0),
	m_offsetPos(0, 0)
{


	m_size = Vector2(18, 18);
	m_offsetPos = Vector2(m_tileContext.tileSize / 2, m_tileContext.tileSize - (m_size.y / 2));

	m_collider = new BoxCollider(m_size, m_offsetCol);
	m_transform.position = (m_tileContext.pos - Camera::GetInstance()->GetStagePos() + m_offsetPos);

	//アニメデータ
	AnimeData =
	{
		Animation2D("Idle", "FreeSlime/slime_idle.png", 4, 7, true),
		Animation2D("Run", "FreeSlime/slime_run.png", 6, 11, true),
		Animation2D("Die", "FreeSlime/slime_die.png", 5, 9, false),
	};


	// Sprite起動
	m_sprite = new Sprite();
	for (const auto& anime : AnimeData)
	{
		m_sprite->Register(anime);
	}
	m_sprite->gridSize = GridSize;
	m_sprite->flipX = true;

	m_transform.scale = 2.0f;	//スライムは小さいので、少し大きくする


	m_defenseSE = SoundLoader::GetInstance()->LoadAndGetId("sound/防御音.mp3");
	m_escapeSE = SoundLoader::GetInstance()->LoadAndGetId("sound/逃げる.mp3");


}

void Slime::Update()
{

	m_transform.position = (m_tileContext.pos - Camera::GetInstance()->GetStagePos() + m_offsetPos);

	if(m_status.IsDead())
	{

		//アニメーションを再生する(死亡)
		m_sprite->Play("Die", 0.0f);

		//死亡モーションが終わったら消す
		if(m_sprite->isAnimationFinished())	Destroy();

		return;
	}
	else
	{

		//アニメーションを再生する(待機)
		m_sprite->Play("Idle", 0.0f);
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

void Slime::Release()
{
	Actor2D::Release();

	SoundLoader::GetInstance()->Delete(m_defenseSE);
	SoundLoader::GetInstance()->Delete(m_escapeSE);

}