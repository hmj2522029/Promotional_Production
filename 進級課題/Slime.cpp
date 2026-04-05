#include "Slime.h"
#include "Camera.h"

Slime::Slime(const TileContext& tile, Camera* camera) :
	Enemy(Tag::Enemy, Rigidbody2D::Type::Dynamic, 1, 15, 5, 2, 10),
	m_camera(camera),
	m_tileContext(tile),
	m_size(0, 0),
	m_offsetCol(0, 0),
	m_offsetPos(0, 0)
{

	m_size = Vector2(32, 32);
	m_offsetPos = Vector2(m_tileContext.tileSize / 2, m_tileContext.tileSize - (m_size.y / 2));

	m_collider = new BoxCollider(m_size, m_offsetCol);
	m_transform.position = (m_tileContext.pos - m_camera->GetPosition() + m_offsetPos);


}

void Slime::Update()
{

	m_transform.position = (m_tileContext.pos - m_camera->GetPosition() + m_offsetPos);

	//オブジェクト画面外に出たら消す・HPが0以下になったら消す
	if (m_transform.position.x + m_tileContext.tileSize <= Screen::Left || m_status.GetHp() <= 0)
	{
		Destroy();
	}

}

void Slime::Draw()
{

	DrawBoxAA(
		m_transform.position.x - m_size.x / 2,
		m_transform.position.y - m_size.y / 2,
		m_transform.position.x + m_size.x / 2,
		m_transform.position.y + m_size.y / 2,
		GetColor(255, 0, 0),
		true
	);



	Actor2D::Draw();
}