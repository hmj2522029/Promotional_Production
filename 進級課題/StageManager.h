#pragma once
#include "MyLib.h"
#include "StageData.h"
#include "TileContext.h"
#include <unordered_map>
#include <vector>
#include <memory>	
//#include <random>エラーになる

class StageData;
class Camera;


class StageManager : public Node
{
private:


	//ステージの進み具合を表す定数
	enum Situation
	{
		EarlyStage,	 //序盤
		MiddleStage, //中盤
		LateStage,	 //終盤

	};


	using TileCreateFunc = void (StageManager::*)(const TileContext&, Camera*);	//タイルを生成する関数の型(引数 Vector2 戻り値 void)
	std::unordered_map<char, TileCreateFunc> m_tileTable;	//マップ記号とタイル生成関数の対応表(キー = タイル文字 値 = 生成する関数)

	static const int UI_HEIGHT = 158;	//UIを表示するためのyの範囲
	static const int PLAYER_Y  = 480;	//置きたいプレイヤーの位置
	static const int GROUND_Y  = 544;	//置きたいブロックの位置
	static const int TILE_SIZE = 80;	//タイルのサイズ

	//std::unique_ptrは自動的に所有者(StageManager)がなくなった場合にメモリを解放してくれる
	std::unique_ptr<StageData> m_stage;
	Camera* m_camera;

	Situation m_situation;	//ステージの進み具合
	int m_prevStageIndex;	//前のステージのインデックス(前のステージを出さないようにするため)
	int m_worldColumn;		//生成した列の数(生成する列の位置を計算するため)

	//マップデータ
	std::vector<StageData::StageMap*> m_mapEarlyStageData;	//序盤のマップデータ
	std::vector<StageData::StageMap*> m_mapMiddleStageData;	//中盤のマップデータ
	std::vector<StageData::StageMap*> m_mapLateStageData;	//終盤のマップデータ


	StageData::StageMap* GetRandomStage(const std::vector<StageData::StageMap*>& list);	//マップデータのリストからランダムにマップデータを取得する関数

	//マップデータの読み込み
	void LoadEarlyMapData();	//序盤のマップデータの読み込み
	void LoadMiddleMapData();	//中盤のマップデータの読み込み
	void LoadLateMapData();		//終盤のマップデータの読み込み

	//テーブルの初期化
	void InitializeTileTable();	//マップ記号とタイル生成関数の対応表を初期化する関数

	//ステージの生成
	void GenerateColumn(int column);	//マップデータの列を生成する関数

	void CreateGround(const TileContext& tile, Camera* camera);		//地面を生成する関数
	void CreateAirGround(const TileContext& tile, Camera* camera); 	//空中ブロックを生成する関数
	void CreateEnemy(const TileContext& tile, Camera* camera);		//敵を生成する関数
	void CreateSpike(const TileContext& tile, Camera* camera);		//トゲを生成する関数
	void CreateHole(const TileContext& tile, Camera* camera);		//落とし穴を生成する関数
		
protected:

	virtual void Update() override;
	virtual void Draw() override;

public:

	StageManager(Camera* camera);

	//ステージの進み具合を変更する関数
	void SetSituation(Situation situation) { m_situation = situation; }


	//ステージの進んでいる距離を取得する関数(1ブロック = 1メートル)
	float GetDistance() const { return m_worldColumn * TILE_SIZE / 100.0f; }


#ifdef _DEBUG
	std::vector<Vector2> m_debugBlocks;
	bool m_isBlockDraw = true;	//ブロックを描画するかどうかのフラグ(デバッグ用)

	void BlockDraw();

	//m_isBlockDrawの値を切り替える関数(デバッグ用)
	void ToggleBlockDraw() { m_isBlockDraw = !m_isBlockDraw; }
	

#endif

};
