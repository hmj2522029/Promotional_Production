#include "ResultData.h"
#include "Camera.h"

void ResultData::Load()
{

	Reset();


}

void ResultData::Update()
{

	//プレイ時間を更新する
	m_data.m_playTime += Time::GetInstance()->GetDeltaTime();

	//距離を更新する(プレイヤーがどれぐらい進んだか)
	m_data.m_distance = Camera::GetInstance()->GetPlayerPos().x / m_tile;

}

void ResultData::Reset()
{
	m_data.m_distance = 0;
	m_data.m_enemies = 0;
	m_data.m_exp = 0;
	m_data.m_playTime = 0.0f;
}