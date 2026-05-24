#pragma once
#include "MyLib.h"
#include "ResultData.h"

class SceneClear : public SceneBase
{
private:


	Node* m_rootNode;
	ResultData* m_resultData;

	int m_largeFontHandle;		//大きいフォントのハンドル
	int m_smallFontHandle;		//小さいフォントのハンドル
	float m_timer;				//シーンに入ってからの時間

	//プレイ時間を計測する用
	int m_totalSeconds;		//プレイ時間の合計秒数
	int m_hours;			//時間
	int m_minutes;			//分
	int m_seconds;			//秒


public:
	SceneClear(ResultData* data) :
		m_rootNode(nullptr),
		m_resultData(data),
		m_largeFontHandle(0),
		m_smallFontHandle(0),
		m_timer(0.0f),
		m_totalSeconds(0),
		m_hours(0),
		m_minutes(0),
		m_seconds(0)
	{
	}

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
};