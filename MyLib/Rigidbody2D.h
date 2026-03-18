#pragma once
#include "Vector2.h"

class Rigidbody2D
{
public:

	enum class Type
	{
		None,		//なし
		Static,		//静的
		Dynamic,	//動的
		Kinematic,	//キネマティック
	};

	float gravityScale;	//重力の影響度合
	Vector2 velocity;	//速度
	float bounciness;	//反発係数
	float mass;			//質量

private:

	Type m_type;	//剛体の種類


public:
	Rigidbody2D(
		Type type = Type::Dynamic,
		float gravityScale = 1.0f,
		float bounciness = 0.4f,
		float mass = 1.0f
	):
		m_type(type),
		gravityScale(gravityScale),
		velocity(0.0f, 0.0f),
		bounciness(bounciness),
		mass(mass)
	{
	}

	//力の加算
	void AddForce(const Vector2& force) { velocity += force; }

	//速度の取得
	const Vector2 GetVelocity() const { return velocity; }

	//速度の設定
	void SetVelocity(const Vector2 v) { velocity = v; }

	//剛体の種類の取得
	const Type GetBodyType() const { return m_type; }
};