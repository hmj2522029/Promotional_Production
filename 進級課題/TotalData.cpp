#include "TotalData.h"

void TotalData::AddData(const ResultData* resultData)
{
	if (m_resultData == resultData) return;	//同じResultDataを加算しないようにする

	m_totalData.m_distance += resultData->GetDistance();	//ゲーム全体の距離にResultDataの距離を加算する
	m_totalData.m_enemies += resultData->GetEnemies();	//ゲーム全体の倒した敵の数にResultDataの倒した敵の数を加算する
	m_totalData.m_exp += resultData->GetExp();			//ゲーム全体の獲得した経験値にResultDataの獲得した経験値を加算する
	m_totalData.m_playTime += resultData->GetPlayTime();	//ゲーム全体のプレイ時間にResultDataのプレイ時間を加算する

	m_resultData = resultData;	//ResultDataをTotalDataに保存する
}