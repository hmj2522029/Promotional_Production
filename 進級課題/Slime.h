#pragma once
#include "MyLib.h"
#include "Enemy.h"
#include "TileContext.h"
#include "Status.h"

class Camera;

class Slime : public Enemy
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

	Slime(const TileContext& tile, Camera* camera);

	int GetExpReward() const { return m_expReward * m_status.GetLevel(); }


};