#include "SceneSelectionButton.h"

SceneSelectionButton::SceneSelectionButton(
	const Vector2& position,			//ボタンの座標
	ScenePrep::SceneSelectionType selectionType,
	ScenePrep* scenePrep
) :
	Actor2D( DrawLayer::UILayer),
	m_selectionType(selectionType),
	m_scenePrep(scenePrep),
	m_button(Size, MOUSE_INPUT_LEFT, std::bind(&SceneSelectionButton::OnClick, this))
{
	m_transform.position = position;
}

void SceneSelectionButton::Update()
{

	//本来の更新処理
	Actor2D::Update();

	//ボタン
	m_button.Update(m_transform.position);

}

void SceneSelectionButton::Draw()
{
	//本来の描画処理
	Actor2D::Draw();

	// ボタン
	m_button.Draw(m_transform.position);

}