#pragma once
#include "MyLib.h"
#include "TileContext.h"

class Camera;

//落とし穴(オブジェクト)
class Hole : public Actor2D
{
private:

	Vector2 m_size;			//サイズ
	Vector2 m_center;		//中心座標
	Vector2 m_offsetPos;	//座標をずらすため(落とし穴)
	Vector2 m_offsetCol;	//座標をずらすため(当たり判定)
	TileContext m_tileContext;

protected:
	virtual void Update() override;
	virtual void Draw() override;

public:

	Hole(const TileContext& tile);
};