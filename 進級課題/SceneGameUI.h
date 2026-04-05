#pragma once
#include "MyLib.h"

class Player;

class SceneGameUI : public Node
{
private:

	Transform m_transform;	//フォントを描画する基準点の座標
	const Player* m_player;
	int m_fontHandle;	// フォントハンドル

	//UIの座標
	Vector2 m_hpPos;
	Vector2 m_expPos;
	Vector2 m_levelPos;


protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;


public:

	SceneGameUI(const Player* player);

};