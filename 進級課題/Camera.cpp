#include "Camera.h"

Camera::Camera() :
	Actor2D(Tag::None, Rigidbody2D::Type::Kinematic),
	m_velocity(MOVE_SPEED,0),
	m_position(0, 0)
{
	m_transform.position = m_position; // カメラの初期位置を設定

	m_collider = new BoxCollider(Size, Vector2(Size) / 2);

} 

void Camera::Update()
{
	m_transform.position += m_velocity; // カメラの位置を速度に応じて更新


}