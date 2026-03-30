#include "SceneGame.h"
#include "Player.h"
#include "Camera.h"
#include "StageManager.h"


void SceneGame::Initialize()
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


	//物理起動
	//Physics2D::GetInstance()->Active();
}

void SceneGame::Finalize()
{

	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		delete m_rootNode;
		m_rootNode = nullptr;
	}


}


void SceneGame::Update()
{
#ifdef _DEBUG

	//デバッグ用のブロックの描画を切り替える
	if (Keyboard::isPress(KEY_INPUT_F1))
	{
		m_stageManager->ToggleBlockDraw();
	}


#endif



	m_rootNode->TreeUpdate();
}

void SceneGame::Draw()
{
	m_rootNode->TreeDraw();





}

