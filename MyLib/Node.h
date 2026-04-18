#pragma once
#include <list>

class Node
{
private:

	Node* m_parent;						// 親のポインタ
	std::list<Node*> m_children;		// 子のポインタリスト
	std::list<Node*> m_removeChildren;	// 削除する子のポインタリスト
	bool m_isDestroyed;					// Destroy関数を実行済みか


	bool m_isLoaded;				// Load関数を実行済みか
	void (Node::* m_updateFunc)();	//一回だけスタート関数を呼ぶ

	void Start_();

protected:
	virtual void Load() {}
	virtual void Release() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void Draw() {}

	int m_drawOrder;	//レイヤー

	// 自身の削除
	void Destroy();

	// 親を設定
	void SetParent(Node* node) { m_parent = node; }

	// 親を取得
	Node* GetParent() { return m_parent; }


public:
	Node() :
		m_parent(nullptr),
		m_isDestroyed(false),
		m_isLoaded(false),
		m_updateFunc(&Node::Start_),	//Nodeが生成されたらStart_関数を呼ぶ
		m_drawOrder(0)
	{
	}

	virtual ~Node();

	virtual void TreeLoad();
	virtual void TreeRelease();
	virtual void TreeUpdate();
	virtual void TreeDraw();

	// 子ノードの追加
	void AddChild(Node* node);

	// 子ノードの削除
	void RemoveChild(Node* node);

	//レイヤー設定
	int GetDrawOrder() const { return m_drawOrder; }
	void SetDrawOrder(int order) { m_drawOrder = order; }


};