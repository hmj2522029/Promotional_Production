#pragma once
#include "MyLib.h"

class Player;
class Camera;
class StageManager;
class SceneGameUI;
class BattleScene;

class SceneGame : public SceneBase
{
private:
	
	Node* m_rootNode;
	Camera* m_camera;
	Player* m_player;
	StageManager* m_stageManager;
	SceneGameUI* m_sceneGameUI;
	BattleScene* m_battleScene;

public:
	SceneGame():
		m_rootNode(nullptr),
		m_player(nullptr),
		m_camera(nullptr),
		m_stageManager(nullptr),
		m_sceneGameUI(nullptr),
		m_battleScene(nullptr)
	{ }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};