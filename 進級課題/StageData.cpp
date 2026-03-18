#include"StageData.h"

StageData::StageData(const StageMap& map) :
    m_enemies(),
    m_terrain()
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
           char c = map[y][x];

		   m_tile[x][y] = c; //マップ記号を保存

            switch (c)
            {
            case MAP_GROUND:
                m_terrain[x][y] = Ground; //地面
                break;

			case MAP_SKYGROUND:
                m_terrain[x][y] = SkyGround; //地面(空中)
				break;

            case MAP_SPIKE:
                m_terrain[x][y] = Spike;  //トゲ
                break;

            case MAP_PIT:
                m_terrain[x][y] = Pit;    //落とし穴
                break;

            default:
                m_terrain[x][y] = Empty;   //何もない
                break;
            }

            if (c == MAP_ENEMY)   //敵の位置
            {
                m_enemies.push_back(Vector2(x, y));
            }
        }
    }

}



