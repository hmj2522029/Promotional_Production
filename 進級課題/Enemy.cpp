#include "Enemy.h"


void Enemy::LevelUpStatus(int maxLv, int minLv, int maxHp, int minHp, int maxAttack, int minAttack, int maxDefense, int minDefense, int expReward)
{
	//何回レベルアップさせるかを決める(ランダム)
	int levelUpCount = GetRand(maxLv - minLv) + minLv;	// レベルアップさせる回数はmaxLv～minLvの範囲でランダム



	for (int i = 0; i < levelUpCount; i++)
	{
		m_status.LevelUp(maxHp, minHp, maxAttack, minAttack, maxDefense, minDefense);	//レベルアップさせる

		//倒したときに貰える経験値もレベルに応じて増やす
		m_expReward += expReward;	//経験値の上昇値は固定
	}
}