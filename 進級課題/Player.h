#pragma once
#include "BattleCommand.h"
#include "Character.h"
#include "MyLib.h"

class Camera;
class Enemy;

class Player : public Character
{
private:

	// プレイヤー情報
	static constexpr Vector2 SpawnPos = Vector2(250, 478);	// 初期位置
	static constexpr float InvincibleTime = 1.5f;	// 無敵時間
	static constexpr float JUMP_SCALE = 7.0f;
	static constexpr Vector2 Size = Vector2(32, 32);

	//ステータス情報(初期)
	static constexpr int Level = 1;		//レベル(初期)
	static constexpr int Hp	= 50;		//HP(初期)
	static constexpr int Attack = 10;	//攻撃力(初期)
	static constexpr int Defense = 5;	//防御力(初期)

	//レベルアップの時のステータスの上昇値の範囲
	static constexpr int UpHpMax = 10;		//レベルアップの時のHPの上昇値の最大値
	static constexpr int UpHpMin = 5;		//レベルアップの時のHPの上昇値の最小値
	static constexpr int UpAttackMax = 5;	//レベルアップの時の攻撃力の上昇値の最大値
	static constexpr int UpAttackMin = 2;	//レベルアップの時の攻撃力の上昇値の最小値
	static constexpr int UpDefenseMax = 3;	//レベルアップの時の防御力の上昇値の最大値
	static constexpr int UpDefenseMin = 1;	//レベルアップの時の防御力の上昇値の最小値


	Camera* m_camera;		//カメラ
	Enemy* m_targetEnemy;	//当たった時の対象の敵
	BattleCommand m_command;

	bool m_isGround;		//地面判定
	float m_invincibleTime;	//残りの無敵時間
	
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

	Player(Camera* camera);

	int GetX() const { return static_cast<int>(m_transform.position.x); }

	//当たった敵を返す
	Enemy* GetTargetEnemy() const { return m_targetEnemy; }

	//プレイヤーの行動
	void ActionSelection(ActionType actionType);

	// 衝突イベント
	virtual void OnCollisionEnter(const Actor2D* other) override;
	virtual void OnCollision(const Actor2D* other) override;
	virtual void OnCollisionExit(const Actor2D* other) override;


};