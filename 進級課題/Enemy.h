#pragma once
#include "MyLib.h"
#include "TileContext.h"

class Camera;


//敵(オブジェクト)
class Enemy : public Actor2D
{
private:

	Camera* m_camera;
	TileContext m_tileContext;


protected:
	virtual void Update() override;
	virtual void Draw() override;

public:

	Enemy(const TileContext& tile, Camera* camera);

};