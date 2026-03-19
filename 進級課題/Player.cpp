#include "Player.h"
#include "DxLib.h"
#include "Camera.h"



Player::Player(Camera* camera):
	Actor2D( Tag::Player, Rigidbody2D::Type::Dynamic),
	m_camera(camera),
	m_isGround(false)
{

	m_transform.position = SpawnPos - m_camera->GetPosition();

	m_collider = new BoxCollider(Size);
	m_collider->SetPhysicsBehavior(Tag::Hole, PhysicsBehavior::Trigger);

	m_rigidbody2d.gravityScale = 1.6f;

}

void Player::Load()
{
	Actor2D::Load();



}

void Player::Release()
{
	Actor2D::Release();



}

void Player::Update()
{
	
	int a = static_cast<int>(m_transform.position.y);
	//Debug::Log("%d \n", a);

	//操作
	if (Keyboard::isDown(KEY_INPUT_SPACE) && m_isGround)
	{
		m_rigidbody2d.AddForce(Vector2(0, -1) * JUMP_SCALE);

		m_isGround = false;
	}


}

void Player::Draw()
{

	DrawBoxAA(
		m_transform.position.x - Size.x / 2,
		m_transform.position.y - Size.y / 2,
		m_transform.position.x + Size.x / 2,
		m_transform.position.y + Size.y / 2,
		GetColor(0, 0, 255),
		true
	);

	// Actor2D本来の描画処理
	Actor2D::Draw();

}

// 衝突イベント
void Player::OnCollisionEnter(const Actor2D* other)
{
	// 落とし穴
	if (other->GetTag() == Tag::Hole)
	{
		Debug::Log("落ちた");
	}

}
void Player::OnCollision(const Actor2D* other)
{
	// 床
	if (other->GetTag() == Tag::Ground)
	{
		float playerBottom = m_transform.position.y + Size.y / 2;
		float groundTop = other->GetTransform().position.y;

		// 上から乗ってる判定
		if (m_rigidbody2d.velocity.y >= 0 &&
			playerBottom <= groundTop + 5.0f) 
		{
			m_isGround = true;
		}
	}
}
void Player::OnCollisionExit(const Actor2D* other)
{
	// 床
	if (other->GetTag() == Tag::Ground)
	{
		m_isGround = false;
	}
}

