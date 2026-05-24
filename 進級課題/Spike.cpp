#include "Spike.h"
#include "Camera.h"

Spike::Spike(const TileContext& tile) :
	Actor2D("4 Conjoined Spikes.png", m_transform.position, 30, Tag::Spike, Rigidbody2D::Type::Static),
	m_tileContext(tile),
	m_size(0, 0),
	m_offsetPos(0, 0)
{
	m_size = Vector2(m_tileContext.tileSize, 20);
	m_center = Vector2(m_size) / 2;
	m_offsetPos = Vector2(0, m_tileContext.tileSize - 20);


	m_transform.position = (m_tileContext.pos - Camera::GetInstance()->GetStagePos() + m_offsetPos + m_center);

	m_collider = new BoxCollider(m_size);


}

void Spike::Update()
{

	m_transform.position = (m_tileContext.pos - Camera::GetInstance()->GetStagePos() + m_offsetPos + m_center);


	if (m_transform.position.x + m_tileContext.tileSize <= Screen::Left)
	{
		Destroy();
	}



}

void Spike::Draw()
{


	Actor2D::Draw();
}