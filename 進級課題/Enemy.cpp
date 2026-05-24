#include "Enemy.h"

void Enemy::LevelUpStatus(int lv, StatusIncreaseValue increaseValue)
{
	//レベルアップさせる回数分ループする(レベル1のときはループしない)
	for (int i = 1; i < lv; i++) 
	{

		int MaxHp = GetRand(increaseValue.maxHp - increaseValue.minHp) + increaseValue.minHp;

		m_status.AddLevel(1);	//レベルの上昇値は固定
		m_status.AddMaxHp(MaxHp);	//HPの上昇値はランダム
		m_status.AddAttack(GetRand(increaseValue.maxAttack - increaseValue.minAttack) + increaseValue.minAttack);	//攻撃力の上昇値はランダム
		m_status.AddDefense(GetRand(increaseValue.maxDefense - increaseValue.minDefense) + increaseValue.minDefense);	//防御力の上昇値はランダム

		//最大Hpが上がった時に現在のHpも上げる
		m_status.AddHp(MaxHp);

		//倒したときに貰える経験値もレベルに応じて増やす
		m_expReward += increaseValue.expReward;	//経験値の上昇値は固定
	}

	Debug::Log("Level: %d\n", m_status.GetLevel());
	Debug::Log("Hp: %d\n", m_status.GetHp());
	Debug::Log("Attack: %d\n", m_status.GetAttack());
	Debug::Log("Defense: %d\n", m_status.GetDefense());
	Debug::Log("ExpReward: %d\n", m_expReward);
	Debug::Log("MaxHp: %d\n", m_status.GetMaxHp());

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

void Enemy::EnemyLevelSetting(const EnemyLevelParam param, const StatusIncreaseValue increaseValue, int distance, int levelPerDistance)
{

	//距離から基本レベルを計算する(距離が[m]増えるごとにレベルが1上がる)
	int baseLevel = distance / levelPerDistance;

	//基本レベルに倍率をかけて調整する
	int level = static_cast<int>(baseLevel * param.multiplier);

	//レベルにランダムな補正を加える
	level += GetRand(param.maxOffset - param.minOffset) + param.minOffset;

	//レベルの下限を1にする
	if (level < 1) level = 1;

	Debug::Log("baseLevel: %d\n", baseLevel);
	Debug::Log("level: %d\n", level);

	//敵のレベルに応じてステータスを上昇させる
	LevelUpStatus(
		level, 
		increaseValue
	);

}

