#pragma once
#include "MyLib.h"
#include "TileContext.h"

class Camera;


//敵(オブジェクト)
class EnemyFactory
{
private:

	EnemyFactory(){};

public:

	//どの敵を生成するかを返す
	static Actor2D* RandomEnemy(const TileContext& tile, Camera* camera);

};