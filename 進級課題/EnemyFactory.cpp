#include "EnemyFactory.h"
#include "Camera.h"

#include "Slime.h"

//敵の生成関数のテンプレート
template<typename T>
Enemy* Create(const TileContext& t, Camera* c) {
	return new T(t, c);
}

Actor2D* EnemyFactory::RandomEnemy(const TileContext& tile, Camera* camera)
{
	//敵の生成関数の配列
	static Enemy* (*factory[])(const TileContext&, Camera*) = {
	  Create<Slime>,
	  //??Create<Bat>,
	  //??Create<Goblin>
	};

	//敵の種類はランダムに決める
	int enemyType = GetRand(std::size(factory) - 1);

	//敵の種類が配列の範囲内なら生成関数を呼び出す
	if (enemyType >= 0 && enemyType < std::size(factory)) {
		return factory[enemyType](tile, camera);
	}

	return nullptr;
}