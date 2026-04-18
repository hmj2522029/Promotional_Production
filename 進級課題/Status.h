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

	int m_exp;            // 経験値
	int m_expToNextLevel; // 次のレベルまでの経験値

	bool m_isDefending;		//防御しているかどうかのフラグ


public:


    Status(int level, int hp, int attack, int defense) :
        m_level(level),
        m_hp(hp),
        m_maxHp(hp),
        m_attack(attack),
        m_defense(defense),
		m_exp(0),
		m_expToNextLevel(level * ExpMultiplier), // 次のレベルまでの経験値はレベル×100
		m_isDefending(false)
    {}

    
	int GetLevel() const { return m_level; }
    int GetHp() const { return m_hp; }
    int GetMaxHp() const { return m_maxHp; }
    int GetAttack() const { return m_attack; }
	int GetDefense() const { return m_defense; }
	bool IsDead() const { return m_hp <= 0; }

    //ダメージ計算
    int CalculateDamage(const Status& target);

	// ダメージを受ける
    void TakeDamage(int damage, bool penetration);

	//即死攻撃
	void InstantDeath();

	//回復する
    void Heal(int amount);

	// 経験値を獲得する
    void GainExp(int amount);

	// レベルアップ
    void LevelUp(int maxHp, int minHp,int maxAttack,int minAttack, int maxDefense, int minDefense);

	// レベルアップ判定
	void CheckLevelUp(int maxHp, int minHp, int maxAttack, int minAttack, int maxDefense, int minDefense);

	//防御しているかどうか
	bool IsDefending() const { return m_isDefending; }

	//防御する・やめる
	void StartDefend() { m_isDefending = true; }
	void EndDefend() { m_isDefending = false; }


};