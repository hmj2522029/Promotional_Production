#pragma once
#include "MyLib.h"
#include "ResultData.h"

class TotalData
{
private:

	//ゲーム全体のデータをまとめる構造体
    struct Data
    {
        int m_distance;         //プレイヤーが進んだ距離
        int m_enemies;          //倒した敵の数
        int m_exp;              //獲得した経験値
		float m_playTime;		//プレイ時間
    };

	Data m_totalData;	            //ゲーム全体のデータ
	const ResultData* m_resultData;	//現在のゲームのデータ(m_totalDataに加算させるときに重複しないようにするため)

public:

    static TotalData* GetInstance()
    {
        static TotalData instance;
        return &instance;
    }

	void AddData(const ResultData* resultData);	//ゲーム全体のデータにResultDataのデータを加算する関数

    //初期化
	void Initialize() { m_totalData = Data(); }

	//各データの取得
    int GetTotalDistance() const { return m_totalData.m_distance; }
    int GetTotalEnemies() const { return m_totalData.m_enemies; }
    int GetTotalExp() const { return m_totalData.m_exp; }
	float GetTotalPlayTime() const { return m_totalData.m_playTime; }


};