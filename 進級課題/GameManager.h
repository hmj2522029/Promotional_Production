#pragma once
#include "MyLib.h"

class Camera;
class StageManager;

class GameManager : public Node
{
private:

	Camera* m_camera;
	StageManager* m_stageManager;

protected:

	void Update() override;

public:

	GameManager(Camera* camera, StageManager* stageManager);

};