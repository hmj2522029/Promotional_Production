#pragma once
#include "MyLib.h"
#include "TileContext.h"

class Camera;

class Spike : public Actor2D
{
private:

	TileContext m_tileContext;
	Camera* m_camera;

protected:
	virtual void Update() override;
	virtual void Draw() override;

public:

	Spike(const TileContext& tile, Camera* camera);

};