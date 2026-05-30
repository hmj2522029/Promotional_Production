#include "BattleCommand.h"
#include "Character.h"

void BattleCommand::AttackCommand(Character* action, Character* target)
{

	bool penetration = false;	// 貫通攻撃かどうかのフラグ（例: スキルや特定の武器で貫通攻撃を実装する場合に使用）
	int damage = action->m_status.CalculateDamage(target->m_status, penetration);
	target->m_status.TakeDamage(damage);

	//キャラクターは行動した
	action->Action();

};


void BattleCommand::DefenseCommand(Character* action)
{

	// 防御状態にする
	action->m_status.StartDefend();
	
	//防御した時ちょっとだけHPを回復する
	action->m_status.Heal(5);

	//キャラクターは行動した
	action->Action();
};


void BattleCommand::EscapeCommand(Character* action)
{


	//逃走成功の確率を計算する
	int escapeChance = 30;			// 基本の逃走成功率（例: 50%）
	int randomValue = GetRand(100); // 0から99までのランダムな値を生成
	if (randomValue < escapeChance)
	{
		// 逃走成功

		action->RanAway();

	}
	else
	{
		// 逃走失敗
		//何もしない
	}

	//キャラクターは行動した
	action->Action();

};

