#pragma once
#include "Character.h"
#include <vector>

class Enemy : public Character
{
protected:

	//敵のステータス情報(テキストファイル読み込み用の仮のデータ)
	struct EnemyData
	{
		int Level = 0;		//レベル(初期)		
		int Hp = 0;			//HP(初期)
		int Attack = 0;		//攻撃力(初期)
		int Defense = 0;	//防御力(初期)
		int ExpReward = 0;	//倒したときの経験値(初期)
	};

	//敵のレベルアップによるステータスの上昇値(EnemyLevelSettingで使う用)
	struct StatusIncreaseValue
	{
		int maxHp = 0;
		int minHp = 0;
		int maxAttack = 0;
		int minAttack = 0;
		int maxDefense = 0;
		int minDefense = 0;
		int expReward = 0;
	};

	//距離によってレベルを変えるためのパラメータ
	struct EnemyLevelParam
	{
		float multiplier = 0; // 成長倍率
		int minOffset = 0;    // 最低補正
		int maxOffset = 0;    // 最大補正
	};

	int m_expReward;			//倒したときの経験値(現在)

	//敵のレベルに応じて全ステータスの上昇をさせる関数
	void LevelUpStatus(int lv, StatusIncreaseValue increaseValue);

	//テキストファイルから読み込んだデータをEnemyData構造体に変換する関数(map → 構造体)
	EnemyData Convert(const std::unordered_map<std::string, std::string>& data);


	//距離に応じて敵のレベルを設定する関数
	void EnemyLevelSetting(EnemyLevelParam param, StatusIncreaseValue increaseValue, int distance, int levelPerDistance);

	//敵共通の情報の初期化
	void InitializeEnemy(int expReward) { m_expReward = expReward; }

public:

	Enemy( //アニメーション
		const Animation2D& anime,
		const Vector2& gridSize,
		const Vector2& pos = Vector2(),
		const int drawOrder = 0,
		Tag tag = Tag::Enemy,
		Rigidbody2D::Type type = Rigidbody2D::Type::Dynamic,
		EnemyData enemyData = EnemyData(),
		StatusIncreaseValue statusIncreaseValue = StatusIncreaseValue(),
		EnemyLevelParam enemyLevelParam = EnemyLevelParam(),
		const int distance = 0,
		const int levelPerDistance = 10
	) :
		Character(anime, gridSize, pos, drawOrder, tag, type)
	{

		Init(enemyData, statusIncreaseValue, enemyLevelParam, distance, levelPerDistance);
	
	}
	Enemy( //画像
		const SpriteRegion& image,
		const Vector2& gridSize = Vector2(),
		const Vector2& pos = Vector2(),
		const int drawOrder = 0,
		Tag tag = Tag::Enemy,
		Rigidbody2D::Type type = Rigidbody2D::Type::Dynamic,
		EnemyData enemyData = EnemyData(),
		StatusIncreaseValue statusIncreaseValue = StatusIncreaseValue(),
		EnemyLevelParam enemyLevelParam = EnemyLevelParam(),
		const int distance = 0,
		const int levelPerDistance = 10
	) :
		Character(image, gridSize, pos, drawOrder, tag, type)
	{
		Init(enemyData, statusIncreaseValue, enemyLevelParam, distance, levelPerDistance);

	}
	Enemy(
		const char* textureName,
		const Vector2& pos = Vector2(),
		const int drawOrder = 0,
		Tag tag = Tag::Enemy,
		Rigidbody2D::Type type = Rigidbody2D::Type::Dynamic,
		EnemyData enemyData = EnemyData(),
		StatusIncreaseValue statusIncreaseValue = StatusIncreaseValue(),
		EnemyLevelParam enemyLevelParam = EnemyLevelParam(),
		const int distance = 0,
		const int levelPerDistance = 10
	) :
		Character(textureName, pos, drawOrder, tag, type)
	{

		Init(enemyData, statusIncreaseValue, enemyLevelParam, distance, levelPerDistance);

	}
	Enemy(
		const int drawOrder = 0,
		Tag tag = Tag::Enemy,
		Rigidbody2D::Type type = Rigidbody2D::Type::Dynamic,
		EnemyData enemyData= EnemyData(),
		StatusIncreaseValue statusIncreaseValue = StatusIncreaseValue(),
		EnemyLevelParam enemyLevelParam = EnemyLevelParam(),
		const int distance = 0,
		const int levelPerDistance = 10
	) :
		Enemy(
			nullptr,
			Vector2(), 
			drawOrder,
			tag,
			type,
			enemyData,
			statusIncreaseValue,
			enemyLevelParam,
			distance,
			levelPerDistance
		)
	{
	}

	int GetExpReward() const { return m_expReward; }

	//初期化をまとめる関数
	void Init(const EnemyData enemy, const StatusIncreaseValue increaseValue, const EnemyLevelParam enemyLevelParam, const int distance, const int levelPerDistance)
	{
		//ステータス初期化
		m_status.InitializeStatus(enemy.Level, enemy.Hp, enemy.Attack, enemy.Defense);

		//敵共通の情報の初期化
		InitializeEnemy(enemy.ExpReward);

		//レベル設定
		EnemyLevelSetting(enemyLevelParam, increaseValue, distance, levelPerDistance);
	}
};