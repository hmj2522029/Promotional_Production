#pragma once
#include <cmath>	//数学関数ライブラリ 使える例 sqrt()(平方根) : abs()(絶対値) : pow()(べき乗) など

class Vector2
{
	public:

	//定数
	float x;	// X成分
	float y;	// Y成分

	//コンストラクタ
	Vector2() :
		x(0), 
		y(0) 
	{}

	template<typename T1, typename T2>	//ジェネリックコンストラクタ(異なる型の引数を受け取ることができる)
	constexpr Vector2(T1 x, T2 y) :
		x(static_cast<float>(x)),
		y(static_cast<float>(y)) {
	}

	// ベクトルの加算(足し算)
	constexpr Vector2 operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}
	constexpr Vector2& operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	// ベクトルの減算(引き算)
	constexpr Vector2 operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}
	constexpr Vector2& operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	// ベクトルのスカラー乗算(掛け算)
	constexpr Vector2 operator*(float scalar) const
	{
		return Vector2(x * scalar, y * scalar);
	}
	constexpr friend Vector2 operator*(const float& scalar, const Vector2& v)
	{
		return v * scalar;
	}
	constexpr Vector2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	} 

	// ベクトルのスカラー除算(割り算)
	constexpr Vector2 operator/(float scalar) const
	{
		return Vector2(x / scalar, y / scalar);
	}
	constexpr Vector2& operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	// ベクトルの等価比較(イコール)
	bool operator==(const Vector2& other) const
	{
		const float epsilon = 0.00001f;	// 浮動小数点数の誤差を考慮して、ある程度の範囲内で等しいとみなす

		return
			std::abs(x - other.x) < epsilon &&
			std::abs(y - other.y) < epsilon;
	}

	// ベクトルの非等価比較(ノットイコール)
	bool operator!=(const Vector2& other) const
	{
		return !(*this == other);
	}


	//ベクトル関数

	//ベクトルの長さの二乗(三平方の定理)(この関数がある理由 : std::sqrtは重く距離比較とかならSqrMagnitude()で十分だから)
	constexpr float SqrMagnitude() const
	{
		return x * x + y * y;
	}

	// ベクトルの長さを計算(sqrt() 平方根)
	float Magnitude() const
	{
		return std::sqrt(SqrMagnitude());
	}

	// ベクトルを正規化(方向ベクトル)
	Vector2 Normalized() const
	{
		float length = Magnitude();

		if (length <= 0.000001f) return Vector2(0, 0); // 長さが0の場合はゼロベクトルを返す

		return Vector2(x / length, y / length);
	}

	// ベクトルの内積を計算(方向の一致	1: 同じ方向 0: 直角 -1: 逆方向(正規化している場合))
	static constexpr float Dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	static constexpr Vector2 Zero()
	{
		return Vector2(0.0f, 0.0f);
	}

	// ここから下は「将来追加したい機能」(自分が調べた中であったらいいなと思う関数)
	// 
	// TODO: 外積
	// static float Cross(const Vector2& a, const Vector2& b);

	// TODO: 2つのベクトルの距離
	// static float Distance(const Vector2& a, const Vector2& b);

	// TODO: 距離の2乗（高速版）
	// static float SqrDistance(const Vector2& a, const Vector2& b);

	// TODO: 反射ベクトル
	// static Vector2 Reflect(const Vector2& direction, const Vector2& normal);

	// TODO: 線形補間（Lerp）
	// static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);

	// TODO: ベクトル回転
	// Vector2 Rotate(float rad);

	// TODO: ベクトルを角度に変換
	// float ToAngle();

};