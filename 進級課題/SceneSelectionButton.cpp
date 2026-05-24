#include "SceneSelectionButton.h"

SceneSelectionButton::SceneSelectionButton(
	const Vector2& position,			//ボタンの座標
	ScenePrep::SceneSelectionType selectionType,
	ScenePrep* scenePrep
) :
	Actor2D( DrawLayer::UILayer),
	m_selectionType(selectionType),
	m_scenePrep(scenePrep),
	m_button(Size, MOUSE_INPUT_LEFT, std::bind(&SceneSelectionButton::OnClick, this)),
	m_fontHandle(0)
{
	//フォントの読み込み
	AddFontResourceEx("Resource/PixelMplus/PixelMplus12-Regular.ttf", FR_PRIVATE, NULL);
	m_fontHandle = CreateFontToHandle("PixelMplus12", 30, -1);


	m_transform.position = position;
}

void SceneSelectionButton::Release()
{

	DeleteFontToHandle(m_fontHandle);

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


	Frame();

	switch (m_selectionType)
	{

	case ScenePrep::SceneSelectionType::SceneGame:

		DrawStringToHandle(
			static_cast<int>(m_transform.position.x - (Size.x / 2) + 75),
			static_cast<int>(m_transform.position.y - (Size.y / 2) + 10) ,
			"ゲーム開始",
			GetColor(255, 255, 255),
			m_fontHandle,
			GetColor(0, 0, 0)
		);


		break;
	case ScenePrep::SceneSelectionType::SceneStatus:

		DrawStringToHandle(
			static_cast<int>(m_transform.position.x - (Size.x / 2) + 40),
			static_cast<int>(m_transform.position.y - (Size.y / 2) + 10),
			"ステータス表示",
			GetColor(255, 255, 255),
			m_fontHandle,
			GetColor(0, 0, 0)
		);


		break;
	case ScenePrep::SceneSelectionType::SceneCredits:


		DrawStringToHandle(
			static_cast<int>(m_transform.position.x - (Size.x / 2) + 40),
			static_cast<int>(m_transform.position.y - (Size.y / 2) + 10),
			"クレジット表記",
			GetColor(255, 255, 255),
			m_fontHandle,
			GetColor(0, 0, 0)
		);

		break;


	}

	// ボタン
	m_button.Draw(m_transform.position);

}

void SceneSelectionButton::Frame()
{

	//枠
	DrawBox(
		static_cast<int>(m_transform.position.x - 2 - (Size.x / 2)), 
		static_cast<int>(m_transform.position.y - 2 - (Size.y / 2)),
		static_cast<int>(m_transform.position.x + (Size.x / 2) + 2),
		static_cast<int>(m_transform.position.y + (Size.y / 2) + 2),
		GetColor(0, 0, 0), TRUE);

	//枠の中
	DrawBox(
		static_cast<int>(m_transform.position.x - (Size.x / 2)),
		static_cast<int>(m_transform.position.y - (Size.y / 2)),
		static_cast<int>(m_transform.position.x + (Size.x / 2)),
		static_cast<int>(m_transform.position.y + (Size.y / 2)),
		GetColor(150, 150, 150), TRUE);


}