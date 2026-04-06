#include "SceneGame.h"
#include "Player.h"
#include "Camera.h"
#include "StageManager.h"
#include "SceneGameUI.h"
#include "BattleScene.h"


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

	// UIの生成
	m_sceneGameUI = new SceneGameUI(m_player);
	m_rootNode->AddChild(m_sceneGameUI);


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
	//戦闘画面に遷移するかどうかの判定
	if (m_player->GetTargetEnemy() != nullptr)
	{
		//フェードアウト
		ScreenFade::GetInstance()->StartFadeOut(true);

		SceneManager::GetInstance()->PushScene(new BattleScene(m_player, m_player->GetTargetEnemy(), m_camera));

	}



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

