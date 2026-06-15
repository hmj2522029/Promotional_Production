#pragma once
#include "MyLib.h"

class Player;

class PrepPlayerController : public Node
{
public:

	enum class DemoState
	{
		Enter,   // 入ってくる
		Wait,    // 待機
		Exit     // 出ていく
	};

private:

	Tween m_tween;
	DemoState m_state;
	Player* m_player;	//プレイヤーへのポインタ

	float m_InterpolatedValue;
	bool m_isSceneGameButton;	//ボタンが押されているか(シーンゲーム遷移の)
	bool m_isExitStateEnd;		//状態のExitが終わっているかどうか

	//状態の変更
	void ChangeState(DemoState state);

public:


	PrepPlayerController();


	virtual void Update() override;

	Player* GetPlayer() const { return m_player; }

	//今の状態
	DemoState CurrentState() { return m_state; }

	//ボタン押されたことを通知
	void ButtonPressed() { m_isSceneGameButton = true; }

	bool GetExitStateEnd() const { return m_isExitStateEnd; }

}; 