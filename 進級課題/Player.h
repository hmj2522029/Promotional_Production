#pragma once
#include "MyLib.h"

class Camera;

class Player : public Actor2D
{
private:

	// プレイヤー情報
	static constexpr Vector2 SpawnPos = Vector2(100, 478);	// 初期位置
	static constexpr float InvincibleTime = 1.5f;	// 無敵時間
	static constexpr float JUMP_SCALE = 7.0f;
	static constexpr Vector2 Size = Vector2(32, 32);

	Camera* m_camera;	//カメラ

	Vector2 m_velocity;	//速度
	bool m_isGround;	//地面判定
	
protected:

	void Load() override;
	void Release() override;
	void Update() override;
	void Draw()override;

public:
	Player(Camera* camera);

	int GetX() const { return static_cast<int>(m_transform.position.x); }

	//プレイヤーが進だ距離を取得する関数(1ブロック = 1メートル)
	float GetDistance() const { return m_transform.position.x / 100.0f; }

	// 衝突イベント
	virtual void OnCollisionEnter(const Actor2D* other) override;
	virtual void OnCollision(const Actor2D* other) override;
	virtual void OnCollisionExit(const Actor2D* other) override;


};