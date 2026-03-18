#include "Ground.h"
#include "Camera.h"
#include "HitBox.h"

Ground::Ground(const TileContext& tile, Camera* camera) :
	Actor2D(Tag::Ground, Rigidbody2D::Type::Static),
	m_camera(camera),
	m_tileContext(tile),
	m_size(0, 0)
{

	m_size = Vector2(m_tileContext.tileSize, m_tileContext.tileSize * 3);
	m_transform.position = m_tileContext.pos - m_camera->GetPosition();

	m_collider = new BoxCollider(m_size, Vector2(m_size.x / 2, m_size.y / 2));

	m_rigidbody2d.bounciness = 0;


}

void Ground::Update()
{

}

void Ground::Draw()
{

	DrawBoxAA(
		m_transform.position.x ,
		m_transform.position.y ,
		m_transform.position.x - m_camera->GetPosition().x + m_size.x,
		m_transform.position.y - m_camera->GetPosition().y + m_size.y,
		GetColor(0, 255, 255),
		true
	);

	
	Actor2D::Draw();
}