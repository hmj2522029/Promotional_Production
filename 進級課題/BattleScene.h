#pragma once
#include "MyLib.h"

class Player;
class Enemy;
class Camera;

class BattleScene : public SceneBase
{
private:
	Player* m_player;	//プレイヤー
	Enemy* m_enemy;		//敵
	Camera* m_camera;	//カメラ

public:

	BattleScene(Player* player, Enemy* enemy, Camera* camera) :
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