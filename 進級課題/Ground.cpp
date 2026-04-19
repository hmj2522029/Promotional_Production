#include "Ground.h"
#include "Camera.h"
#include "HitBox.h"

Ground::Ground(const TileContext& tile, Camera* camera) :
	Actor2D(DrawLayer::GroundLayer ,Tag::Ground, Rigidbody2D::Type::Static),
	m_camera(camera),
	m_tileContext(tile),
	m_size(0, 0),
	m_center(0, 0),
	m_offsetPos(0, 65),
	m_offsetCol(0, 95)
{

	m_size = Vector2(m_tileContext.tileSize, m_tileContext.tileSize * 3);

	m_center = Vector2(m_size) / 2;
	m_transform.position = m_tileContext.pos - m_camera->GetPosition() + m_center - m_offsetPos;

	//Debug::Log("%f, %f\n", m_transform.position.x, m_transform.position.y);

	m_collider = new BoxCollider(m_size, m_offsetCol);

	m_rigidbody2d.bounciness = 0;


	m_sprite = new Sprite();
	m_sprite->Register(SpriteRegion("ground.jpg", Vector2((m_tileContext.screenStage - 1) * m_tileContext.tileSize, 0)));
	m_sprite->gridSize = m_size;
	

}

void Ground::Update()
{
	m_transform.position = m_tileContext.pos - m_camera->GetPosition() + m_center - Vector2(0, 95);


	if (m_transform.position.x + m_tileContext.tileSize <= Screen::Left)
	{
		Destroy();
	}

}

void Ground::Draw()
{


	
	Actor2D::Draw();
}