#pragma once
#include "MyLib.h"

class PrepPlayerController;
class SceneStatus;
class SceneCredit;

class ScenePrep : public SceneBase
{

private:

	Node* m_rootNode;
	PrepPlayerController* m_playerController;
	SceneStatus* m_sceneStatus;
	SceneCredit* m_sceneCredit;
	int m_fontHandle;	//フォントハンドル
	int m_bgm;			//BGM

public:

	enum class SceneSelectionType
	{
		SceneGame,		//ゲームシーン
		SceneStatus,	//タイトルシーン
		SceneCredits	//クレジット情報シーン
	};
	 

	ScenePrep() :
		m_rootNode(nullptr),
		m_playerController(nullptr),
		m_sceneStatus(nullptr),
		m_sceneCredit(nullptr),
		m_fontHandle(0),
		m_bgm(0)
	{ }


	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;


	void LoadScene(SceneSelectionType type);

};