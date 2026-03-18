#pragma once
#include "MyLib.h"
#include <vector>

class StageData
{
public:

    // マップ記号
    static const char MAP_EMPTY     = '.'; //何もない
    static const char MAP_GROUND    = 'G'; //地面
    static const char MAP_SKYGROUND = 'S'; //地面(空中)
    static const char MAP_PIT       = 'P'; //落とし穴
    static const char MAP_SPIKE     = '^'; //トゲ
    static const char MAP_ENEMY     = 'E'; //敵

    static const int WIDTH  = 50;
    static const int HEIGHT = 5;

    using StageMap = const char* [HEIGHT];

private:

	//タイルの種類を表す定数
    enum TerrainType
    {
        Empty     = 0,  // 何もない
        Ground    = 1,  // 地面
		SkyGround = 2,  // 地面(空中)
        Pit       = 3,  // 落とし穴
		Spike     = 4,  // トゲ

    };

    struct EnemySpawnData
    {
        Vector2 pos;
        int type;
    };

    TerrainType m_terrain[WIDTH][HEIGHT]; //地形情報
    char m_tile[WIDTH][HEIGHT];

    std::vector<Vector2> m_enemies;       //敵情報

public:

	const int GetHeight() { return HEIGHT; }
	const int GetWidth() { return WIDTH; }

    StageData(const StageMap& map);

    TerrainType GetTerrain(int x, int y) const { return m_terrain[x][y]; }
	char GetTile(int x, int y) const { return m_tile[x][y]; }


    const std::vector<Vector2>& GetEnemies() const { return m_enemies; }

};
