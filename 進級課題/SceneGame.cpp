#include "SceneGame.h"
#include "Player.h"
#include "Camera.h"
#include "StageManager.h"
#include "BattleScene.h"
#include "SceneStatus.h"
#include "SceneLevelUp.h"
#include "SceneResults.h"
#include "PlayerData.h"
#include "SceneClear.h"


void SceneGame::Initialize()
{

	Camera::GetInstance()->Initialization();

	//フォント読み込み
	AddFontResourceEx("Resource/PixelMplus/PixelMplus12-Regular.ttf", FR_PRIVATE, NULL);
	m_fontHandle = CreateFontToHandle("PixelMplus12", 25, -1);
	m_largeFontHandle = CreateFontToHandle("PixelMplus12", 40, -1);

	m_rootNode = new Node();

	//背景
	m_rootNode->AddChild(new Actor2D("background.jpg", Screen::Center - Vector2(0, 70), DrawLayer::BackgroundLayer));

	// ステージマネージャーの生成
	m_stageManager = new StageManager();
	m_rootNode->AddChild(m_stageManager);

	// プレイヤーの生成
	m_player = new Player();
	m_rootNode->AddChild(m_player);

	//リザルトのデータの生成
	m_resultData = new ResultData(m_stageManager->GetTileSize());
	m_rootNode->AddChild(m_resultData);

	//戦闘画面
	m_battleScene = new BattleScene(m_player, m_resultData);

	//ステータス画面
	m_sceneStatus = new SceneStatus(m_player);
	m_sceneStatus->Initialize();

	//レベルアップシーン
	m_sceneLevelUp = new SceneLevelUp(m_player);
	m_sceneLevelUp->Initialize();

	//リザルトシーン
	m_sceneResults = new SceneResults(m_resultData);
	
	//クリアシーン
	m_sceneClear = new SceneClear(m_resultData);


	// BGM
	m_bgm = SoundLoader::GetInstance()->LoadAndGetId("sound/ゲーム.mp3");
	ChangeVolumeSoundMem(70, m_bgm);


	//戦闘のBGM
	m_battleBgm = SoundLoader::GetInstance()->LoadAndGetId("sound/戦闘BGM.mp3");
	ChangeVolumeSoundMem(150, m_battleBgm);

	//クリアのBGM
	m_clearBgm = SoundLoader::GetInstance()->LoadAndGetId("sound/クリア.mp3");
	ChangeVolumeSoundMem(150, m_clearBgm);

	//リザルトのBGM
	m_resultBgm = SoundLoader::GetInstance()->LoadAndGetId("sound/リザルト.mp3");
	ChangeVolumeSoundMem(150, m_resultBgm);

	//レベルアップのBGM
	m_revelUpBgm = SoundLoader::GetInstance()->LoadAndGetId("sound/レベルアップ.mp3");
	ChangeVolumeSoundMem(150, m_revelUpBgm);

}

void SceneGame::Finalize()
{

	DeleteFontToHandle(m_fontHandle);

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

	if(m_sceneLevelUp)
	{
		SceneManager::GetInstance()->RemoveScene(m_sceneLevelUp);
		m_sceneLevelUp->Finalize();
		delete m_sceneLevelUp;
		m_sceneLevelUp = nullptr;
	}

	if(m_sceneResults)
	{
		SceneManager::GetInstance()->RemoveScene(m_sceneResults);
		m_sceneResults->Finalize();
		delete m_sceneResults;
		m_sceneResults = nullptr;
	}

	if(m_sceneClear)
	{
		SceneManager::GetInstance()->RemoveScene(m_sceneClear);
		m_sceneClear->Finalize();
		delete m_sceneClear;
		m_sceneClear = nullptr;
	}

	// BGM
	SoundLoader::GetInstance()->Delete(m_bgm);
	SoundLoader::GetInstance()->Delete(m_battleBgm);
	SoundLoader::GetInstance()->Delete(m_clearBgm);
	SoundLoader::GetInstance()->Delete(m_resultBgm);
	SoundLoader::GetInstance()->Delete(m_revelUpBgm);
	SoundLoader::GetInstance()->Delete("sound/ピコ音.mp3");

}


void SceneGame::Update()
{

	switch (m_fadeState)
	{
	case FadeState::Fade:
		if (ScreenFade::GetInstance()->IsFade())return;

		ScreenFade::GetInstance()->StartFadeIn(true);

		Physics2D::GetInstance()->Active();

		m_fadeState = FadeState::Run;

		break;

	case FadeState::Run:


		//BGMの切り替え
		PlayChangeBGM(GameState::State_Play);

		Camera::GetInstance()->Update();

		if (m_resultData->GetDistance() > 400) { m_stageManager->SetSituation(m_stageManager->MiddleStage); }
		if (m_resultData->GetDistance() > 800) { m_stageManager->SetSituation(m_stageManager->LateStage); }
	
		if (m_resultData->GetDistance() >= 1000 - m_stageManager->GetMaxScreenStage() + 2)
		{
			m_player->SetMoveMode(Player::MoveMode::SelfMove);
			Camera::GetInstance()->StopStage();
		}

		//クリア条件の判定
		if (m_resultData->GetDistance() >= 1000)
		{

			//BGMをクリアのBGMに切り替える
			PlayChangeBGM(GameState::State_Clear, false);
			
			//リザルトの初期化
			m_sceneClear->Initialize();

			Camera::GetInstance()->StopPlayer();

			//プレイヤーのデータ保存
			PlayerData::GetInstance()->SavePlayerStatus(m_player->ToPlayerStatus());

			Physics2D::GetInstance()->Deactive();
			SceneManager::GetInstance()->PushScene(m_sceneClear);
		}


		//戦闘画面に遷移するかどうかの判定
		if (m_player->GetTargetEnemy() != nullptr)
		{

			//BGMを戦闘のBGMに切り替える
			PlayChangeBGM(GameState::State_Battle);

			//フェードアウト
			ScreenFade::GetInstance()->StartFadeOut(true);
		
			//戦闘画面の初期化
			m_battleScene->Initialize();

			Physics2D::GetInstance()->Deactive();

			//戦闘が終わって戻って来る時はフェード中だから
			m_fadeState = FadeState::Fade;
	
			SceneManager::GetInstance()->PushScene(m_battleScene);
	
		}

		//ステージを止める
		if(m_player->m_status.IsDead())Camera::GetInstance()->StopStage();

		//プレイヤーの死亡アニメが終わったらリザルトシーンに遷移
		if (m_player->IsDeadAnimeEnds())
		{
			//BGMをリザルトのBGMに切り替える
			PlayChangeBGM(GameState::State_Results);

			//初期化
			m_sceneResults->Initialize();			

			//プレイヤーのデータ保存
			PlayerData::GetInstance()->SavePlayerStatus(m_player->ToPlayerStatus());

			Physics2D::GetInstance()->Deactive();
			SceneManager::GetInstance()->PushScene(m_sceneResults);

		}
	
		//プレイヤーがレベルアップしていたらシーンの追加
		if (m_player->GetLevelUpFlag())
		{
			//BGMをレベルアップのBGMに切り替える
			PlayChangeBGM(GameState::State_LevelUp, false);

			Physics2D::GetInstance()->Deactive();
	
			//レベルアップのシーンに切り替える
			SceneManager::GetInstance()->PushScene(m_sceneLevelUp);
	
		}
	
		//ステータス画面の表示
		if (Keyboard::isDown(KEY_INPUT_X))
		{

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
	
		break;
	}


}

void SceneGame::Draw()
{
	if (m_fadeState == FadeState::Fade) return; //フェード中は描画しない

	m_rootNode->TreeDraw();
	
	//操作説明
	DrawStringToHandle(
		Screen::Width / 5 * 3, Screen::Height - 25,
		"X: ステータス画面  SPACE: ジャンプ",
		GetColor(255, 255, 255),
		m_fontHandle,
		GetColor(0, 0, 0)
	);

	//何メートル進んだかの表示
	DrawStringToHandle(
		static_cast<int>(Screen::TopRight.x) - 60,
		30,
		"m",
		GetColor(255, 255, 255),
		m_largeFontHandle,
		GetColor(0, 0, 0)
	);
	NumberDrawer::DrawNumberTextFont(
		Vector2(static_cast<int>(Screen::TopRight.x) - 70, 30),
		m_resultData->GetDistance(),
		m_largeFontHandle,
		Align::Right
	);


}

void SceneGame::PlayChangeBGM(GameState gameState, bool loop)
{

	// 同じ状態なら何もしない
	if (gameState == m_prevState) return;

	//BGMを止める
	if (m_currentBGM != -1)
	{
		StopSoundMem(m_currentBGM);
	}

	switch (gameState)
	{
	case GameState::State_Play:
		m_currentBGM = m_bgm;
		break;

	case GameState::State_Battle:
		m_currentBGM = m_battleBgm;
		break;

	case GameState::State_LevelUp:
		m_currentBGM = m_revelUpBgm;
		break;

	case GameState::State_Results:
		m_currentBGM = m_resultBgm;
		break;

	case GameState::State_Clear:
		m_currentBGM = m_clearBgm;
		break;

	}

	if (loop)
	{
		PlaySoundMem(m_currentBGM, DX_PLAYTYPE_LOOP);
	}
	else
	{
		PlaySoundMem(m_currentBGM, DX_PLAYTYPE_BACK);
	}

	// 状態を保存
	m_prevState = gameState;

}
