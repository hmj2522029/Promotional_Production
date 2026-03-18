#pragma once
#include "Collider.h"
#include "DxLib.h"
#include "Vector2.h"


class BoxCollider : public Collider
{
public:

	Vector2 size;   // サイズ


    BoxCollider(const Vector2& size, const Vector2& offset = Vector2()) :
		Collider(offset),
        size(size)
    {}

	Vector2 GetSize() const { return size; }


    // 衝突判定
    // ダブルディスパッチによる形状識別を行う
    virtual Collision::HitInfo CheckCollision(const Transform& t1, const Transform& t2, const Collider* col2) const override
    {
        return col2->CheckCollision(t2, t1, this);
    }
    virtual Collision::HitInfo CheckCollision(const Transform& t1, const Transform& t2, const BoxCollider* col2) const override
    {
        // 矩形×矩形
        return Collision::BoxVsBox(t1, this, t2, col2);

    }


#ifdef _DEBUG

    virtual void Draw(const Transform& t) const override
    {
        DrawBoxAA(
        	t.position.x + offset.x * t.scale - size.x * t.scale / 2,
        	t.position.y + offset.y * t.scale - size.y * t.scale / 2,
        	t.position.x + offset.x * t.scale + size.x * t.scale / 2,
        	t.position.y + offset.y * t.scale + size.y * t.scale / 2,
        	GetColor(0, 255, 0),
        	false
        );
    }

#endif

};