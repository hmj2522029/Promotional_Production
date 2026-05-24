#pragma once
#include "MyLib.h"

class ResultData : public Node
{
private:

	struct Data
	{
		int m_distance;         //プレイヤーが進んだ距離
		int m_enemies;          //倒した敵の数
		int m_exp;              //獲得した経験値
		float m_playTime;		//プレイ時間

	};

	Data m_data;	//データ
	int m_tile;		//距離を出すため用



protected:

	void Load() override;
	void Update() override;

public:

	ResultData(int tile) :
		m_tile(tile),
		m_data()
	{
	}

	//各データの取得
	int GetDistance() const { return m_data.m_distance; }
	int GetEnemies() const { return m_data.m_enemies; }
	int GetExp() const { return m_data.m_exp; }
	float GetPlayTime() const { return m_data.m_playTime; }

	//データの加算
	void AddEnemies(int enemies) { m_data.m_enemies += enemies; }
	void AddExp(int exp) { m_data.m_exp += exp; }
	void AddPlayTime(float playTime) { m_data.m_playTime += playTime; }
	
	//データのリセット
    void Reset();


};