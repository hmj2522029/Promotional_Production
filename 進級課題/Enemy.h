#pragma once
#include "MyLib.h"
#include "TileContext.h"

class Camera;


//敵(オブジェクト)
class Enemy : public Actor2D
{
private:

	Vector2 m_size;			//サイズ
	Vector2 m_offsetPos;	//座標をずらすため(落とし穴)
	Vector2 m_offsetCol;	//座標をずらすため(当たり判定)
	Camera* m_camera;
	TileContext m_tileContext;


protected:
	virtual void Update() override;
	virtual void Draw() override;

public:

	Enemy(const TileContext& tile, Camera* camera);

};