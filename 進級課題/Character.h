#pragma once
#include "Status.h"
#include "MyLib.h"

class Character : public Actor2D
{

	bool m_isAction;	//各キャラクターが行動したかどうか

public:
	Status m_status;	//ステータス

	Character(
		Tag tag = Tag::None, 
		Rigidbody2D::Type type = Rigidbody2D::Type::Static, 
		int Lv = 0, 
		int Hp = 0, 
		int attack = 0,
		int defense = 0
	) :
		Actor2D(tag, type),
		m_status(Lv, Hp, attack, defense),
		m_isAction(false)
	{
	}

	//行動したかどうか
	bool isAction() const { return m_isAction; }

	//行動した
	void Action() { m_isAction = true; }

	//行動をリセット
	void ResetAction() { m_isAction = false; }

};