#pragma once
#include "Screen.h"
#include <list>
#include <unordered_map>
#include <unordered_set>


class Actor2D;

class Physics2D
{
private:

	static constexpr float Gravity = 9.8f;          // 重力加速度
	static constexpr float LimitSpeedFall = 50.0f;   // 最大落下速度
	static constexpr int LimitDistance =            // 衝突判定の距離制限(画面の対角線の半分の長さの2乗)
        ((std::max)(Screen::Width, Screen::Height) / 2) *
        ((std::max)(Screen::Width, Screen::Height) / 2);


	// 衝突判定のペアを表す構造体
    struct Pair
    {
        Actor2D* actor1;
        Actor2D* actor2;

        Pair(Actor2D* a1, Actor2D* a2)
            : actor1(a1), actor2(a2) {
        }
    };

	bool m_isActive;    // 物理演算が有効かどうか

	std::list<Actor2D*> m_actorList;    // 登録されているActor2Dのリスト

	std::unordered_map<Actor2D*, std::unordered_set<Actor2D*>> m_prevCallbackList;  // 前回のコールバックリスト


    Physics2D() :
        m_isActive(false)
    {}

public:

    static Physics2D* GetInstance()
    {
        static Physics2D instance;
        return &instance;
    }

	// 物理演算の有効化・無効化
    void Active() { m_isActive = true; }

    void Deactive() { m_isActive = false; }

	// Actor2Dの登録と削除
    void Register(Actor2D* actor)
    {
        m_actorList.push_back(actor);
    }

    void Remove(Actor2D* actor)
    {
        m_actorList.remove(actor);
    }

    void Update();

#ifdef _DEBUG
    void Draw() const;
#endif

};