#pragma once
#include "MyLib.h"
#include "StageData.h"
#include "TileContext.h"
#include <vector>
#include <memory>	

class StageData;
class Camera;


class StageManager : public Node
{
public:

	//ステージの進み具合を表す定数
	enum Situation
	{
		EarlyStage,	 //序盤
		MiddleStage, //中盤
		LateStage,	 //終盤

	};

private:

	static constexpr int GenerateAhead = 20;	//プレイヤーの前にどれだけステージを生成するか(タイルの数)
	static constexpr int UiHeight = 195;		//UIを表示するためのyの範囲
	static constexpr int PlayerY = 500;			//置きたいプレイヤーの位置
	static constexpr int GroundY = 544;			//置きたいブロックの位置
	static constexpr int TileSize = 80;			//タイルのサイズ

	static constexpr int MaxScreenStage = 16;	//画面に表示される最大のステージ数(画面の幅 / タイルのサイズ)

	//std::unique_ptrは自動的に所有者(StageManager)がなくなった場合にメモリを解放してくれる
	std::unique_ptr<StageData> m_stage;

	Situation m_situation;	//ステージの進み具合
	int m_prevStageIndex;	//前のステージのインデックス(連続して同じステージを出さないため)
	int m_worldColumn;		//生成した列の数(生成する列の位置を計算するため)
	int m_localColumn;		//現在のステージの列の位置(現在のステージの最後まで生成したかどうかを判断するため)
	int m_stageLoopIndex;	//ステージのループのインデックス

	//マップデータ
	std::vector<StageData::StageMap> m_mapEarlyStageData;	//序盤のマップデータ
	std::vector<StageData::StageMap> m_mapMiddleStageData;	//中盤のマップデータ
	std::vector<StageData::StageMap> m_mapLateStageData;	//終盤のマップデータ


	StageData::StageMap* GetRandomStage(std::vector<StageData::StageMap>& list);	//マップデータのリストからランダムにマップデータを取得する関数

	//ステージの生成
	void GenerateColumn(int column, int screenStage);	//マップデータの列を生成する関数

	//テキストファイルからステージデータを読み込む関数(複数)
	std::vector<StageData::StageMap>LoadStageData(const std::string& filePath);


protected:

	virtual void Update() override;
	virtual void Draw() override;

public:

	StageManager();

	//ステージの進み具合を変更する関数
	void SetSituation(Situation situation) { m_situation = situation; }

	//タイルのサイズを取得する関数
	static int GetTileSize() { return TileSize; }
	static int GetMaxScreenStage() { return MaxScreenStage; }


#ifdef _DEBUG
	std::vector<Vector2> m_debugBlocks;
	bool m_isBlockDraw = true;	//ブロックを描画するかどうかのフラグ(デバッグ用)

	void BlockDraw();

	//m_isBlockDrawの値を切り替える関数(デバッグ用)
	void ToggleBlockDraw() { m_isBlockDraw = !m_isBlockDraw; }
	

#endif

};
