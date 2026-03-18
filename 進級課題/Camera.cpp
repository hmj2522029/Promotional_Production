#include "Camera.h"

Camera::Camera() :
	Actor2D(Tag::None, Rigidbody2D::Type::Kinematic),
	m_velocity(MOVE_SPEED,0),
	m_position(0, 0)
{
	m_transform.position = m_position; // ƒJƒƒ‰‚Ì‰ŠúˆÊ’u‚ğİ’è

	m_rigidbody2d.velocity = m_velocity;

	m_collider = new BoxCollider(Size, Vector2(Size) / 2);

} 

void Camera::Update()
{




}