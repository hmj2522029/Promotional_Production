#pragma once
#include "Vector2.h"

class Transform;
class BoxCollider;


//衝突判定
class Collision
{
public:

	// 矩形
	struct Box
	{
		Vector2 center;		// 中央座標X
		float width;		// 幅
		float height;		// 高さ

		Box(const Transform& t, const BoxCollider* col);
	};


	//衝突の結果をまとめて返すための入れ物(拡張する時に返す値が一つじゃ足りなくなるから)
	struct HitInfo
	{
		bool isHit;

		//押し出しベクトル
		Vector2 resolve;

		HitInfo() :	//何も当たっていない状態をデフォルトにするため
			resolve(0.0f, 0.0f),
			isHit(false)
		{ }
	};

	//矩形×矩形
	static const HitInfo BoxVsBox(
		const Transform& t1, const BoxCollider* a, 
		const Transform& t2, const BoxCollider* b
	);

};