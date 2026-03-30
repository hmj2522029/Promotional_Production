#pragma once
#pragma once
#include "Math.hpp"

// https://easings.net/ja(イージングのURL)
//https://toburau.hatenablog.jp/entry/20180510/1525948672 (LerpのURL)

// 2つの値の間を補間
class Easing
{
public:

    //イージングのタイプ
    enum EasingType
    {
        Line,
        InCubic,
        OutCubic,
        InOutCubic
    };


    //基本
    static float Linear(float t)
    {
        return Math::Clamp01(t);
    }

    //Cubic
    static float EaseInCubic(float t)
    {
        t = Math::Clamp01(t);
        return t * t * t;
    }

    static float EaseOutCubic(float t)
    {
        t = Math::Clamp01(t);
        return 1 - (1 - t) * (1 - t) * (1 - t);
    }

    static float EaseInOutCubic(float t)
    {
        t = Math::Clamp01(t);
        return (t < 0.5f)
            ? 4 * t * t * t
            : 1 - powf(-2 * t + 2, 3) / 2;
    }

};

