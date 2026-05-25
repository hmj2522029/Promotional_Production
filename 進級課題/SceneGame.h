#pragma once
#include "MyLib.h"

class Player;
class Camera;
class StageManager;
class SceneStatus;
class BattleScene;
class SceneLevelUp;
class SceneResults;
class ResultData;
class SceneClear;

class SceneGame : public SceneBase
{
private:

	enum class FadeState
	{
		Fade,		//フェード中
		Run,		//実行中

	};
	
	Node* m_rootNode;
	Player* m_player;
	StageManager* m_stageManager;
	SceneStatus* m_sceneStatus;
	BattleScene* m_battleScene;
	SceneLevelUp* m_sceneLevelUp;
	SceneResults* m_sceneResults;
	ResultData* m_resultData;
	SceneClear* m_sceneClear;
	FadeState m_fadeState;

	int m_fontHandle;		//フォントハンドル
	int m_largeFontHandle;	//大きいフォントのハンドル
	int m_bgm;				//BGM

public:

	SceneGame() :
		m_rootNode(nullptr),
		m_player(nullptr),
		m_stageManager(nullptr),
		m_sceneStatus(nullptr),
		m_battleScene(nullptr),
		m_sceneLevelUp(nullptr),
		m_sceneResults(nullptr),
		m_resultData(nullptr),
		m_sceneClear(nullptr),
		m_fadeState(FadeState::Run),
		m_fontHandle(0),
		m_largeFontHandle(0),
		m_bgm(0)
	{ }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;

};