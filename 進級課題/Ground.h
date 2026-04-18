#pragma once
#include "MyLib.h"
#include "TileContext.h"

class Camera;

//地面(オブジェクト)
class Ground : public Actor2D
{
private:

	Vector2 m_size;		//サイズ
	Vector2 m_center;	//中心座標
	Camera* m_camera;
	TileContext m_tileContext;


protected:

	virtual void Update() override;
	virtual void Draw() override;
	
public:
	Ground(const TileContext& tile, Camera* camera);

};