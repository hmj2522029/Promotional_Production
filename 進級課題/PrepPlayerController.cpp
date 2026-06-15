#include "PrepPlayerController.h"
#include "Player.h"

PrepPlayerController::PrepPlayerController() :
	m_tween(),
	m_state(),	
	m_player(nullptr),
	m_InterpolatedValue(0),
	m_isSceneGameButton(false)
{
	
	ChangeState(DemoState::Enter);

	//プレイヤーの生成
	m_player = new Player(Vector2(-50, 478));
	AddChild(m_player);
	m_player->StopUpdating();
	

}

void PrepPlayerController::Update()
{
	
	m_tween.Update();

	switch (m_state)
	{
	case DemoState::Enter:

		//移動している前提だからアニメーションを走りに変える
		m_player->AnimationChange("Run");

		//今補間している値を取得
		m_InterpolatedValue = m_tween.GetValue();

		m_player->SetPosition(Vector2(m_InterpolatedValue, 490));

		if (!m_tween.IsPlaying())
		{
			
			ChangeState(DemoState::Wait);

		}

		break;

	case DemoState::Wait:

		//待機(止まっている)からアニメーションを待機に変える
		m_player->AnimationChange("Idle");

		// ボタンを押され待ち
		if (m_isSceneGameButton)
		{

			ChangeState(DemoState::Exit);

		}

		break;

	case DemoState::Exit:

		//今補間している値を取得
		m_InterpolatedValue = m_tween.GetValue();

		m_player->SetPosition(Vector2(m_InterpolatedValue, 495));

		if (!m_tween.IsPlaying())
		{
			m_isExitStateEnd = false;
		}

		break;
	}

}

void PrepPlayerController::ChangeState(DemoState state)
{
	m_state = state;

	switch (m_state)
	{
	case DemoState::Enter:
		m_tween.Start(3.0f, -50.0f, Screen::Center.x);
		break;

	case DemoState::Exit:
		m_tween.Start(3.0f, m_player->GetPosition().x, Screen::Right + 50);
		break;
	}
}

