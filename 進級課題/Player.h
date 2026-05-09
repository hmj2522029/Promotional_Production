#pragma once
#include "BattleCommand.h"
#include "Character.h"
#include "MyLib.h"
#include "PlayerData.h"

class Camera;
class Enemy;

class Player : public Character
{
private:

	//シーン違いによるプレイヤーの行動の違い
	enum class SceneActionType	
	{
		SceneGame,
		ScenePrep
	};


	//画像
	static constexpr Vector2 GridSize = Vector2(95, 84);	//グリッドサイズ

	// プレイヤー情報
	static constexpr Vector2 SpawnPos = Vector2(250, 478);	// 初期位置
	static constexpr float InvincibleTime = 1.5f;	// 無敵時間
	static constexpr float JumpScale = 8.0f;
	static constexpr Vector2 Size = Vector2(25, 32);

	//レベルアップの時のステータスの上昇値の範囲
	static constexpr int UpHpMax = 10;		//レベルアップの時のHPの上昇値の最大値
	static constexpr int UpHpMin = 5;		//レベルアップの時のHPの上昇値の最小値
	static constexpr int UpAttackMax = 5;	//レベルアップの時の攻撃力の上昇値の最大値
	static constexpr int UpAttackMin = 2;	//レベルアップの時の攻撃力の上昇値の最小値
	static constexpr int UpDefenseMax = 3;	//レベルアップの時の防御力の上昇値の最大値
	static constexpr int UpDefenseMin = 1;	//レベルアップの時の防御力の上昇値の最小値


	Enemy* m_targetEnemy;				//当たった時の対象の敵
	BattleCommand m_command;
	SceneActionType m_sceneActionType;	//シーン違いによるプレイヤーの行動の違い

	bool m_isGround;		//地面判定
	bool m_hasCollided;		//何かのオブジェクトに衝突しているかどうか(初期位置のずれを直すため)
	bool m_lvelUpFlag;		//レベルアップしているかどうかのフラグ	
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

	//アニメーションデータ
	std::vector<Animation2D> AnimeData;


	Player();

	int GetX() const { return static_cast<int>(m_transform.position.x); }

	//当たった敵を返す
	Enemy* GetTargetEnemy() const { return m_targetEnemy; }

	//当たった敵をリセットする
	void ResetTargetEnemy() { m_targetEnemy = nullptr; }

	//レベルアップフラグの取得
	bool GetLevelUpFlag() { return m_lvelUpFlag; }

	//レベルアップフラグのリセット
	void ResetLevelUpFlag() { m_lvelUpFlag = false; }

	//レベルアップしているか
	bool CheckLevelUp() { return m_status.CheckLevelUp(UpHpMax, UpHpMin, UpAttackMax, UpAttackMin, UpDefenseMax, UpDefenseMin); }

	//プレイヤーの行動
	void ActionSelection(ActionType actionType, Enemy* target);

	//プレイヤーデータをPlayerStatusに変換する関数(ステータスの保管)
	PlayerData::PlayerStatus ToPlayerStatus() const;
	 
	// 衝突イベント
	virtual void OnCollisionEnter(const Actor2D* other) override;
	virtual void OnCollision(const Actor2D* other) override;
	virtual void OnCollisionExit(const Actor2D* other) override;


};