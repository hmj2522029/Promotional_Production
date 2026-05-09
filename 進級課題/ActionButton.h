#pragma once
#include "Player.h"
#include "MyLib.h"

class Enemy;

class ActionButton : public Actor2D
{
private:
	
	static constexpr Vector2 Size = Vector2(100, 100);

	Vector2 m_size;						// ボタンのサイズ
	Player::ActionType m_actionType;	//押された時の行動
	Player* m_player;
	Enemy* m_enemy;						//当たった敵
	Button m_button;					//ボタン機能

	//ボタンが押された時に呼ばれる関数
	void OnClick() { m_player->ActionSelection(m_actionType, m_enemy); }

protected:

	void Update() override;
	void Draw() override;

public:
	
	ActionButton(
		const Vector2& position,			//ボタンの座標
		Player::ActionType actionType,		//ボタンが押した時の行動
		const char* textureName,			//ボタンの画像
		Player* const playerNod,
		Enemy* const enemy					//当たった敵
	);


};