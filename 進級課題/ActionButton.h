#pragma once
#include "Player.h"
#include "BattleCommand.h"
#include "MyLib.h"

class ActionButton : public Actor2D
{
private:
	
	static constexpr Vector2 Size = Vector2(30, 30);

	Vector2 m_size;		// ボタンのサイズ
	Player* m_player;
	BattleCommand* m_command;
	Button m_button

	//ボタンが押された時に呼ばれる関数
	void OnClick() {m_command->}

protected:

	void Update() override;
	void Draw() override;

public:


};