#include "Enemy.h"
#include "Camera.h"

Enemy::Enemy(const TileContext& tile, Camera* camera) :
	Actor2D(Tag::Enemy, Rigidbody2D::Type::Dynamic),
	m_camera(camera),
	m_tileContext(tile)
{

}

void Enemy::Update()
{


}

void Enemy::Draw()
{


	Actor2D::Draw();
}