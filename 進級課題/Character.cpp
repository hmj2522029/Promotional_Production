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

void Character::DrawHPBar(int x, int y, int currentHP, int maxHP, int width, int height)
{
	if (maxHP <= 0) return;

	//HPの割合（0.0?1.0）
	float rate = (float)currentHP / (float)maxHP;

	//範囲制限
	if (rate < 0.0f) rate = 0.0f;
	if (rate > 1.0f) rate = 1.0f;

	//HPバーの長さ
	int barWidth = (int)(width * rate);

	//HPバーの枠
	DrawBox(x - 2, y - 2, x + width + 2, y + height + 2, GetColor(200, 200, 200), TRUE);

	//背景（黒）
	DrawBox(x, y, x + width, y + height, GetColor(0, 0, 0), TRUE);

	//HP部分（色変化付き）
	int color;

	if (rate > 0.5f)
		color = GetColor(0, 255, 0);   // 緑
	else if (rate > 0.2f)
		color = GetColor(255, 255, 0); // 黄色
	else
		color = GetColor(255, 0, 0);   // 赤

	//HPバーを描画
	DrawBox(x, y, x + barWidth, y + height, color, TRUE);

}