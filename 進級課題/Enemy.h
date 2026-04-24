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

	int m_expReward;	//倒したときの経験値(現在)

	//敵のレベルに応じて全ステータスの上昇をさせる関数
	void LevelUpStatus(int maxLv, int minLv, int maxHp, int minHp, int maxAttack, int minAttack, int maxDefense, int minDefense, int expReward);


	//テキストファイルから読み込んだデータをEnemyData構造体に変換する関数(map → 構造体)
	EnemyData Convert(const std::unordered_map<std::string, std::string>& data);

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
		EnemyData enemyData = EnemyData()
	) :
		Character(anime, gridSize, pos, drawOrder, tag, type)
	{

		Init(enemyData);
	
	}
	Enemy( //画像
		const SpriteRegion& image,
		const Vector2& gridSize = Vector2(),
		const Vector2& pos = Vector2(),
		const int drawOrder = 0,
		Tag tag = Tag::Enemy,
		Rigidbody2D::Type type = Rigidbody2D::Type::Dynamic,
		EnemyData enemyData = EnemyData()
	) :
		Character(image, gridSize, pos, drawOrder, tag, type)
	{

		Init(enemyData);
	
	}
	Enemy(
		const char* textureName,
		const Vector2& pos = Vector2(),
		const int drawOrder = 0,
		Tag tag = Tag::Enemy,
		Rigidbody2D::Type type = Rigidbody2D::Type::Dynamic,
		EnemyData enemyData = EnemyData()
	) :
		Character(textureName, pos, drawOrder, tag, type)
	{

		Init(enemyData);

	}
	Enemy(
		const int drawOrder = 0,
		Tag tag = Tag::Enemy,
		Rigidbody2D::Type type = Rigidbody2D::Type::Dynamic,
		EnemyData enemyData= EnemyData()
	) :
		Enemy(nullptr, Vector2(), drawOrder, tag, type, enemyData)
	{
	}

	int GetExpReward() const { return m_expReward; }


	//初期化をまとめる関数
	void Init(const EnemyData enemy)
	{
		//ステータス初期化
		m_status.InitializeStatus(enemy.Level, enemy.Hp, enemy.Attack, enemy.Defense);

		//敵共通の情報の初期化
		InitializeEnemy(enemy.ExpReward);
	}
};