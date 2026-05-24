#include "ObjectFactory.h"
#include "Ground.h"
#include "AirGround.h"
#include "EnemyFactory.h"
#include "Spike.h"
#include "Hole.h"
#include "Camera.h"

Actor2D* ObjectFactory::CreateObject(const TileContext& tileContext)
{
	auto it = m_tileTable.find(tileContext.tile);	//マップ記号に対応するタイル生成関数を探す


	if (it != m_tileTable.end())	//対応するタイル生成関数が見つかった場合
	{
		return (this->*it->second)(tileContext);	//タイル生成関数を呼び出す(返す)
	}

	return nullptr;	//見つからなかった場合はnullptrを返す
}


Actor2D* ObjectFactory::CreateGround(const TileContext& tile)
{
	return new Ground(tile);
}
Actor2D* ObjectFactory::CreateAirGround(const TileContext& tile)
{
	return new AirGround(tile);
}
Actor2D* ObjectFactory::CreateEnemy(const TileContext& tile)
{
	return EnemyFactory::RandomEnemy(tile);
}
Actor2D* ObjectFactory::CreateSpike(const TileContext& tile)
{
	return new Spike(tile);
}
Actor2D* ObjectFactory::CreateHole(const TileContext& tile)
{
	return new Hole(tile);
}


void ObjectFactory::InitializeTileTable()
{
	m_tileTable['G'] = &ObjectFactory::CreateGround;
	m_tileTable['S'] = &ObjectFactory::CreateAirGround;
	m_tileTable['E'] = &ObjectFactory::CreateEnemy;
	m_tileTable['^'] = &ObjectFactory::CreateSpike;
	m_tileTable['P'] = &ObjectFactory::CreateHole;
}

