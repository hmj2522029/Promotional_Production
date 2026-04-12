#pragma once
#include "Status.h"
#include "MyLib.h"

class Character : public Actor2D
{

	bool m_isAction;	//各キャラクターが行動したかどうか

public:
	Status m_status;	//ステータス

	Character(	//アニメーション
		const Animation2D& anime,
		const Vector2& gridSize,
		const Vector2& pos,
		Tag tag = Tag::None,
		Rigidbody2D::Type type = Rigidbody2D::Type::Static,
		int Lv = 0,
		int Hp = 0,
		int attack = 0,
		int defense = 0
	) :
		Actor2D(anime, gridSize, pos, tag, type),
		m_status(Lv, Hp, attack, defense),
		m_isAction(false)
	{
	}
	Character(	//画像
		const char* textureName,
		const Vector2& pos,
		Tag tag = Tag::None,
		Rigidbody2D::Type type = Rigidbody2D::Type::Static,
		int Lv = 0,
		int Hp = 0,
		int attack = 0,
		int defense = 0
	) :
		Actor2D(textureName, pos, tag, type),
		m_status(Lv, Hp, attack, defense),
		m_isAction(false)
	{
	}

	Character(	//アニメーションなし
		Tag tag = Tag::None,
		Rigidbody2D::Type type = Rigidbody2D::Type::Static,
		int Lv = 0,
		int Hp = 0,
		int attack = 0,
		int defense = 0
	) :
		Character(nullptr, Vector2(0, 0), tag, type, Lv, Hp, attack, defense)
	{
	}

	//行動したかどうか
	bool isAction() const { return m_isAction; }

	//行動した
	void Action() { m_isAction = true; }

	//行動をリセット
	void ResetAction() { m_isAction = false; }

};