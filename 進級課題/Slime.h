#pragma once
#include "MyLib.h"
#include "Enemy.h"
#include "TileContext.h"
#include "Status.h"

class Camera;

class Slime : public Enemy
{
private:

	//ステータス情報(初期)
	static constexpr int Level = 1;			//レベル(初期)
	static constexpr int Hp = 15;			//HP(初期)
	static constexpr int Attack = 15;		//攻撃力(初期)
	static constexpr int Defense = 2;		//防御力(初期)
	static constexpr int ExpReward = 10;	//倒したときの経験値(初期)


	static constexpr Vector2 GridSize = Vector2(32, 32);	//グリッドサイズ

	Vector2 m_size;			//サイズ(当たり判定)
	Vector2 m_offsetPos;	//座標をずらすため()
	Vector2 m_offsetCol;	//座標をずらすため(当たり判定)
	TileContext m_tileContext;
	Camera* m_camera;

protected:
	virtual void Update() override;
	virtual void Draw() override;

public: 

	enum class Anime
	{
		Idle,
		Ran,
		Die,

		Length,
	};
	static constexpr Animation2D AnimeData[static_cast<int>(Anime::Length)] =
	{
		Animation2D("FreeSlime/slime_idle.png", 4, 7, true),
		Animation2D("FreeSlime/slime_run.png", 6, 11, true),
		Animation2D("FreeSlime/slime_die.png", 5, 9, false),
	};



	Slime(const TileContext& tile, Camera* camera);

	int GetExpReward() const { return m_expReward * m_status.GetLevel(); }


};