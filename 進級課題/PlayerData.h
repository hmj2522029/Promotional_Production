#pragma once
#include "MyLib.h"
#include <unordered_map>

//ScenePrepに戻ってもプレイヤーのステータスを保持するためのクラス
class PlayerData
{
public:
	struct PlayerStatus
	{
		int Level;		//レベル
		int MaxHp;		//最大HP
		int Attack;		//攻撃力
		int Defense;	//防御力
		int Exp;		//経験値
		int NextExp;	//次のレベルまでの経験値
	};


	//シングルトン
	static PlayerData* GetInstance()
	{
		static PlayerData instance;
		return &instance;
	}

	//初期化
	void Initialize();

	//テキストファイルからデータを読み込む関数(単体)
	std::unordered_map<std::string, std::string> LoadInitialData(const std::string& path);

	//テキストファイルからデータを読み込んでPlayerStatusに変換する関数
	PlayerStatus ConvertToStatus(const std::unordered_map<std::string, std::string>& data);

	//現在のプレイヤーのステータスを保管する関数
	void SavePlayerStatus(const PlayerStatus& status);

	//現在のプレイヤーのステータスを取得する関数
	PlayerStatus GetPlayerStatus() const { return m_playerStatus; }

private:

	PlayerStatus m_playerStatus;	//プレイヤーのステータス

};