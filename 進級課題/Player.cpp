#include "Player.h"
#include "DxLib.h"
#include "Camera.h"
#include "Enemy.h"



Player::Player(Camera* camera):
	Character(Tag::Player, Rigidbody2D::Type::Dynamic, Level, Hp, Attack, Defense),
	m_camera(camera),
	m_targetEnemy(nullptr),
	m_isGround(false),
	m_invincibleTime(0)
{

	m_transform.position = SpawnPos - m_camera->GetPosition();

	m_collider = new BoxCollider(Size);
	m_collider->SetPhysicsBehavior(Tag::Hole, PhysicsBehavior::Trigger);
	m_collider->SetPhysicsBehavior(Tag::Spike, PhysicsBehavior::Trigger);
	m_collider->SetPhysicsBehavior(Tag::Enemy, PhysicsBehavior::Trigger);

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
	//死んでいたら更新しない
	if (m_status.IsDead()) return;

	//レベルアップのチェック
	m_status.CheckLevelUp(10, 5, 3, 1, 2, 1);
	

		// 無敵時間のカウントダウン
	if (m_invincibleTime > 0)
	{
		m_invincibleTime -= Time::GetInstance()->GetDeltaTime();
	}


	//操作
	if (Keyboard::isDown(KEY_INPUT_SPACE) && m_isGround)
	{
		m_rigidbody2d.AddForce(Vector2(0, -1) * JUMP_SCALE);

		m_isGround = false;
	}


}

void Player::Draw()
{
	// 無敵時間中は表示/非表示を繰り返して点滅させる
	if (m_invincibleTime > 0)
	{
		// 無敵時間の小数点第一位が奇数なら非表示
		if (static_cast<int>(m_invincibleTime * 10) % 2)
		{
			return;
		}
	}


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

void Player::ActionSelection(ActionType actionType, Enemy* enemy)
{

	switch (actionType)
	{
		
	case ActionType::Attack:

		m_command.AttackCommand(this, enemy);

		break;
	case ActionType::Defense:

		m_command.DefenseCommand(this);

		break;
	case ActionType::Escape:

		m_command.EscapeCommand(this);

		break;
	}


}


// 衝突イベント
void Player::OnCollisionEnter(const Actor2D* other)
{
	// 落とし穴
	if (other->GetTag() == Tag::Hole)
	{
		Debug::Log("落ちた");

		//落ちたら即死
		m_status.InstantDeath();
	}

	//トゲ
	if (other->GetTag() == Tag::Spike)
	{
		Debug::Log("トゲに当たった");

		// 無敵中はダメージを受けない
		if (m_invincibleTime > 0) return;

		// 無敵時間を設定
		m_invincibleTime = InvincibleTime;

		// ダメージを受ける
		m_status.TakeDamage(10, true);	// 10のダメージを受ける

	}

	if (other->GetTag() == Tag::Enemy)
	{
		Debug::Log("敵に当たった");

		//対象の敵を保存する
		m_targetEnemy = const_cast<Enemy*>(dynamic_cast<const Enemy*>(other));

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

