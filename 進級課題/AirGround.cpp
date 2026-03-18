#include "AirGround.h"
#include "Camera.h"

AirGround::AirGround(const TileContext& tile, Camera* camera) :
	Actor2D(Tag::Ground, Rigidbody2D::Type::Kinematic),
	m_camera(camera),
	m_tileContext(tile)
{
	m_transform.position = m_tileContext.pos;
}

void AirGround::Update()
{


}

void AirGround::Draw()
{
	
	
	
	Actor2D::Draw();
}
