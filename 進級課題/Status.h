#pragma once

#include "MyLib.h"

class Status
{
private:
	//各ステータスの最大値
	static constexpr int MaxLevel = 100;			//レベルの最大値
	static constexpr int MaxHp = 999;				//HPの最大値
	static constexpr int MaxAttack = 999;			//攻撃力の最大値
	static constexpr int MaxDefense = 999;			//防御力の最大値
	static constexpr int MaxExpToNextLevel = 9999;	//次のレベルまでの経験値の最大値

	//次のレベルまでの経験値の倍率
	static constexpr int ExpMultiplier = 100;

	//ステータスの情報
	int m_level;   // レベル
	int m_hp;      // 現在のHP
	int m_maxHp;   // 現在の最大HP
	int m_attack;  // 攻撃力
	int m_defense; // 防御力

	int m_exp;				// 経験値
	int m_expToNextLevel;	// 次のレベルまでの経験値
	int m_expMultiplier;	// 経験値の倍率

	bool m_isDefending;		//防御しているかどうかのフラグ


public:


	Status() :
		m_level(0),
		m_hp(0),
		m_maxHp(0),
		m_attack(0),
		m_defense(0),
		m_exp(0),
		m_expToNextLevel(0),
		m_expMultiplier(ExpMultiplier),
		m_isDefending(false)
	{
	}

	//各ステータスのゲッター
	int GetLevel() const { return m_level; }
	int GetHp() const { return m_hp; }
	int GetMaxHp() const { return m_maxHp; }
	int GetAttack() const { return m_attack; }
	int GetDefense() const { return m_defense; }
	int GetExp() const { return m_exp; }
	int GetExpToNextLevel() const { return m_expToNextLevel; }

	//各ステータスの加算
	void AddLevel(int amount) { m_level += amount; if (m_level > MaxLevel) { m_level = MaxLevel; } }
	void AddHp(int amount) { m_hp += amount; if (m_hp > m_maxHp) { m_hp = m_maxHp; } }
	void AddMaxHp(int amount) { m_maxHp += amount; if (m_maxHp > MaxHp) { m_maxHp = MaxHp; } }
	void AddAttack(int amount) { m_attack += amount; if (m_attack > MaxAttack) { m_attack = MaxAttack; } }
	void AddDefense(int amount) { m_defense += amount; if (m_defense > MaxDefense) { m_defense = MaxDefense; } }

	bool IsDead() const { return m_hp <= 0; }

	//ステータスを初期化する
	void InitializeStatus(int level, int hp, int attack, int defense, int exp = 0);

	//ダメージ計算
	int CalculateDamage(const Status& target, bool penetration);

	// ダメージを受ける
	void TakeDamage(int damage);

	//即死攻撃
	void InstantDeath();

	//回復する
	void Heal(int amount);

	// 経験値を獲得する
	void GainExp(int amount);

	// レベルアップ(経験値)
	void LevelUp(int maxHp, int minHp, int maxAttack, int minAttack, int maxDefense, int minDefense);

	// レベルアップ判定
	bool CheckLevelUp();

	//防御しているかどうか
	bool IsDefending() const { return m_isDefending; }

	//防御する
	void StartDefend() { m_isDefending = true; }

	//防御をやめる
	void EndDefend() { m_isDefending = false; }

};