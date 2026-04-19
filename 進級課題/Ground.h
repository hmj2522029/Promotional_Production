#pragma once
#include "MyLib.h"
#include "TileContext.h"

class Camera;

//地面(オブジェクト)
class Ground : public Actor2D
{
private:

	Vector2 m_size;			//サイズ
	Vector2 m_center;		//中心座標
	Vector2 m_offsetPos;	//座標をずらすため(地面)
	Vector2 m_offsetCol;	//座標をずらすため(当たり判定)
	Camera* m_camera;
	TileContext m_tileContext;


protected:

	virtual void Update() override;
	virtual void Draw() override;
	
public:
	Ground(const TileContext& tile, Camera* camera);

};