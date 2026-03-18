#include "Hole.h"
#include "Camera.h"

Hole::Hole(const TileContext& tile, Camera* camera) :
	Actor2D(Tag::Hole, Rigidbody2D::Type::Static),
	m_camera(camera),
	m_tileContext(tile)
{

}

void Hole::Update()
{

}

void Hole::Draw()
{
	
	
	
	Actor2D::Draw();
}