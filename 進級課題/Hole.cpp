#include "Hole.h"
#include "Camera.h"

Hole::Hole(const TileContext& tile, Camera* camera) :
	Actor2D(Tag::Hole, Rigidbody2D::Type::Static),
	m_camera(camera),
	m_tileContext(tile),
	m_size(0, 0),
	m_offset(0, 0)
{
	m_offset = Vector2(0, m_tileContext.tileSize * 3);
	m_size = Vector2(m_tileContext.tileSize, m_tileContext.tileSize);

	m_transform.position = (m_tileContext.pos - m_camera->GetPosition() + m_offset);

	m_collider = new BoxCollider(m_size, Vector2(m_size) / 2);
	m_collider->SetPhysicsBehavior(Tag::Ground, PhysicsBehavior::Ignore);


}

void Hole::Update()
{
	m_transform.position = (m_tileContext.pos - m_camera->GetPosition() + m_offset);


	if (m_transform.position.x + m_tileContext.tileSize <= Screen::Left)
	{
		Destroy();
	}

}

void Hole::Draw()
{

	Actor2D::Draw();
}