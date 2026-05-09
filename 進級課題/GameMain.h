#pragma once

class SceneGame;

// ゲームメインループ
class GameMain
{
private:
	int m_screen; //自作スクリーン

public:
	GameMain();

	virtual ~GameMain();

	// メインループの実行
	void Run();
};
