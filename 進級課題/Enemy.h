#pragma once
#include "Character.h"

class Enemy : public Character
{
protected:
	//敵が共通して持つ情報や機能をここに書く
	int m_expReward;	//倒したときにプレイヤーが得る経験値

public:


	Enemy(
		Tag tag = Tag::Enemy,
		Rigidbody2D::Type type = Rigidbody2D::Type::Dynamic,
		int Lv = 0,
		int Hp = 0,
		int attack = 0,
		int defense = 0,
		int expReward = 0
	) :
		Character(tag, type, Lv, Hp, attack, defense),
		m_expReward(expReward)
	{
	}

	int GetExpReward() const { return m_expReward; }

};