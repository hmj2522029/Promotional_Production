#include "SceneGame.h"
#include "Player.h"
#include "Camera.h"
#include "StageManager.h"

SceneGame::SceneGame() :
	m_rootNode(nullptr),
	m_player(nullptr)
{

	m_rootNode = new Node();

	// カメラの生成
	m_camera = new Camera();
	m_rootNode->AddChild(m_camera);

	// プレイヤーの生成
	m_player = new Player(m_camera);
	m_rootNode->AddChild(m_player);

	// ステージマネージャーの生成
	m_stageManager = new StageManager(m_camera);
	m_rootNode->AddChild(m_stageManager);

	// 物理演算を稼働
	Physics2D::GetInstance()->Active();


}


void SceneGame::Update()
{




	m_rootNode->TreeUpdate();
}

void SceneGame::Draw()
{
	m_rootNode->TreeDraw();





}

