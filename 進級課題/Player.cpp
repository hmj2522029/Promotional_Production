#include "Player.h"
#include "DxLib.h"
#include "Camera.h"
#include "Enemy.h"



Player::Player(Vector2 pos):
	Character(DrawLayer::PlayerLayer , Tag::Player, Rigidbody2D::Type::Dynamic),
	m_moveMode(MoveMode::StageDriven),
	m_velocity(Speed),
	m_stopUpdating(false),
	m_targetEnemy(nullptr),
	m_isGround(false),
	m_hasCollided(false),
	m_lvelUpFlag(false),
	m_isDead(false),
	m_invincibleTime(0)
{

	m_rigidbody2d.velocity.x = 0;

	Debug::Log("velocity: %d\n", m_velocity);

	//ステータスの初期化
	m_status.InitializeStatus(
		PlayerData::GetInstance()->GetPlayerStatus().Level,
		PlayerData::GetInstance()->GetPlayerStatus().MaxHp,
		PlayerData::GetInstance()->GetPlayerStatus().Attack,
		PlayerData::GetInstance()->GetPlayerStatus().Defense,
		PlayerData::GetInstance()->GetPlayerStatus().Exp
	);

	m_transform.position = pos;

	m_collider = new BoxCollider(Size);
	m_collider->SetPhysicsBehavior(Tag::Hole, PhysicsBehavior::Trigger);
	m_collider->SetPhysicsBehavior(Tag::Spike, PhysicsBehavior::Trigger);
	m_collider->SetPhysicsBehavior(Tag::Enemy, PhysicsBehavior::Trigger);

	m_rigidbody2d.gravityScale = 1.6f;

	//アニメデータ
	AnimeData =
	{
		Animation2D("Idle", "Knight 2D Pixel Art/with_outline/IDLE.png", 7, 5, true),
		Animation2D("Run", "Knight 2D Pixel Art/with_outline/RUN.png", 8, 10, true),
		Animation2D("Die", "Knight 2D Pixel Art/with_outline/DEATH.png", 12, 12, false),
		Animation2D("Jump", "Knight 2D Pixel Art/with_outline/JUMP.png", 5, 5, false),
	};

	

	// Sprite起動
	m_sprite = new Sprite();
	for (const auto& anime : AnimeData)
	{
		m_sprite->Register(anime);
	}
	m_sprite->gridSize = GridSize;

	m_transform.scale = 2.0f;

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

	//アップデートを止めている場合は更新しない
	if (m_stopUpdating) return;

	//死んでいたら更新しない
	if (m_status.IsDead())
	{
		//カメラを止める
		Camera::GetInstance()->StopPlayer();

		//アニメーションを再生する(死亡)
		m_sprite->Play("Die", 0.0f);

		//アニメーションが終了したら、死亡フラグを立てる
		if (m_sprite->isAnimationFinished()) m_isDead = true;

		return;
	}
	else if (m_isGround)
	{

		//アニメーションを再生する(走る)
		m_sprite->Play("Run", 0.0f);


		//プレイヤーが動いていないなら、アニメーションを再生する(待機)
		if (!Camera::GetInstance()->IsMovingPlayer())
		{
			m_sprite->Play("Idle", 0.0f);
		}

	}

	//レベルアップ
	if (m_status.CheckLevelUp())
	{
		//シーンの追加はシーンゲームの方で行う
		m_lvelUpFlag = true;
	}


	// 無敵時間のカウントダウン
	if (m_invincibleTime > 0)
	{
		m_invincibleTime -= Time::GetInstance()->GetDeltaTime();
	}


	//ジャンプ
	if (Keyboard::isDown(KEY_INPUT_SPACE) && m_isGround)
	{
		m_rigidbody2d.AddForce(Vector2(0, -1) * JumpScale);


		//アニメーションを再生する(ジャンプ)
		m_sprite->Play("Jump", 0.0f);

		m_isGround = false;
	}

	if (m_moveMode == MoveMode::StageDriven)
	{
		//もし過去に何かのオブジェクトに衝突していて、現在の位置が初期位置と違う場合、初期位置に戻るようにする
		if (m_hasCollided)
		{
	
			//地面についていない場合は、初期位置に戻さない
			if (!m_isGround) return;
	
			float direction = SpawnPos.x - m_transform.position.x;
	
			//float問題を回避するための閾値を1.0fとする
			if (abs(direction) > 1.0f)
			{
	
				m_transform.position.x += (SpawnPos.x - m_transform.position.x) * 0.05f;
	
			}
			else
			{
				m_transform.position.x = SpawnPos.x;
				m_hasCollided = false;
			}
	
		}
	}
	else if (m_moveMode == MoveMode::SelfMove)
	{

		m_rigidbody2d.velocity.x = m_velocity;
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


	// Actor2D本来の描画処理
	Actor2D::Draw();

}

void Player::ActionSelection(ActionType actionType, Enemy* target)
{

	//行動したら行動できないようにする
	if (isAction()) return;

	switch (actionType)
	{
		
	case ActionType::Attack:

		m_command.AttackCommand(this, target);

		break;
	case ActionType::Defense:

		m_command.DefenseCommand(this);

		break;
	case ActionType::Escape:

		m_command.EscapeCommand(this);

		break;
	}


}


PlayerData::PlayerStatus Player::ToPlayerStatus() const
{
	PlayerData::PlayerStatus status;

	status.Level = m_status.GetLevel();
	status.MaxHp = m_status.GetMaxHp();
	status.Attack = m_status.GetAttack();
	status.Defense = m_status.GetDefense();
	status.Exp = m_status.GetExp();
	status.NextExp = m_status.GetExpToNextLevel();

	return status;
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
		m_status.TakeDamage(10);	// 10のダメージを受ける

	}

	if (other->GetTag() == Tag::Enemy)
	{
		Debug::Log("敵に当たった");

		//当たった敵を保存する
		Enemy* enemy = dynamic_cast<Enemy*>(const_cast<Actor2D*>(other));
		if (enemy)
		{
			m_targetEnemy = enemy;
		}
	}


}
void Player::OnCollision(const Actor2D* other)
{
	// 床
	if (other->GetTag() == Tag::Ground)
	{
		float playerBottom = m_transform.position.y + Size.y / 2;
		float groundTop = other->GetTransform().position.y + 40;

		// 上から乗ってる判定
		if (m_rigidbody2d.velocity.y >= 0 &&
			playerBottom <= groundTop + 1.0f) 
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


	//タグを取得して、衝突判定の形状を取得する
	auto tag = other->GetTag();
	auto behavior = other->GetCollider()->GetPhysicsBehavior(tag);

	//衝突判定の形状が衝突の場合、衝突していた(過去形)とする
	if (behavior == PhysicsBehavior::Collision)
	{
		
		float playerBottom = m_transform.position.y + Size.y / 2;
		float groundTop = other->GetTransform().position.y;
	
		//もし衝突オブジェクトに上から乗っている場合は、初期位置はずれないのでreturnする
		if (m_rigidbody2d.velocity.y >= 0 &&
			playerBottom <= groundTop + 5.0f)
		{
			return;
		}
	
		m_hasCollided = true;
	}


}

