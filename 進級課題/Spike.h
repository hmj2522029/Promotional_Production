#pragma once
#include "MyLib.h"
#include "TileContext.h"

class Camera;

class Spike : public Actor2D
{
private:

	Vector2 m_size;			//サイズ
	Vector2 m_offsetPos;	//座標をずらすため(落とし穴)
	Vector2 m_center;
	TileContext m_tileContext;

protected:
	virtual void Update() override;
	virtual void Draw() override;

public:

	Spike(const TileContext& tile);

};