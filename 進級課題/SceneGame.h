#pragma once
#include "MyLib.h"

class Player;
class Camera;
class StageManager;
class SceneStatus;
class BattleScene;

class SceneGame : public SceneBase
{
private:
	
	Node* m_rootNode;
	Camera* m_camera;
	Player* m_player;
	StageManager* m_stageManager;
	SceneStatus* m_sceneStatus;
	BattleScene* m_battleScene;

	int m_fontHandle;	//フォントハンドル

public:
	SceneGame() :
		m_rootNode(nullptr),
		m_player(nullptr),
		m_camera(nullptr),
		m_stageManager(nullptr),
		m_sceneStatus(nullptr),
		m_battleScene(nullptr),
		m_fontHandle(0)
	{ }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};