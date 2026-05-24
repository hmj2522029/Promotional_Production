#pragma once
#include "MyLib.h"

class SceneCredit : public SceneBase
{
private:

	Node* m_rootNode;

	int m_fontHandle;


public:

	SceneCredit() :
		m_rootNode(nullptr),
		m_fontHandle(0)
	{ }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;


};