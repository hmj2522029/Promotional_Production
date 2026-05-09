#include "PlayerData.h"
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <string>

void PlayerData::Initialize()
{
	//テキストファイルからデータを読み込んでPlayerStatusに変換して保存する
	m_playerStatus = ConvertToStatus(LoadInitialData("Data/Player/Status.txt"));


}

void PlayerData::SavePlayerStatus(const PlayerStatus& status)
{
	m_playerStatus = status;	//現在のプレイヤーのステータスを保管する
}


std::unordered_map<std::string, std::string> PlayerData::LoadInitialData(const std::string& path)
{
	std::unordered_map<std::string, std::string> data;  //データを格納するマップ
	std::ifstream file(path);   //ファイルを開く

	//ファイルが開けなかった場合は返す
	if (!file.is_open()) return data;

	std::string line;   //ファイルから1行ずつ読み込むための変数

	while (std::getline(file, line))    //ファイルから1行ずつ読み込むループ
	{
		// 空行 = データ終了
		if (line.empty()) continue;

		std::istringstream iss(line);   //行をスペースで区切って読み込むための文字列ストリーム
		std::string key, value;         //最初の文字列をkey、次の文字列をvalueとして読み込む

		//行からkeyとvalueを読み込む。読み込めなかった場合は次の行へ
		if (!(iss >> key >> value)) continue;

		data[key] = value;      //マップにkeyとvalueを保存する
	}


	return data;

}


PlayerData::PlayerStatus PlayerData::ConvertToStatus(const std::unordered_map<std::string, std::string>& data)
{
	//マップから特定のキーの値を整数に変換して取得するラムダ関数
	auto getInt = [&](const std::string& key, int defaultValue = 0) //ラムダ関数(その場で無名関数を作る)
		{
			if (data.count(key)) return std::stoi(data.at(key));    //キーが存在する場合はを整数に変換して返す(std::stoi)

			return defaultValue;
		};

	PlayerStatus player;

	//stringからintに変換してEnemyDataに格納(std::stoi)
	player.Level = getInt("Level");
	player.MaxHp = getInt("Hp");
	player.Attack = getInt("Attack");
	player.Defense = getInt("Defense");
	//もしステータスが増えたらここに追加する



	return player;
	
}

