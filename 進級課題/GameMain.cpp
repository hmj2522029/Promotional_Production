#include "GameMain.h"
#include "GameConfig.h"
#include "SceneGame.h"
#include "MyLib.h"
#include "DxLib.h"

 GameMain::GameMain() :
	 m_screen(0),
	 m_sceneGame()
{
	 Debug::Initialize();

	 m_sceneGame = new SceneGame();
	 //m_sceneGame->Initialize();
}


GameMain::~GameMain()
{
	// 自作スクリーンの破棄
	DeleteGraph(m_screen);	

	DxLib_End();
}

// メインループの実行
void GameMain::Run()
{
	// DxLib前処理
	ChangeWindowMode(GameConfig::WindowMode);	// ウィンドウモード
	SetMainWindowText(GameConfig::Title);	// ウィンドウタイトル
	SetGraphMode(Screen::Width, Screen::Height, GameConfig::ColorBit);	// ウィンドウサイズ
	SetAlwaysRunFlag(GameConfig::AlwaysRunFlag);	// 非アクティブ時の動作
	SetWaitVSyncFlag(false);

	if (DxLib_Init() == -1)
	{
		throw -1;
	}

	//背景を白にする(スクリーンの設定が白なら)
	if (Screen::ScreenColor == Screen::White) SetBackgroundColor(255, 255, 255);

	//背景を黒にする(スクリーンの設定が黒なら)
	if (Screen::ScreenColor == Screen::Black) SetBackgroundColor(0, 0, 0);

	// デバッグコンソール起動
	Debug::Initialize();

	//シーン起動
	SceneManager::GetInstance()->Setup(new SceneGame);


	// スクリーン作成
	m_screen = MakeScreen(Screen::Width, Screen::Height);


#ifdef _DEBUG
	//FPS計測
	double fps = 0.0;
	double frameTime = 0.0;
	int frameCount = 0;
#endif

	LONGLONG frameStartTime;

	while (true)
	{
		// フレームの開始時間を取得(単位マイクロ「秒
		frameStartTime = GetNowHiPerformanceCount();
		if (ProcessMessage())
		{
			break;
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		//入力デバイスの更新
		input::Update();

		// 時間の更新
		Time::GetInstance()->Update();

		//シーンの更新
		SceneManager::GetInstance()->Update();
		//m_sceneGame->Update();

		// 物理演算
		Physics2D::GetInstance()->Update();

		// 自作スクリーンに描画
		SetDrawScreen(m_screen);
		ClearDrawScreen();

		//シーンの描画
		SceneManager::GetInstance()->Draw();
		//m_sceneGame->Draw();

		while(GetNowHiPerformanceCount() - frameStartTime < 1000000 / GameConfig::FPS);

#ifdef _DEBUG

		// 物理演算の描画
		Physics2D::GetInstance()->Draw();

		// ローダー
#endif

		// フェード
		ScreenFade::GetInstance()->Update(m_screen);

		// 自作スクリーンを裏画面に描画
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawGraph(0, 0, m_screen, false);
	
		// 裏画面と表画面をひっくり返す
		ScreenFlip();
	}

	// シーンの破棄
	SceneManager::GetInstance()->Dispose();
	//m_sceneGame->Finalize();

	// デバッグコンソールの破棄
	Debug::Finalize();

}
