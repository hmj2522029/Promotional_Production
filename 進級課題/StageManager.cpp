#include "StageData.h"
#include "StageManager.h"
#include "ObjectFactory.h"
#include "Ground.h"
#include "AirGround.h"
#include "Enemy.h"
#include "Spike.h"
#include "Hole.h"
#include "Camera.h"

#include <sstream>
#include <fstream>
#include <unordered_map>
#include <string>


StageManager::StageManager(Camera* camera) :
	m_stage(nullptr),
	m_camera(camera),
	m_prevStageIndex(-1),
	m_worldColumn(0),
	m_localColumn(0),
	m_screenStage(1),
	m_situation(Situation::EarlyStage)
{
	
	m_mapEarlyStageData = LoadStageData("Data/Stage/EarlyStage/Stage.txt");
	m_mapMiddleStageData = LoadStageData("Data/Stage/MiddleStage/Stage.txt");
	m_mapLateStageData = LoadStageData("Data/Stage/LateStage/Stage.txt");

	m_stage = std::make_unique<StageData>(m_mapEarlyStageData[0]);	//最初のステージデータを読み込む(最初だけ固定)

}

void StageManager::Update()
{

	int cameraTileX = static_cast<int>(m_camera->GetPos().x / TileSize);		//カメラの位置からタイルの列を計算する

	int generateLimit = cameraTileX + 20;	//カメラの位置から20列先まで生成する

	while (m_worldColumn < generateLimit)	//生成する列の上限まで生成する
	{
		GenerateColumn(m_localColumn, m_screenStage);
		m_worldColumn++;
		m_localColumn++;

		m_screenStage++;
		if(m_screenStage > MaxScreenStage)	//
		{
			m_screenStage = 1;	
		}

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
				screenX + TileSize,
				screenY + TileSize,
				GetColor(255, 0, 0),
				false
			);
		}
	
	}
#endif



}


void StageManager::GenerateColumn(int column, int screenStage)
{
	for (int y = 0; y < m_stage->GetHeight(); y++)
	{
		char tile = m_stage->GetTile(column, y);


		Vector2 pos(m_worldColumn * TileSize, UiHeight + y * TileSize);

		TileContext tileContext{tile, screenStage, pos, TileSize };	//タイルの情報を作成する

		//タイルの種類に応じたオブジェクトを生成する
		if(Actor2D* obj = ObjectFactory::GetInstance()->CreateObject(tileContext, m_camera))
		{
			AddChild(obj);	//生成したオブジェクトをステージマネージャーの子として追加する
		}


#ifdef _DEBUG
		m_debugBlocks.push_back(pos);	//デバッグ用のブロックの位置を保存する
#endif


	}
}



StageData::StageMap* StageManager::GetRandomStage(std::vector<StageData::StageMap>& list)
{

	int index;

	do
	{
		index = GetRand(static_cast<int>(list.size()) - 1);
	} while (index == m_prevStageIndex);

	m_prevStageIndex = index;

	return &list[index];
}


std::vector<StageData::StageMap> StageManager::LoadStageData(const std::string& path)
{
	//テキストファイルからステージデータを読み込む関数(複数)
	std::ifstream file(path);

	
	//ステージデータを保存するベクター
	std::vector<StageData::StageMap> stages;

	//ファイルが開けなかった場合は返す
	if (!file.is_open())return stages;

	//現在読み込んでいるステージデータ
	StageData::StageMap current;

	//テキストファイルを1行ずつ読み込む
	std::string line;

	//空行でステージデータを区切る
	while (std::getline(file, line))
	{
		//空行の場合は現在のステージデータを保存して次のステージデータの読み込みを開始する
		if (line.empty())
		{
			//現在のステージデータが空でない場合は保存する
			if (!current.empty())
			{
				stages.push_back(current);
				current.clear();
			}
			continue;
		}

		//行の先頭が#の場合はコメント行とみなして読み飛ばす
		if (line[0] == '#') continue;

		current.push_back(line);
	}

	//最後のステージデータが空でない場合は保存する
	if (!current.empty())
	{
		stages.push_back(current);
	}

	return stages;
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
				screenX + TileSize,
				screenY + TileSize,
				GetColor(255, 0, 0),
				false
			);
		}

	}
}

#endif

