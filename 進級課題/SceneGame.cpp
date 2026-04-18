#include "SceneGame.h"
#include "Player.h"
#include "Camera.h"
#include "StageManager.h"
#include "SceneGameUI.h"
#include "BattleScene.h"


void SceneGame::Initialize()
{
	m_rootNode = new Node();

	//背景
	m_rootNode->AddChild(new Actor2D("background.jpg", Screen::Center - Vector2(0, 70), DrawLayer::BackgroundLayer));

	// カメラの生成
	m_camera = new Camera();
	m_rootNode->AddChild(m_camera);


	// ステージマネージャーの生成
	m_stageManager = new StageManager(m_camera);
	m_rootNode->AddChild(m_stageManager);

	// プレイヤーの生成
	m_player = new Player(m_camera);
	m_rootNode->AddChild(m_player);

	// UIの生成
	m_sceneGameUI = new SceneGameUI(m_player);
	m_rootNode->AddChild(m_sceneGameUI);

	//戦闘画面
	m_battleScene = new BattleScene(m_player);
	m_battleScene->Initialize();

	//リザルト画面

}

void SceneGame::Finalize()
{

	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		delete m_rootNode;
		m_rootNode = nullptr;
	}

	if (m_battleScene)
	{
		SceneManager::GetInstance()->RemoveScene(m_battleScene);
		m_battleScene->Finalize();
		delete m_battleScene;
		m_battleScene = nullptr;

	}


}


void SceneGame::Update()
{
	//カメラを動かす
	m_camera->Move();

	//戦闘画面に遷移するかどうかの判定
	if (m_player->GetTargetEnemy() != nullptr)
	{
		//止める
		m_camera->Stop();

		//フェードアウト
		ScreenFade::GetInstance()->StartFadeOut(true);

		SceneManager::GetInstance()->PushScene(m_battleScene);

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

