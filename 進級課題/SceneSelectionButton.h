#pragma once
#include "MyLib.h"
#include "ScenePrep.h"

class SceneSelectionButton : public Actor2D
{
private:
	static constexpr Vector2 Size = Vector2(300, 50);	//ボタンのサイズ
	Vector2 m_size;										//ボタンのサイズ
	Button m_button;									//ボタン機能
	ScenePrep::SceneSelectionType m_selectionType;		//シーンセレクションの種類
	ScenePrep* m_scenePrep;								//シーンセレクションの親シーン

	int m_fontHandle;


	//ボタンが押された時に呼ばれる関数
	void OnClick(){ m_scenePrep->LoadScene(m_selectionType); }

	//ボタンの枠
	void Frame();

protected:

	void Release() override;
	void Update() override;
	void Draw() override;

public:


	SceneSelectionButton(
		const Vector2& position,			//ボタンの座標
		ScenePrep::SceneSelectionType selectionType,
		ScenePrep* scenePrep
	);

};