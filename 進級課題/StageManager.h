#pragma once
#include "MyLib.h"
#include "StageData.h"
#include "TileContext.h"
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



	static constexpr int UI_HEIGHT = 158;	//UIを表示するためのyの範囲
	static constexpr int PLAYER_Y  = 480;	//置きたいプレイヤーの位置
	static constexpr int GROUND_Y  = 544;	//置きたいブロックの位置
	static constexpr int TILE_SIZE = 80;	//タイルのサイズ

	static constexpr int MaxScreenStage = 16;	//画面に表示される最大のステージ数(画面の幅 / タイルのサイズ)

	//std::unique_ptrは自動的に所有者(StageManager)がなくなった場合にメモリを解放してくれる
	std::unique_ptr<StageData> m_stage;
	Camera* m_camera;

	Situation m_situation;	//ステージの進み具合
	int m_prevStageIndex;	//前のステージのインデックス(前のステージを出さないようにするため)
	int m_worldColumn;		//生成した列の数(生成する列の位置を計算するため)
	int m_localColumn;		//現在のステージの列の位置(現在のステージの最後まで生成したかどうかを判断するため)
	int m_screenStage;		//現在画面に表示されているステージの数

	//マップデータ
	std::vector<StageData::StageMap*> m_mapEarlyStageData;	//序盤のマップデータ
	std::vector<StageData::StageMap*> m_mapMiddleStageData;	//中盤のマップデータ
	std::vector<StageData::StageMap*> m_mapLateStageData;	//終盤のマップデータ


	StageData::StageMap* GetRandomStage(const std::vector<StageData::StageMap*>& list);	//マップデータのリストからランダムにマップデータを取得する関数

	//マップデータの読み込み
	void LoadEarlyMapData();	//序盤のマップデータの読み込み
	void LoadMiddleMapData();	//中盤のマップデータの読み込み
	void LoadLateMapData();		//終盤のマップデータの読み込み


	//ステージの生成
	void GenerateColumn(int column, int screenStage);	//マップデータの列を生成する関数

		
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
