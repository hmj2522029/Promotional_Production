#pragma once
#include "Vector2.h"

class Transform
{
public:

	Vector2 position;

	//今は使わないけどいつか使うかもしれないから
	float angle;		// 角度（ラジアン）
	float scale;		// 拡縮

	Transform() :
		position(0.0f, 0.0f),
		angle(0),
		scale(1)
	{
	}

};