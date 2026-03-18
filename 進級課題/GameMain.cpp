#include "GameMain.h"
#include "GameConfig.h"
#include "SceneGame.h"
#include "MyLib.h"
#include "DxLib.h"

 GameMain::GameMain() :
	m_screen(0),
	m_scnenGame(nullptr)
{
	 Debug::Initialize();

	m_scnenGame = new SceneGame();
}


GameMain::~GameMain()
{
	// 自作スクリーンの破棄
	DeleteGraph(m_screen);

	if (m_scnenGame)
	{
		//m_scnenGame->Finalize();
		delete m_scnenGame;
		m_scnenGame = nullptr;
	}


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

	//背景を白にする
	SetBackgroundColor(255, 255, 255);

	// デバッグコンソール起動
	Debug::Initialize();


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

		//シーンゲームの更新
		m_scnenGame->Update();

		// 物理演算
		Physics2D::GetInstance()->Update();

		// 自作スクリーンに描画
		SetDrawScreen(m_screen);
		ClearDrawScreen();

		//シーンゲームの描画
		m_scnenGame->Draw();


		while(GetNowHiPerformanceCount() - frameStartTime < 1000000 / GameConfig::FPS);

#ifdef _DEBUG

		// 物理演算の描画
		Physics2D::GetInstance()->Draw();

		// ローダー
#endif


		// 自作スクリーンを裏画面に描画
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawGraph(0, 0, m_screen, false);
	
		// 裏画面と表画面をひっくり返す
		ScreenFlip();
	}



	// デバッグコンソールの破棄
	Debug::Finalize();

}
