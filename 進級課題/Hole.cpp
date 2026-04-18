#include "Hole.h"
#include "Camera.h"

Hole::Hole(const TileContext& tile, Camera* camera) :
	Actor2D(DrawLayer::GroundLayer, Tag::Hole, Rigidbody2D::Type::Static),
	m_camera(camera),
	m_tileContext(tile),
	m_size(0, 0),
	m_offsetPos(0, 0),
	m_offsetCol(0, 0)
{
	m_size = Vector2(m_tileContext.tileSize, m_tileContext.tileSize);
	m_offsetPos = Vector2(0, m_tileContext.tileSize * 3);
	m_offsetCol = Vector2(m_size) / 2;

	m_transform.position = (m_tileContext.pos - m_camera->GetPosition() + m_offsetPos);

	m_collider = new BoxCollider(m_size, m_offsetCol);
	m_collider->SetPhysicsBehavior(Tag::Ground, PhysicsBehavior::Ignore);


}

void Hole::Update()
{
	m_transform.position = (m_tileContext.pos - m_camera->GetPosition() + m_offsetPos);


	if (m_transform.position.x + m_tileContext.tileSize <= Screen::Left)
	{
		Destroy();
	}

}

void Hole::Draw()
{

	Actor2D::Draw();
}