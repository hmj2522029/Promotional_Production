#pragma once

class SceneGame;

// ゲームメインループ
class GameMain
{
private:
	int m_screen; //自作スクリーン

	SceneGame* m_sceneGame;	//ゲームシーン

public:
	GameMain();

	virtual ~GameMain();

	// メインループの実行
	void Run();
};
