#pragma once
#include "MyLib.h"
#include "TileContext.h"

class Camera;

//落とし穴(オブジェクト)
class Hole : public Actor2D
{
private:

	Camera* m_camera;
	TileContext m_tileContext;

protected:
	virtual void Update() override;
	virtual void Draw() override;

public:

	Hole(const TileContext& tile, Camera* camera);
};