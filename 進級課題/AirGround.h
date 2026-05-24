#pragma once
#include "MyLib.h"
#include "TileContext.h"

class Camera;

//空中ブロック(オブジェクト)
class AirGround : public Actor2D
{
private:

	Vector2 m_center;		//中心
	Vector2 m_size;			//サイズ
	TileContext m_tileContext;


protected:

	virtual void Update() override;
	virtual void Draw() override;

public:
	AirGround(const TileContext& tile);


};