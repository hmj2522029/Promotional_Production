#pragma once
#include <string>
#include <unordered_map>

// ローダーの基底クラス
class LoaderBase
{
protected:

	// パスのルートフォルダ
	static const std::string RootPath;

	// 管理用構造体(渡す情報を増やすため)
	struct LoadData
	{
		const int id;	// ロードしたリソースハンドル
		int count;		// この画像を何個のオブジェクトが使用しているか

		LoadData(int id) :
			id(id),
			count(0)
		{
		}
	};

	LoaderBase() {};

	//(mapの特性上同じキーは一個しか作られない)
	//画像パスとIDを管理する配列("player.png"(キー) → {id = 10, const = 2}(値))
	static std::unordered_map<std::string, LoadData> m_image;

	// idから画像パスとLoadDataへの逆引きコンテナ(10 → {"player.png", {id = 10, const = 2}})(削除が楽になる)
	static std::unordered_map<int, std::pair<const std::string, LoadData>*> m_reverseLookup;

	// リソースの種類に応じた読み込み
	virtual int LoadResource(const std::string& path) = 0;

	// リソースの種類に応じた破棄
	virtual void DeleteResource(int id) = 0;

	// リソースの破棄(各リソースの共通の破棄)
	virtual void Delete_(const std::string& path, int id, LoadData* loadData);

public:

	// リソースの読み込み
	virtual void Load(const std::string& path);

	// リソースIDの取得(.at(キーがなかったらエラーになる))
	virtual int GetId(const std::string& path) { return m_image.at(path).id; }

	// リソースの破棄(IDで消す)
	virtual void Delete(int id)
	{
		auto data = m_reverseLookup.find(id);
		Delete_(data->second->first, id, &data->second->second);
	}

};