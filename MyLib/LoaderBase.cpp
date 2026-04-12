#include "LoaderBase.h"
#include "DxLib.h"

const std::string LoaderBase::RootPath = "Resource/";
std::unordered_map<std::string, LoaderBase::LoadData> LoaderBase::m_image;
std::unordered_map<int, std::pair<const std::string, LoaderBase::LoadData>*> LoaderBase::m_reverseLookup;


// リソースの読み込み
void LoaderBase::Load(const std::string& path)
{
	LoadData* loadData = nullptr;

	// 既に読み込んでいるかをチェック
	auto data = m_image.find(path);
	if (data != m_image.end())
	{
		// 読み込んでいたので、読み込み済みのデータで処理する
		loadData = &data->second;
	}
	else
	{
		// 読み込んでいなかったので、新規にロードして登録する

		// ロード
		int id = LoadResource(RootPath + path);

		// 登録

		//(emplace(mapの配列に追加する)戻り値(pair<追加されたデータの位置, 追加できたか(bool)>))
		auto& pair = *m_image.emplace(path, LoadData(id)).first;	//.first = 追加されたデータの位置
		m_reverseLookup.emplace(id, &pair);

		loadData = &pair.second;
	}

	// 読み込みカウントを増やす
	loadData->count++;
}

// リソースの破棄
void LoaderBase::Delete_(const std::string& path, int id, LoadData* loadData)
{
	// 読み込みカウントを減らす
	loadData->count--;

	// 読み込みカウントが0になったら破棄
	if (loadData->count <= 0)
	{
		DeleteResource(id);
		m_reverseLookup.erase(id);
		m_image.erase(path);
	}
}

