#include "StageData.h"
#include "StageManager.h"
#include "ObjectFactory.h"
#include "Ground.h"
#include "AirGround.h"
#include "Enemy.h"
#include "Spike.h"
#include "Hole.h"
#include "Camera.h"

StageManager::StageManager(Camera* camera) :
	m_stage(nullptr),
	m_camera(camera),
	m_prevStageIndex(-1),
	m_worldColumn(0),
	m_localColumn(0),
	m_situation(Situation::EarlyStage)
{
	
	LoadEarlyMapData();		//序盤
	LoadMiddleMapData();	//中盤
	LoadLateMapData();		//終盤


	m_stage = std::make_unique<StageData>(*m_mapEarlyStageData[0]);	//最初のステージデータを読み込む(最初だけ固定)

}

void StageManager::Update()
{
	//デバッグ用のブロックの描画を切り替える
	//if (Keyboard::isDown(KEY_INPUT_1)) ToggleBlockDraw();


	int cameraTileX = static_cast<int>(m_camera->GetPos().x / TILE_SIZE);		//カメラの位置からタイルの列を計算する

	int generateLimit = cameraTileX + 20;	//カメラの位置から20列先まで生成する

	while (m_worldColumn < generateLimit)	//生成する列の上限まで生成する
	{
		//Debug::Log("Generate Column: %d\n", m_worldColumn);
		GenerateColumn(m_localColumn);
		m_worldColumn++;
		m_localColumn++;
	}

	if (m_localColumn >= m_stage->GetWidth())	//現在のステージの最後まで生成したら次のステージを生成する
	{

		switch (m_situation)
		{
		case Situation::EarlyStage:

			m_stage = std::make_unique<StageData>(*GetRandomStage(m_mapEarlyStageData));
			m_localColumn = 0;
			break;

		case Situation::MiddleStage:
			m_stage = std::make_unique<StageData>(*GetRandomStage(m_mapMiddleStageData));
			m_localColumn = 0;
			break;

		case Situation::LateStage:
			m_stage = std::make_unique<StageData>(*GetRandomStage(m_mapLateStageData));
			m_localColumn = 0;
			break;


		}
	}
}

void StageManager::Draw()
{

#ifdef _DEBUG
//ステージ全体の枠を描画
if (m_isBlockDraw)
{
	for (auto& pos : m_debugBlocks)
	{
		float screenX = pos.x - m_camera->GetPosition().x;
		float screenY = pos.y - m_camera->GetPosition().y;

		DrawBoxAA(
			screenX,
			screenY,
			screenX + TILE_SIZE,
			screenY + TILE_SIZE,
			GetColor(255, 0, 0),
			false
		);
	}

}
#endif



}


void StageManager::GenerateColumn(int column)
{
	for (int y = 0; y < m_stage->GetHeight(); y++)
	{
		char tile = m_stage->GetTile(column, y);
		//Debug::Log("Tile: %c\n", tile);


		Vector2 pos(m_worldColumn * TILE_SIZE, UI_HEIGHT + y * TILE_SIZE);
		//Debug::Log("Tile Position: (%f, %f)\n", pos.x, pos.y);
		m_debugBlocks.push_back(pos);	//デバッグ用のブロックの位置を保存する

		TileContext tileContext{ pos, TILE_SIZE };	//タイルの情報を作成する

		//タイルの種類に応じたオブジェクトを生成する
		if(Actor2D* obj = ObjectFactory::GetInstance()->CreateObject(tile, tileContext, m_camera))
		{
			AddChild(obj);	//生成したオブジェクトをステージマネージャーの子として追加する
		}
	}
}



StageData::StageMap* StageManager::GetRandomStage(const std::vector<StageData::StageMap*>& list)
{

	int index;

	do
	{
		index = GetRand(list.size() - 1);
	} while (index == m_prevStageIndex);

	m_prevStageIndex = index;

	return list[index];
}


void StageManager::LoadEarlyMapData()	
{
	static StageData::StageMap stage1 =
	{
		"..................................................",
		"..................................................",
		"...................S..............................",
		"........E.......S...............^.....E...........",
		"GGGGGGGGGGGPGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
	};

	static StageData::StageMap stage2 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage3 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage4 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage5 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage6 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage7 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage8 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage9 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage10 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
	};


	m_mapEarlyStageData.push_back(&stage1);
	m_mapEarlyStageData.push_back(&stage2);
	m_mapEarlyStageData.push_back(&stage3);
	m_mapEarlyStageData.push_back(&stage4);
	m_mapEarlyStageData.push_back(&stage5);
	m_mapEarlyStageData.push_back(&stage6);
	m_mapEarlyStageData.push_back(&stage7);
	m_mapEarlyStageData.push_back(&stage8);
	m_mapEarlyStageData.push_back(&stage9);
	m_mapEarlyStageData.push_back(&stage10);
}

void StageManager::LoadMiddleMapData()	
{

	static StageData::StageMap stage11 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage12 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage13 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage14 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage15 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage16 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage17 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage18 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage19 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage20 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};


	m_mapMiddleStageData.push_back(&stage11);
	m_mapMiddleStageData.push_back(&stage12);
	m_mapMiddleStageData.push_back(&stage13);
	m_mapMiddleStageData.push_back(&stage14);
	m_mapMiddleStageData.push_back(&stage15);
	m_mapMiddleStageData.push_back(&stage16);
	m_mapMiddleStageData.push_back(&stage17);
	m_mapMiddleStageData.push_back(&stage18);
	m_mapMiddleStageData.push_back(&stage19);
	m_mapMiddleStageData.push_back(&stage20);

}

void StageManager::LoadLateMapData()	
{

	static StageData::StageMap stage21 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage22 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage23 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage24 =
	{ 
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
	};

	static StageData::StageMap stage25 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage26 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage27 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage28 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage29 =
	{
		"..................................................",
		"..................................................",
		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};

	static StageData::StageMap stage30 =
	{
		"..................................................",
		"..................................................",
 		"..................................................",
		"..................................................",
		"GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",

	};


	m_mapLateStageData.push_back(&stage21);
	m_mapLateStageData.push_back(&stage22);
	m_mapLateStageData.push_back(&stage23);
	m_mapLateStageData.push_back(&stage24);
	m_mapLateStageData.push_back(&stage25);
	m_mapLateStageData.push_back(&stage26);
	m_mapLateStageData.push_back(&stage27);
	m_mapLateStageData.push_back(&stage28);
	m_mapLateStageData.push_back(&stage29);
	m_mapLateStageData.push_back(&stage30);

}

#ifdef _DEBUG

void StageManager::BlockDraw()
{
	if (m_isBlockDraw)
	{
		for (auto& pos : m_debugBlocks)
		{
			float screenX = pos.x - m_camera->GetPosition().x;
			float screenY = pos.y - m_camera->GetPosition().y;

			DrawBoxAA(
				screenX,
				screenY,
				screenX + TILE_SIZE,
				screenY + TILE_SIZE,
				GetColor(255, 0, 0),
				false
			);
		}

	}
}

#endif

