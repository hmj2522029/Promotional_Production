#include "Node.h"
#include <vector>
#include "Actor2D.h"
#include <algorithm>

Node::~Node()
{
	// 子ノードをすべて削除
	for (Node* node : m_children)
	{
		delete node;
		node = nullptr;
	}
	m_children.clear();

}


void Node::Start_()
{
	Start();
	m_updateFunc = &Node::Update;	//Start_関数を一回読んだらUpdate関数を呼ぶ

}

// 自身の削除
void Node::Destroy()
{
	// 親がいなければ何もしない
	if (!m_parent) return;

	// 既に削除済みなら何もしない
	if (m_isDestroyed) return;

	// 削除フラグを立てる
	m_isDestroyed = true;

	// 親に自身を削除させる
	m_parent->RemoveChild(this);
}

// 子ノードの追加
void Node::AddChild(Node* node)
{
	// 子の親を設定
	node->SetParent(this);

	// 子を登録
	m_children.push_back(node);

	// 子ノードの描画順をソートする必要があることを伝える
	m_needSort = true;

	// 子のリソース読み込み
	node->TreeLoad();
}

// 子ノードの削除
void Node::RemoveChild(Node* node)
{
	m_removeChildren.push_back(node);
}

// 子ノードを含むリソースの読み込み
void Node::TreeLoad()
{

	// 自身
	if (!m_isLoaded)
	{
		Load();
		m_isLoaded = true;
	}

	// 子
	for (Node* node : m_children)
	{
		node->TreeLoad();
	}
}

// 子ノードを含むリソースの解放
void Node::TreeRelease()
{
	// 自身
	if (m_isLoaded)
	{
		Release();
		m_isLoaded = false;
	}

	// 子
	for (Node* node : m_children)
	{
		node->TreeRelease();
	}
}

// 子ノードを含む更新
void Node::TreeUpdate()
{
	// 自身
	(this->*m_updateFunc)();

	// 子
	for (Node* node : m_children)
	{
		node->TreeUpdate();
	}

	// 子の削除
	for (Node* node : m_removeChildren)
	{
		node->TreeRelease();
		m_children.remove(node);	//子リストから削除(全て)
		delete node;
		node = nullptr;
	}
	m_removeChildren.clear();
}

// 子ノードを含む描画
void Node::TreeDraw()
{
	// 自身
	Draw();


	if(m_needSort)
	{
		//stable_sort → 同じ値なら元の順番を維持する
		// Actor2DだけdrawOrderでソート(sort(開始, 終了, 比較ルール))
		std::stable_sort(m_children.begin(), m_children.end(), [](Node* a, Node* b)
			{
	
				//同じ値じゃないなら
				if (a->GetDrawOrder() != b->GetDrawOrder())
				{
					return a->GetDrawOrder() < b->GetDrawOrder();
				}
	
				return false;	//値が同じなら順番維持
			});

		m_needSort = false;
	}

	// 子
	for (Node* node : m_children)
	{
		node->TreeDraw();
	}
}

void Node::SetDrawOrder(int drawOrder)
{
	
	m_drawOrder = drawOrder;

	//描画順を変更したら、親に子ノードの描画順をソートする必要があることを伝える
	if (m_parent)
	{
		m_parent->m_needSort = true;
	}


}