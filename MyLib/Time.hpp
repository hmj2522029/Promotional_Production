#pragma once
#pragma once

// 時間に関するクラスや関数を定義するヘッダーファイル
class Time
{
private:
	int m_prevTime;		//前フレームの時刻
	float m_deltaTime;	// 前フレームからの経過時間

	Time();
public:
	//シングルトン
	static Time* GetInstance()
	{
		static Time instance;
		return &instance;
	}

	void Update();

	//デルタタイムの取得
	float GetDeltaTime() const { return m_deltaTime; }


};