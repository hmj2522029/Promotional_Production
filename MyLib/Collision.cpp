#include "Collision.h"
#include "BoxCollider.h"
#include "Transform.h"
#include <cmath>

//矩形
Collision::Box::Box(const Transform& t, const BoxCollider* col) :
    center(t.position + col->offset),
    width(col->size.x* t.scale),
    height(col->size.y* t.scale)
{
}

const Collision::HitInfo Collision::BoxVsBox(
    const Transform& t1, const BoxCollider* a, 
    const Transform& t2, const BoxCollider* b)
{
	HitInfo info;

    Box boxA = Box(t1, a);
    Box boxB = Box(t2, b);

    Vector2 d = boxA.center - boxB.center;   //中心距離

    //(当たる限界距離 - 実際の距離 = めり込み量)
    float overlapX = (boxA.width + boxB.width) / 2 - std::abs(d.x);    //X方向のめり込み量
    float overlapY = (boxA.height + boxB.height) / 2 - std::abs(d.y);  //Y方向のめり込み量


    // 軸が重なっていない(当っていない)
    if (overlapX <= 0 || overlapY <= 0)
    {
        info.isHit = false;
        return info;    //めり込んでいないから押し出しベクトルは0のまま
    }

	info.isHit = true;

	// めり込み量の小さい方の軸を押し出し方向にする
    if (overlapX < overlapY)
    {
        info.resolve.x = (d.x < 0) ? -overlapX : overlapX;  //めり込んだ方向(左右)から押し出す
    }
    else
    {
		info.resolve.y = (d.y < 0) ? -overlapY : overlapY;  //めり込んだ方向(上下)から押し出す
    }

    return info;
}
