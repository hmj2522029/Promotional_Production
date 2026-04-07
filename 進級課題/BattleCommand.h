#pragma once
#include "MyLib.h"

class Character;

class BattleCommand
{
private:


public:
	BattleCommand(){};

	//攻撃コマンド
	void AttackCommand(Character* action, Character* target);

	//防御コマンド
	void DefenseCommand(Character* action);

	//逃走コマンド
	void EscapeCommand(Character* action);


};