#include "Spike.h"
#include "Camera.h"

Spike::Spike(const TileContext& tile, Camera* camera) :
	Actor2D(Tag::Spike, Rigidbody2D::Type::Static),
	m_camera(camera),
	m_tileContext(tile)
{

}

void Spike::Update()
{

}

void Spike::Draw()
{


	Actor2D::Draw();
}