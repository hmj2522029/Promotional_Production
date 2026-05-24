#include "AirGround.h"
#include "Camera.h"

AirGround::AirGround(const TileContext& tile) :
	Actor2D("AirGround.png", m_transform.position, DrawLayer::GroundLayer, Tag::Ground, Rigidbody2D::Type::Static),
	m_tileContext(tile),
	m_size(0, 0),
	m_center(0, 0)
{
	
	m_size = Vector2(m_tileContext.tileSize, 30);
	m_center = Vector2(m_size) / 2;

	m_transform.position = m_tileContext.pos - Camera::GetInstance()->GetStagePos() + m_center;

	m_collider = new BoxCollider(m_size);
}

void AirGround::Update()
{

	m_transform.position = (m_tileContext.pos - Camera::GetInstance()->GetStagePos() + m_center);


	if (m_transform.position.x + m_tileContext.tileSize <= Screen::Left)
	{
		Destroy();
	}



}

void AirGround::Draw()
{

	//DrawBoxAA(
	//	m_transform.position.x,
	//	m_transform.position.y,
	//	m_transform.position.x + m_size.x,
	//	m_transform.position.y + m_size.y,
	//	GetColor(0, 255, 255),
	//	true
	//);


	Actor2D::Draw();
}
