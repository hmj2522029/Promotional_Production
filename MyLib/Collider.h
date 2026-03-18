#pragma once
#include "Transform.h"
#include "PhysicsBehavior.h"
#include "Tag.h"
#include "Collision.h"
#include "Vector2.h"
#include <array>

class BoxCollider;

class Collider
{

private:

	std::array<PhysicsBehavior, static_cast<int>(Tag::Length)>	//C++での代わりの配列
		m_physicsBehavior;

public:
	Vector2 offset;

	Collider(const Vector2& offset) :
		m_physicsBehavior{ PhysicsBehavior::Collision }, //全てのタグに対して、デフォルトは衝突するようにする
		offset(offset)
	{
	}


	// 物理挙動の設定と取得
	PhysicsBehavior GetPhysicsBehavior(Tag tag) const
	{
		return m_physicsBehavior[static_cast<int>(tag)];
	}

	void SetPhysicsBehavior(Tag tag, PhysicsBehavior behavior)
	{
		m_physicsBehavior[static_cast<int>(tag)] = behavior;
	}

	// 衝突判定
	// ダブルディスパッチによる形状識別を行う
	virtual Collision::HitInfo CheckCollision(const Transform& t1, const Transform& t2, const Collider* col2) const = 0;
	virtual Collision::HitInfo CheckCollision(const Transform& t1, const Transform& t2, const BoxCollider* col2) const = 0;


#ifdef _DEBUG

    virtual void Draw(const Transform& transform) const = 0;

#endif 


};