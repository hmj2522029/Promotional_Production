#pragma once
#include <list>

class SceneBase;

class SceneManager
{
private:

	// シーン遷移のフェーズ(即切り替えによる問題の解決)
	enum class Phase
	{
		Run,		// 実行中
		Setup,		// 切り替え中
		Loading,	// ローディング
		Transition,	// 遷移
	};

	Phase m_phase;
	std::list<SceneBase*> m_sceneList;	// 実行中シーン(リストにすることによって複数のシーンを同時に出せる)
	SceneBase* m_nextScene;				// 遷移先のシーン(次のシーンを一時的に保存)
	SceneBase* m_loadingScene;			// ローディングシーン

	SceneManager() :
		m_phase(Phase::Setup),
		m_nextScene(nullptr),
		m_loadingScene(nullptr) {
	}

public:
	// シングルトン
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}

	// 初期シーンの設定
	void Setup(SceneBase* initScene, SceneBase* loadingScene = nullptr);

	// リソースの解放
	void Dispose();

	// シーンのロード
	void LoadScene(SceneBase* scene);

	// シーンの追加
	void PushScene(SceneBase* scene) { m_sceneList.push_back(scene); }

	// 最後に追加したシーンを削除(出しているシーンの一番上のを消す)
	void PopScene() { m_sceneList.pop_back(); }

	// 指定したシーンを削除
	void RemoveScene(SceneBase* scene) { m_sceneList.remove(scene); }

	//指定したシーンが一番上かどうか(実行しているシーン)
	bool TopScene(SceneBase* scene) { return m_sceneList.back() == scene ? true : false; }

	void Update();
	void Draw();
};
