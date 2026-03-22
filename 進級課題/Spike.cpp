#include "Spike.h"
#include "Camera.h"

Spike::Spike(const TileContext& tile, Camera* camera) :
	Actor2D(Tag::Spike, Rigidbody2D::Type::Static),
	m_camera(camera),
	m_tileContext(tile),
	m_size(0, 0),
	m_offsetCol(0, 0),
	m_offsetPos(0, 0)
{
	m_size = Vector2(m_tileContext.tileSize, 20);
	m_offsetCol = Vector2(m_size) / 2;
	m_offsetPos = Vector2(0, m_tileContext.tileSize - 20);

	m_transform.position = (m_tileContext.pos - m_camera->GetPosition() + m_offsetPos);

	m_collider = new BoxCollider(m_size, m_offsetCol);


}

void Spike::Update()
{

	m_transform.position = (m_tileContext.pos - m_camera->GetPosition() + m_offsetPos);


	if (m_transform.position.x + m_tileContext.tileSize <= Screen::Left)
	{
		Destroy();
	}



}

void Spike::Draw()
{


	Actor2D::Draw();
}