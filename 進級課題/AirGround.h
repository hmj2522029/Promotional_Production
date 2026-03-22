#pragma once
#include "MyLib.h"
#include "TileContext.h"

class Camera;

//空中ブロック(オブジェクト)
class AirGround : public Actor2D
{
private:

	Vector2 m_size;			//サイズ
	Vector2 m_offsetCol;	//座標をずらすため(当たり判定)
	Camera* m_camera;
	TileContext m_tileContext;


protected:

	virtual void Update() override;
	virtual void Draw() override;

public:
	AirGround(const TileContext& tile, Camera* camera);


};