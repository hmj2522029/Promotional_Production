#pragma once
#include "MyLib.h"

class Player;
class Enemy;
class Camera;

class BattleScene : public SceneBase
{
private:

	enum class FadeState
	{
		Fade,		//フェード中
		Run,		//実行中

	};

	FadeState m_fadeState;	//フェード状態
	Player* m_player;	//プレイヤー
	Enemy* m_enemy;		//敵
	Camera* m_camera;	//カメラ

public:

	BattleScene(Player* player, Enemy* enemy, Camera* camera) :
		m_fadeState(FadeState::Fade),
		m_player(player),
		m_enemy(enemy),
		m_camera(camera)
	{
	}
	
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;

};