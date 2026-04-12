#include "Status.h"

int Status::CalculateDamage(const Status& target)
{
	// ダメージ計算
	int damage = 0;
	//防御をしている時は攻撃力が半減する
	if (target.IsDefending())
	{
		damage = (m_attack / 2) - target.m_defense;	// 防御している場合のダメージ計算
	} 
	else
	{
		damage = m_attack - target.m_defense;		// 通常のダメージ計算
	}

	if (damage < 1) { damage = 1; } // ダメージは1未満にならない
	return damage;
}

void Status::TakeDamage(int damage, bool penetration)
{
	// ダメージ計算
	int actualDamage = 0;
	if(penetration == false) actualDamage = damage - m_defense;	// 貫通攻撃でない場合、防御力を考慮する
	if (penetration == true)  actualDamage = damage;			// 貫通攻撃の場合、防御力を無視する


	if (actualDamage < 1) { actualDamage = 1; } // ダメージは1未満にならない

	m_hp -= actualDamage;

	if (m_hp < 0)
	{
		m_hp = 0;
	}	// HPは0未満にならない
}

void Status::InstantDeath()
{
	m_hp = 0;
}

void Status::Heal(int amount)
{
	m_hp += amount;
	if (m_hp > m_maxHp) { m_hp = m_maxHp; } // HPは最大HPを超えない
}

void Status::GainExp(int amount)
{
	m_exp += amount;
}

void Status::LevelUp(int maxHp, int minHp, int maxAttack, int minAttack, int maxDefense, int minDefense)
{
	m_exp -= m_expToNextLevel; // レベルアップに必要な経験値を減らす
	m_level++;

	int UpHp = GetRand(maxHp - minHp) + minHp;						// レベルアップごとに最大HPがMax～Min増える
	int UpAttack = GetRand(maxAttack - minAttack) + minAttack;		// レベルアップごとに攻撃力がMax～Min増える
	int UpDefense = GetRand(maxDefense - minDefense) + minDefense;	// レベルアップごとに防御力がMax～Min増える

	m_maxHp += UpHp;
	m_attack += UpAttack;
	m_defense += UpDefense;
	m_hp = m_maxHp;					// レベルアップするとHPが全回復する

	m_expToNextLevel = m_level * 100; // 次のレベルまでの経験値が増える

	// ステータスの最大値を超えないようにする
	if (m_level > MaxLevel) { m_level = MaxLevel; }
	if (m_maxHp > MaxHp) { m_maxHp = MaxHp; }
	if (m_attack > MaxAttack) { m_attack = MaxAttack; }
	if (m_defense > MaxDefense) { m_defense = MaxDefense; }
	if (m_expToNextLevel > MaxExpToNextLevel) { m_expToNextLevel = MaxExpToNextLevel; }

}

void Status::CheckLevelUp(int maxHp, int minHp, int maxAttack, int minAttack, int maxDefense, int minDefense)
{
	while (m_exp >= m_expToNextLevel)
	{
		LevelUp(maxHp, minHp, maxAttack, minAttack, maxDefense, minDefense);
	}
}
