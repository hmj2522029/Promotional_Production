#include "Character.h"
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <string>

std::unordered_map<std::string, std::string> Character::LoadKeyValueFile(const std::string& path)
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