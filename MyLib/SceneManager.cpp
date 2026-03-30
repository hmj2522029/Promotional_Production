#include "SceneManager.h"
#include "SceneBase.h"
#include "Physics2D.h"
#include "ScreenFade.h"
#include "DxLib.h"

void SceneManager::Setup(SceneBase* initScene, SceneBase* loadingScene)
{
	// ローディングシーンは同期読み込み
	SetUseASyncLoadFlag(false);
	m_loadingScene = loadingScene;
	if (m_loadingScene) m_loadingScene->Initialize();

	// 非同期読み込み開始
	SetUseASyncLoadFlag(true);

	m_nextScene = initScene;
	m_phase = Phase::Setup;
}

void SceneManager::Dispose()
{
	// 実行中シーンの破棄
	for (auto scene : m_sceneList)
	{
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}
	m_sceneList.clear();

	// 遷移先シーンの破棄
	if (m_nextScene)
	{
		m_nextScene->Finalize();
		delete m_nextScene;
		m_nextScene = nullptr;
	}

	// ローディングシーンの破棄
	if (m_loadingScene)
	{
		m_loadingScene->Finalize();
		delete m_loadingScene;
		m_loadingScene = nullptr;
	}
}

void SceneManager::LoadScene(SceneBase* scene)
{
	// シーン切り替え中ならキャンセル(一回だけしか通さないようにするため)
	if (m_nextScene)
	{
		delete scene;
		scene = nullptr;
		return;
	}

	m_nextScene = scene;
	m_phase = Phase::Setup;

	// フェードアウト
	ScreenFade::GetInstance()->StartFadeOut();
}

void SceneManager::Update()
{
	switch (m_phase)
	{
	case Phase::Run:
		m_sceneList.back()->Update();	//シーンの一番上のUpdateを更新している
		break;

	case Phase::Setup:	//準備

		// 実行中シーンの更新
		if (!m_sceneList.empty()) m_sceneList.back()->Update();

		// フェードアウトが終わるまで待機
		if (ScreenFade::GetInstance()->IsFade()) break;

		// 遷移先シーンの初期化
		m_nextScene->Initialize();

		// 実行中シーンがあれば破棄(次のシーンに切り替えるため)
		for (auto scene : m_sceneList)
		{
			scene->Finalize();
			delete scene;
			scene = nullptr;
		}
		m_sceneList.clear();

		// 物理演算を止める(ロード中に動かないようにするため)
		Physics2D::GetInstance()->Deactive();

		// ローディングシーン
		ScreenFade::GetInstance()->StartFadeIn(0.2f);
		m_phase = Phase::Loading;
		break;

		// ローディング
	case Phase::Loading:
		if (m_loadingScene) m_loadingScene->Update();

		// フェードインとロードが終わるまで待機
		if (ScreenFade::GetInstance()->IsFade() || GetASyncLoadNum() > 0) break;

		// 遷移へ
		ScreenFade::GetInstance()->StartFadeOut(0.2f);
		m_phase = Phase::Transition;
		break;

		// 遷移
	case Phase::Transition:
		if (m_loadingScene) m_loadingScene->Update();

		// フェードアウトが終わるまで待機
		if (ScreenFade::GetInstance()->IsFade()) break;

		// 遷移
		PushScene(m_nextScene);
		m_nextScene = nullptr;

		// 物理演算を稼働(ロード中が終われば稼働)
		Physics2D::GetInstance()->Active();

		// フェードイン
		ScreenFade::GetInstance()->StartFadeIn(0.2f);

		m_phase = Phase::Run;
		break;
	}
}

void SceneManager::Draw()
{
	//各シーンの描画
	for (auto scene : m_sceneList)	
	{
		scene->Draw();
	}

	// ローディングシーン
	if (m_loadingScene && (m_phase == Phase::Loading || m_phase == Phase::Transition))
	{
		m_loadingScene->Draw();
	}
}
