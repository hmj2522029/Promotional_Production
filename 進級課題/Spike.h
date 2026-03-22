#pragma once
#include "MyLib.h"
#include "TileContext.h"

class Camera;

class Spike : public Actor2D
{
private:

	Vector2 m_size;			//サイズ
	Vector2 m_offsetPos;	//座標をずらすため(落とし穴)
	Vector2 m_offsetCol;	//座標をずらすため(当たり判定)
	TileContext m_tileContext;
	Camera* m_camera;

protected:
	virtual void Update() override;
	virtual void Draw() override;

public:

	Spike(const TileContext& tile, Camera* camera);

};