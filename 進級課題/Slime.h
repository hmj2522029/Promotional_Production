#pragma once
#include "MyLib.h"
#include "Enemy.h"
#include "TileContext.h"
#include "Status.h"

class Camera;

class Slime : public Enemy
{
private:

	static constexpr int LevelPerDistance = 20;	//距離何ごとにレベルを上げるか(メートル)

	//レベルアップの時のステータスの上昇値の範囲
	static constexpr int UpHpMax = 7;		//レベルアップの時のHPの上昇値の最大値
	static constexpr int UpHpMin = 4;		//レベルアップの時のHPの上昇値の最小値
	static constexpr int UpAttackMax = 3;	//レベルアップの時の攻撃力の上昇値の最大値
	static constexpr int UpAttackMin = 1;	//レベルアップの時の攻撃力の上昇値の最小値
	static constexpr int UpDefenseMax = 2;	//レベルアップの時の防御力の上昇値の最大値
	static constexpr int UpDefenseMin = 1;	//レベルアップの時の防御力の上昇値の最小値
	static constexpr int UpExpReward = 30;	//レベルアップの時の経験値の上昇値


	//距離によってレベルを変えるためのパラメータ
	static constexpr float Multiplier = 0.5f;	// 成長倍率
	static constexpr int MinOffset = 0;			// 最低補正
	static constexpr int MaxOffset = 3;			// 最大補正

	static constexpr Vector2 GridSize = Vector2(32, 32);	//グリッドサイズ

	Vector2 m_size;			//サイズ(当たり判定)
	Vector2 m_offsetPos;	//座標をずらすため()
	Vector2 m_offsetCol;	//座標をずらすため(当たり判定)
	TileContext m_tileContext;

protected:
	virtual void Update() override;
	virtual void Draw() override;

public: 

	//アニメーションデータ
	std::vector<Animation2D> AnimeData;

	Slime(const TileContext& tile);

	int GetExpReward() const { return m_expReward * m_status.GetLevel(); }


};