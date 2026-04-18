#include "ActionButton.h"
#include "DxLib.h"

ActionButton::ActionButton(
	const Vector2& position,		
	Player::ActionType actionType,	
	const char* textureName,	
	Player* const player
) :
	Actor2D(textureName, position, DrawLayer::UILayer),
	m_actionType(actionType),
	m_player(player),
	m_button(Size, MOUSE_INPUT_LEFT, std::bind(&ActionButton::OnClick, this))
{
}

void ActionButton::Update()
{
	
	//本来の更新処理
	Actor2D::Update();

	//ボタン
	m_button.Update(m_transform.position);

}

void ActionButton::Draw()
{

	//行動したら暗化表示する
	if (m_player->isAction())
	{
		SetDrawBright(100, 100, 100);
	}

	//本来の描画処理
	Actor2D::Draw();

	// 輝度を戻す
	SetDrawBright(255, 255, 255);

	// ボタン
	m_button.Draw(m_transform.position);

}