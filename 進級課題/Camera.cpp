#include "Camera.h"

Camera::Camera() :
	m_stageVelocity(0,0),
	m_stagePos(SpawnPos),  
	m_playerVelocity(0, 0),
	m_playerPos(SpawnPos)
{

} 

void Camera::Initialization()
{
	m_stagePos = SpawnPos;
	m_playerPos = SpawnPos;

	Camera::MovePlayer();	// カメラの移動を止める
	Camera::MoveStage();	// カメラを動かす
}

void Camera::Update()
{
	//Debug::Log("Camera Pos: %d\n",static_cast<int>(m_position.x) / 80);

	// カメラの位置を速度に応じて更新
	m_stagePos += m_stageVelocity; 
	m_playerPos += m_playerVelocity;
}