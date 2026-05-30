#pragma once
#include "BattleCommand.h"
#include "Character.h"
#include "MyLib.h"
#include "PlayerData.h"

class Camera;
class Enemy;

class Player : public Character
{
public:

	enum class MoveMode
	{
		StageDriven,   // ステージが動く（通常）
		SelfMove       // 自分で動く（クリア前になるとステージを止めるから）
	};

private:

	//画像
	static constexpr Vector2 GridSize = Vector2(95, 84);	//グリッドサイズ

	// プレイヤー情報
	static constexpr Vector2 SpawnPos = Vector2(250, 478);	// 初期位置
	static constexpr float InvincibleTime = 1.5f;			// 無敵時間
	static constexpr float JumpScale = 9.0f;
	static constexpr float Speed = 3.5f;		
	static constexpr Vector2 Size = Vector2(25, 32);

	//レベルアップの時のステータスの上昇値の範囲
	static constexpr int UpHpMax = 10;		//レベルアップの時のHPの上昇値の最大値
	static constexpr int UpHpMin = 5;		//レベルアップの時のHPの上昇値の最小値
	static constexpr int UpAttackMax = 3;	//レベルアップの時の攻撃力の上昇値の最大値
	static constexpr int UpAttackMin = 2;	//レベルアップの時の攻撃力の上昇値の最小値
	static constexpr int UpDefenseMax = 2;	//レベルアップの時の防御力の上昇値の最大値
	static constexpr int UpDefenseMin = 1;	//レベルアップの時の防御力の上昇値の最小値


	Enemy* m_targetEnemy;		//当たった時の対象の敵
	BattleCommand m_command;
	MoveMode m_moveMode;		//移動モード

	bool m_stopUpdating;	//更新を止めるかどうか
	bool m_isGround;		//地面判定
	bool m_hasCollided;		//何かのオブジェクトに衝突しているかどうか(初期位置のずれを直すため)
	bool m_lvelUpFlag;		//レベルアップしているかどうかのフラグ	
	bool m_isDeadAnimeEnds;	//死亡アニメーションが終わっているかのフラグ(シーンの切り替えのタイミングを調整するため)
	bool m_prevGround;		//前のフレームの地面判定
	float m_velocity;		//移動速度
	float m_invincibleTime;	//残りの無敵時間
	int m_jumpSE;			//ジャンプのSE
	int m_landingSE;		//着地のSE
	int m_damageSE;			//ダメージを受けたときのSE
	int m_attackSE;			//攻撃のSE
	int m_defenseSE;		//防御のSE
	int m_escapeSE;			//逃走のSE

	
protected:

	void Load() override;
	void Release() override;
	void Update() override;
	void Draw()override;

public:

	enum class ActionType
	{

		Attack,		//攻撃
		Defense,	//防御
		Escape		//逃走

	};

	//アニメーションデータ
	std::vector<Animation2D> AnimeData;

	Player(Vector2 pos = SpawnPos);

	int GetX() const { return static_cast<int>(m_transform.position.x); }

	//当たった敵を返す
	Enemy* GetTargetEnemy() const { return m_targetEnemy; }

	//当たった敵をリセットする
	void ResetTargetEnemy() { m_targetEnemy = nullptr; }

	//レベルアップフラグの取得
	bool GetLevelUpFlag() { return m_lvelUpFlag; }

	//レベルアップフラグのリセット
	void ResetLevelUpFlag() { m_lvelUpFlag = false; }

	void SetMoveMode(MoveMode mode) { m_moveMode = mode; }

	void PlayDamageSE() { PlaySoundMem(m_damageSE, DX_PLAYTYPE_BACK); }

	//レベルアップしているか
	void LevelUp() { m_status.LevelUp(UpHpMax, UpHpMin, UpAttackMax, UpAttackMin, UpDefenseMax, UpDefenseMin); }

	//プレイヤーの行動
	void ActionSelection(ActionType actionType, Enemy* target);

	//プレイヤーデータをPlayerStatusに変換する関数(ステータスの保管)
	PlayerData::PlayerStatus ToPlayerStatus() const;
	 
	//アップデートを止める関数
	void StopUpdating() { m_stopUpdating = true; }

	//アップデートを再開する関数
	void StartUpdating() { m_stopUpdating = false; }

	//アニメーションの変更(外のクラスからプレイヤーのアニメーションを変えるため)
	void AnimationChange(const char* name, float time = 0) { m_sprite->Play(name, time); }

	//死亡しているかどうかのフラグの取得
	bool IsDeadAnimeEnds() const { return m_isDeadAnimeEnds; }

	// 衝突イベント
	virtual void OnCollisionEnter(const Actor2D* other) override;
	virtual void OnCollision(const Actor2D* other) override;
	virtual void OnCollisionExit(const Actor2D* other) override;



};