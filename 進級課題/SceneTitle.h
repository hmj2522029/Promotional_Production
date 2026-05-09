#pragma once
#include "MyLib.h"

class SceneTitle : public SceneBase
{
private:
	static constexpr float WaitTransitionTime = 0.5f;

	Node* m_rootNode;
	int m_fontHandle;			//フォントハンドル
	float m_waitTransitionTime;	//遷移までの待ち時間	


public:

	SceneTitle() :
		m_rootNode(nullptr),
		m_fontHandle(0),
		m_waitTransitionTime(WaitTransitionTime)
	{ }


	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;

};