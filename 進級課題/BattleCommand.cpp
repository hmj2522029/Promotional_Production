#include "BattleCommand.h"
#include "Character.h"

void BattleCommand::AttackCommand(Character* action, Character* target)
{

	Debug::Log("AttackCommand executed!\n");
	bool penetration = false;	// 貫通攻撃かどうかのフラグ（例: スキルや特定の武器で貫通攻撃を実装する場合に使用）
	int damage = action->m_status.CalculateDamage(target->m_status, penetration);
	target->m_status.TakeDamage(damage);

	//キャラクターは行動した
	action->Action();

};


void BattleCommand::DefenseCommand(Character* action)
{
	Debug::Log("DefenseCommand executed!\n");

	// 防御状態にする
	action->m_status.StartDefend();
	
	//防御した時ちょっとだけHPを回復する
	action->m_status.Heal(5);

	//キャラクターは行動した
	action->Action();
};


void BattleCommand::EscapeCommand(Character* action)
{

	Debug::Log("EscapeCommand executed!\n");

	//逃走成功の確率を計算する
	int escapeChance = 30;			// 基本の逃走成功率（例: 50%）
	int randomValue = GetRand(100); // 0から99までのランダムな値を生成
	if (randomValue < escapeChance)
	{
		// 逃走成功
		Debug::Log("Escape successful!\n");

		action->RanAway();

	}
	else
	{
		// 逃走失敗
		Debug::Log("Escape failed!\n");
	}

	//キャラクターは行動した
	action->Action();

};

