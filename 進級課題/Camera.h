#pragma once
#include "MyLib.h"

class Camera : public Actor2D
{
public:
    static constexpr float MOVE_SPEED = 3.0f;
    static constexpr Vector2 Size = Vector2(10, 10);

	Vector2 m_velocity; // カメラの移動速度
	Vector2 m_position; // カメラの位置

protected:

    void Update() override;

public:

    Camera();               // コンストラクタ

    //カメラを止める・動かす
	void Stop() { m_velocity = Vector2(0, 0); }
	void Move() { m_velocity = Vector2(MOVE_SPEED, 0); }

    Vector2 GetPos() const { return m_transform.position; }     // カメラ位置取得
    float GetSpeed() const { return MOVE_SPEED; }

};