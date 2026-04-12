#pragma once
#include "Vector2.h"

struct SpriteRegion
{
    const char* textureName;
    int textureId;

    Vector2 position; // 切り出し開始位置 (srcX, srcY)

    constexpr SpriteRegion(
        const char* textureName,
        Vector2 pos
    ) : 
        textureName(textureName),
        textureId(0),
        position(pos)
    {
    }
};