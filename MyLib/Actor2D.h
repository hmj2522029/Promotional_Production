#pragma once
#include "Node.h"
#include "Transform.h"
#include "Rigidbody2D.h"
#include "Tag.h"

class Physics2D;
class Collider;


class Actor2D : public Node
{
	friend Physics2D;	//Physics2DがActor内部にアクセスできるようにするため


protected:

	Tag m_tag;				//タグ
	Transform m_transform;	//姿勢情報
	Rigidbody2D m_rigidbody2d;//剛体
	Collider* m_collider;	//衝突形状

	virtual void Load() override;
	virtual void Release() override;
	virtual void Draw() override;

public:

	struct CollisionInfo
	{
		Actor2D* other;
		Vector2 resolve;
	};


	Actor2D(
		Tag tag = Tag::None,
		Rigidbody2D::Type type = Rigidbody2D::Type::Static
	) :
		m_collider(nullptr),
		m_rigidbody2d(type),
		m_tag(tag)
	{
	}

	// ツリー更新(Node)
	virtual void TreeUpdate() override;

	// 姿勢情報の取得
	const Transform& GetTransform() const { return m_transform; }

	// 座標の取得
	const Vector2 GetPosition() const { return m_transform.position; }

	// 座標の設定
	void SetPosition(const Vector2 pos) { m_transform.position = pos; }

	// タグの取得
	const Tag GetTag() const { return m_tag; }

	// 衝突判定の形状を取得
	const Collider* GetCollider() const { return m_collider; }

	// 衝突イベント
	virtual void OnCollisionEnter(const Actor2D* other) {}
	virtual void OnCollision(const Actor2D* other) {}
	virtual void OnCollisionExit(const Actor2D* other) {}


};