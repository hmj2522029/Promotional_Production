#pragma once
#include "MyLib.h"

class Player;
class Enemy;
class Character;

class BattleCommand 
{
private:

	bool m_isDefending;	//防御しているかどうか

public:
	BattleCommand() :
		m_isDefending(false)
	{
	};

	//攻撃コマンド
	void AttackCommand(Character* action, Character* target);

	//防御コマンド
	void DefenseCommand(Character* action);

	//逃走コマンド
	void EscapeCommand(Character* action);


};