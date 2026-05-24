#pragma once
#include "MyLib.h"

class HitBox : public Actor2D
{
public:
	HitBox(
		const Vector2& position,
		const Vector2& size,
		Tag tag = Tag::None,
		Rigidbody2D::Type body = Rigidbody2D::Type::Static
	) :
		Actor2D(nullptr, position, 0, tag, body)
	{
		m_collider = new BoxCollider(size);
		m_rigidbody2d.bounciness = 0;
	}

};