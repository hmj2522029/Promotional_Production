#pragma once
#include "BattleState.h"
#include "MyLib.h"

class Player;
class Enemy;
class ResultData;

class BattleScene : public SceneBase
{
private:

	enum class FadeState
	{
		Fade,		//フェード中
		Run,		//実行中

	};

	
	Node* m_rootNode;
	FadeState m_fadeState;		//フェード状態
	Player* m_player;			//プレイヤー
	Enemy* m_enemy;				//当たった敵(ステータスとかのデータ取得)
	Actor2D* m_drawingEnemy;	//描画している敵(当たった敵のデータからその敵の描画)
	BattleState* m_state;		//状態
	ResultData* m_resultData;	//リザルトデータに加算するためのデータ

	int m_fontHandle;		//フォントハンドル
	int m_smallFontHandle;	//小さいフォントハンドル
	float m_timer;			//リザルトデータに加算するためのタイマー	

public:

	BattleScene(Player* player, ResultData* resultData) :
		m_rootNode(nullptr),
		m_fadeState(FadeState::Fade),
		m_player(player),
		m_enemy(nullptr),				//当たった敵
		m_drawingEnemy(nullptr),		//描画している敵
		m_state(nullptr),
		m_resultData(resultData),
		m_fontHandle(0),
		m_smallFontHandle(0),
		m_timer(0)
	{
	}
	
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;


};