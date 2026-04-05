#pragma once
#include "Status.h"
#include "MyLib.h"

class Character : public Actor2D
{
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
		m_status(Lv, Hp, attack, defense)
	{
	}


};