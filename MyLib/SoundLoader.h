#pragma once
#include "LoaderBase.h"

class SoundLoader : public LoaderBase
{
private:
	SoundLoader() {}

protected:

	//音声専用リソースの読み込み・破棄
	virtual int LoadResource(const std::string& path) override;
	virtual void DeleteResource(int id) override;

public:
	// シングルトン
	static SoundLoader* GetInstance()
	{
		static SoundLoader instance;
		return &instance;
	}

	//音声をロードしてIDを取得
	int LoadAndGetId(const std::string& path)
	{
		Load(path);
		return GetId(path);
	}

	//これをすることによって同じ関数でIDとパスの両方で削除できるようになる
	// オーバーロードで隠蔽される継承元の関数を可視化
	using LoaderBase::Delete;

	// リソースの破棄
	void Delete(const std::string& path)
	{
		LoadData* loadData = &m_image.at(path);
		Delete_(path, loadData->id, loadData);
	}
};
