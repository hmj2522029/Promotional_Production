#include "AirGround.h"
#include "Camera.h"

AirGround::AirGround(const TileContext& tile, Camera* camera) :
	Actor2D(Tag::Ground, Rigidbody2D::Type::Kinematic),
	m_camera(camera),
	m_tileContext(tile),
	m_offsetCol(0, 0),
	m_size(0, 0)
{
	
	m_size = Vector2(m_tileContext.tileSize, 30);
	m_offsetCol = Vector2(m_size) / 2;

	m_transform.position = m_tileContext.pos - m_camera->GetPosition();

	m_collider = new BoxCollider(m_size, m_offsetCol);
}

void AirGround::Update()
{

	m_transform.position = (m_tileContext.pos - m_camera->GetPosition());


	if (m_transform.position.x + m_tileContext.tileSize <= Screen::Left)
	{
		Destroy();
	}



}

void AirGround::Draw()
{

	DrawBoxAA(
		m_transform.position.x,
		m_transform.position.y,
		m_transform.position.x + m_size.x,
		m_transform.position.y + m_size.y,
		GetColor(0, 255, 255),
		true
	);


	Actor2D::Draw();
}
