#pragma once
#include "MyLib.h"

class Player;
class Camera;
class StageManager;

class SceneGame : public SceneBase
{
private:
	
	Node* m_rootNode;
	Camera* m_camera;
	Player* m_player;
	StageManager* m_stageManager;

public:
	SceneGame():
		m_rootNode(nullptr),
		m_player(nullptr),
		m_camera(nullptr),
		m_stageManager(nullptr)
	{ }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};