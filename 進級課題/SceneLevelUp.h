#pragma once
#include "MyLib.h"
#include <vector>

class Player;

class SceneLevelUp : public SceneBase
{
private:

	//前のステータスのを保存する用の構造体
	struct PreviousStatus
	{

		int Level;		//レベル
		int MaxHp;		//最大HP
		int Attack;		//攻撃力
		int Defense;	//防御力

		PreviousStatus(int level, int maxHp, int attack, int defense)
			: Level(level),
			MaxHp(maxHp), 
			Attack(attack), 
			Defense(defense) 
		{
		}


	};

	enum class State
	{
		LevelUpText,	//レベルアップのテキスト
		LevelUpTable,	//レベルアップ表
		Wait		
	};

	Node* m_rootNode;
	Player* m_player;
	State m_state;
	PreviousStatus m_previousStatus;
	Tween m_tweenScale;		//レベルアップの文字を大きさを変える用

	float m_timer;
	int m_largeFontHandle;
	int m_smallFontHandle;

	//レベルアップの文字用
	int m_width;	
	int m_height;

	int m_se;	//SE
	int m_step;	//SEのタイミングを管理する用

	std::vector<float> m_timings = { 1.0f, 2.0f, 3.0f, 4.0f };	//SEを鳴らすタイミング

public:

	SceneLevelUp(Player* player) :
		m_rootNode(nullptr),
		m_player(player),
		m_state(State::LevelUpText),
		m_previousStatus(0, 0, 0, 0),	//一旦今は0にしておく
		m_tweenScale(),
		m_timer(0),
		m_largeFontHandle(0),
		m_smallFontHandle(0),
		m_width(0),
		m_height(0),
		m_se(0),
		m_step(0)
	{ }

	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;

};