#pragma once
#include "MyLib.h"

class ScenePrep : public SceneBase
{

private:

	Node* m_rootNode;
	Player* m_player;
	int m_fontHandle;	//フォントハンドル


public:

	enum class SceneSelectionType
	{
		SceneGame,		//ゲームシーン
		SceneCredits	//クレジット情報シーン
	};
	 

	ScenePrep() :
		m_rootNode(nullptr),
		m_player(nullptr),
		m_fontHandle(0)
	{ }


	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;


	void LoadScene(SceneSelectionType type);

};