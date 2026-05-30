#pragma once
#include "MyLib.h"

class Player;
class Camera;
class StageManager;
class SceneStatus;
class BattleScene;
class SceneLevelUp;
class SceneResults;
class ResultData;
class SceneClear;

class SceneGame : public SceneBase
{
private:

	enum GameState
	{
		State_Play,
		State_Battle,
		State_LevelUp,
		State_Results,
		State_Clear
	};

	enum class FadeState
	{
		Fade,		//フェード中
		Run,		//実行中

	};
	
	Node* m_rootNode;
	Player* m_player;
	StageManager* m_stageManager;
	SceneStatus* m_sceneStatus;
	BattleScene* m_battleScene;
	SceneLevelUp* m_sceneLevelUp;
	SceneResults* m_sceneResults;
	ResultData* m_resultData;
	SceneClear* m_sceneClear;
	FadeState m_fadeState;
	GameState m_prevState;		//前の状態(同じ状態のときはBGMを変えないようにするため)

	int m_fontHandle;		//フォントハンドル
	int m_largeFontHandle;	//大きいフォントのハンドル
	int m_bgm;				//BGM
	int m_battleBgm;		//戦闘のBGM
	int m_clearBgm;			//クリアのBGM
	int m_resultBgm;		//リザルトのBGM
	int m_revelUpBgm;		//レベルアップのBGM
	int m_currentBGM;		//現在流れているBGMのID
	int m_display;			//表示用のSE

	void PlayChangeBGM(GameState gameState, bool loop = true);

public:

	SceneGame() :
		m_rootNode(nullptr),
		m_player(nullptr),
		m_stageManager(nullptr),
		m_sceneStatus(nullptr),
		m_battleScene(nullptr),
		m_sceneLevelUp(nullptr),
		m_sceneResults(nullptr),
		m_resultData(nullptr),
		m_sceneClear(nullptr),
		m_fadeState(FadeState::Run),
		m_prevState(static_cast<GameState>(-1)),	//初期状態は無し
		m_fontHandle(0),
		m_largeFontHandle(0),
		m_bgm(0),
		m_battleBgm(0),
		m_clearBgm(0),
		m_resultBgm(0),
		m_revelUpBgm(0),
		m_currentBGM(0),
		m_display(0)
	{ }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;

};