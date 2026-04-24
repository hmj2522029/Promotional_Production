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


Enemy::EnemyData Enemy::Convert(const std::unordered_map<std::string, std::string>& data)
{
	//マップから特定のキーの値を整数に変換して取得するラムダ関数
    auto getInt = [&](const std::string& key, int defaultValue = 0) //ラムダ関数(その場で無名関数を作る)
        {
			if (data.count(key)) return std::stoi(data.at(key));    //キーが存在する場合はを整数に変換して返す(std::stoi)

            return defaultValue;   
        };

	EnemyData enemy;

	//stringからintに変換してEnemyDataに格納(std::stoi)
	enemy.Level = getInt("Level");
	enemy.Hp = getInt("Hp");
	enemy.Attack = getInt("Attack");
	enemy.Defense = getInt("Defense");
	enemy.ExpReward = getInt("ExpReward");
    //もしステータスが増えたらここに追加する



    return enemy;
}