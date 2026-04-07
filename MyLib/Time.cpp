#include "Time.h"
#include "DxLib.h"

Time::Time() :
	m_prevTime(GetNowCount()),	//現在の時刻を取得して初期化(タイム呼ばれたタイミングで今の時刻を取得)
	m_deltaTime(0.0f)
{
}

void Time::Update()
{
	//現在の時刻を取得
	int currentTime = GetNowCount();	

	//デルタタイムを計算
	//前フレームの時刻と現在の時刻の差を計算
	m_deltaTime = (currentTime - m_prevTime) / 1000.0f; //ミリ秒を秒に変換

	//前フレームの時刻を更新
	m_prevTime = currentTime;
}

