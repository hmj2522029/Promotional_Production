#include "SceneGame.h"
#include "Player.h"
#include "Camera.h"
#include "StageManager.h"
#include "BattleScene.h"
#include "SceneStatus.h"


void SceneGame::Initialize()
{

	//フォント読み込み
	AddFontResourceEx("Resource/PixelMplus/PixelMplus12-Regular.ttf", FR_PRIVATE, NULL);
	m_fontHandle = CreateFontToHandle("PixelMplus12", 25, -1);


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

	//戦闘画面
	m_battleScene = new BattleScene(m_player);

	//ステータス画面
	m_sceneStatus = new SceneStatus(m_player);
	m_sceneStatus->Initialize();

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

	if(m_sceneStatus)
	{
		SceneManager::GetInstance()->RemoveScene(m_sceneStatus);
		m_sceneStatus->Finalize();
		delete m_sceneStatus;
		m_sceneStatus = nullptr;
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

		Debug::Log("戦闘画面に遷移");

		//戦闘画面の初期化
		m_battleScene->Initialize();

		SceneManager::GetInstance()->PushScene(m_battleScene);

	}

	//プレイヤーがレベルアップしていたらシーンの追加
	if (m_player->GetLevelUpFlag())
	{
		//止める
		m_camera->Stop();

		//レベルアップフラグのリセット
		m_player->ResetLevelUpFlag();

		//レベルアップのシーンに切り替える
		//SceneManager::GetInstance()->PushScene());

	}

	//ステータス画面の表示
	if (Keyboard::isDown(KEY_INPUT_X))
	{
		//止める
		m_camera->Stop();

		Physics2D::GetInstance()->Deactive();
		SceneManager::GetInstance()->PushScene(m_sceneStatus);
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

	DrawStringToHandle(
		Screen::Width / 5 * 3, Screen::Height - 25,
		"X: ステータス画面  SPACE: ジャンプ",
		GetColor(255, 255, 255),
		m_fontHandle,
		GetColor(0, 0, 0)
	);




}

