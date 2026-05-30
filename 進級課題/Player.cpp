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
	m_isDeadAnimeEnds(false),
	m_prevGround(true),
	m_invincibleTime(0),
	m_attackSE(0),
	m_damageSE(0),
	m_jumpSE(0),
	m_landingSE(0),
	m_defenseSE(0),
	m_escapeSE(0)
{

	m_rigidbody2d.velocity.x = 0;


	//ステータスの初期化
	m_status.InitializeStatus(
		PlayerData::GetInstance()->GetPlayerStatus().Level,
		PlayerData::GetInstance()->GetPlayerStatus().MaxHp,
		PlayerData::GetInstance()->GetPlayerStatus().Attack,
		PlayerData::GetInstance()->GetPlayerStatus().Defense,
		PlayerData::GetInstance()->GetPlayerStatus().Exp
	);

	m_transform.position = pos;
	m_rigidbody2d.bounciness = 0;


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

	//SEの読み込み
	m_jumpSE  = SoundLoader::GetInstance()->LoadAndGetId("sound/ジャンプ音.mp3");
	ChangeVolumeSoundMem(100, m_jumpSE);

	m_landingSE = SoundLoader::GetInstance()->LoadAndGetId("sound/着地音.mp3");
	ChangeVolumeSoundMem(100, m_landingSE);

	m_damageSE = SoundLoader::GetInstance()->LoadAndGetId("sound/ダメージ.mp3");
	ChangeVolumeSoundMem(100, m_damageSE);

	m_attackSE = SoundLoader::GetInstance()->LoadAndGetId("sound/攻撃.mp3");
	ChangeVolumeSoundMem(100, m_attackSE);

	m_defenseSE = SoundLoader::GetInstance()->LoadAndGetId("sound/防御音.mp3");
	ChangeVolumeSoundMem(100, m_defenseSE);

	m_escapeSE = SoundLoader::GetInstance()->LoadAndGetId("sound/逃げる.mp3");
	ChangeVolumeSoundMem(100, m_escapeSE);

}

void Player::Release()
{
	Actor2D::Release();

	SoundLoader::GetInstance()->Delete(m_jumpSE);
	SoundLoader::GetInstance()->Delete(m_landingSE);
	SoundLoader::GetInstance()->Delete(m_damageSE);
	SoundLoader::GetInstance()->Delete(m_attackSE);
	SoundLoader::GetInstance()->Delete(m_defenseSE);
	SoundLoader::GetInstance()->Delete(m_escapeSE);



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
		if (m_sprite->isAnimationFinished()) m_isDeadAnimeEnds = true;

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

		//SEを再生
		PlaySoundMem(m_jumpSE, DX_PLAYTYPE_BACK);

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

		//攻撃SEを再生
		PlaySoundMem(m_attackSE, DX_PLAYTYPE_BACK);
		
		m_command.AttackCommand(this, target);

		break;
	case ActionType::Defense:

		//防御SEを再生
		PlaySoundMem(m_defenseSE, DX_PLAYTYPE_BACK);

		m_command.DefenseCommand(this);

		break;
	case ActionType::Escape:

		//逃走SEを再生
		PlaySoundMem(m_escapeSE, DX_PLAYTYPE_BACK);

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

	if(other->GetTag() == Tag::Ground && !m_prevGround)
	{
		//着地音を再生
		PlaySoundMem(m_landingSE, DX_PLAYTYPE_BACK);

	}

	// 落とし穴
	if (other->GetTag() == Tag::Hole)
	{
		//落ちたら即死
		m_status.InstantDeath();
	}

	//トゲ
	if (other->GetTag() == Tag::Spike)
	{
		// 無敵中はダメージを受けない
		if (m_invincibleTime > 0) return;

		// 無敵時間を設定
		m_invincibleTime = InvincibleTime;

		// ダメージを受ける
		m_status.TakeDamage(10);	// 10のダメージを受ける

	}

	if (other->GetTag() == Tag::Enemy)
	{
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

			// 前の状態保存
			m_prevGround = m_isGround;

		}
	}
}
void Player::OnCollisionExit(const Actor2D* other)
{
	// 床
	if (other->GetTag() == Tag::Ground)
	{
		m_isGround = false;

		// 前の状態保存
		m_prevGround = m_isGround;
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

