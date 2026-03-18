#pragma once
#include "MyLib.h"

class Player;
class Camera;
class StageManager;

class SceneGame
{
private:
	
	Node* m_rootNode;
	Camera* m_camera;
	Player* m_player;
	StageManager* m_stageManager;

public:
	void Update();
	void Draw();

	SceneGame();
};