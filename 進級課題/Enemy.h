#pragma once
#include "Character.h"

class Enemy : public Character
{
protected:
	//敵が共通して持つ情報や機能をここに書く
	int m_expReward;	//倒したときにプレイヤーが得る経験値

	//敵のレベルに応じて全ステータスの上昇をさせる関数
	void LevelUpStatus(int maxLv, int minLv, int maxHp, int minHp, int maxAttack, int minAttack, int maxDefense, int minDefense, int expReward);

public:

	Enemy( //アニメーション
		const Animation2D& anime,
		const Vector2& gridSize,
		const Vector2& pos = Vector2(),
		const int drawOrder = 0,
		Tag tag = Tag::Enemy,
		Rigidbody2D::Type type = Rigidbody2D::Type::Dynamic,
		int Lv = 0,
		int Hp = 0,
		int attack = 0,
		int defense = 0,
		int expReward = 0
	) :
		Character(anime, gridSize, pos, drawOrder, tag, type, Lv, Hp, attack, defense),
		m_expReward(expReward)
	{
	}
	Enemy( //画像
		const SpriteRegion& image,
		const Vector2& gridSize = Vector2(),
		const Vector2& pos = Vector2(),
		const int drawOrder = 0,
		Tag tag = Tag::Enemy,
		Rigidbody2D::Type type = Rigidbody2D::Type::Dynamic,
		int Lv = 0,
		int Hp = 0,
		int attack = 0,
		int defense = 0,
		int expReward = 0
	) :
		Character(image, gridSize, pos, drawOrder, tag, type, Lv, Hp, attack, defense),
		m_expReward(expReward)
	{
	}
	Enemy(
		const char* textureName,
		const Vector2& pos = Vector2(),
		const int drawOrder = 0,
		Tag tag = Tag::Enemy,
		Rigidbody2D::Type type = Rigidbody2D::Type::Dynamic,
		int Lv = 0,
		int Hp = 0,
		int attack = 0,
		int defense = 0,
		int expReward = 0
	) :
		Character(textureName, pos, drawOrder, tag, type, Lv, Hp, attack, defense),
		m_expReward(expReward)
	{
	}
	Enemy(
		const int drawOrder = 0,
		Tag tag = Tag::Enemy,
		Rigidbody2D::Type type = Rigidbody2D::Type::Dynamic,
		int Lv = 0,
		int Hp = 0,
		int attack = 0,
		int defense = 0,
		int expReward = 0
	) :
		Enemy(nullptr, Vector2(), drawOrder, tag, type, Lv, Hp, attack, defense, expReward)
	{
	}

	int GetExpReward() const { return m_expReward; }

};