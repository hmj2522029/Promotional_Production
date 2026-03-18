#include "Physics2D.h"
#include "Actor2D.h"
#include "Time.h"
#include "Rigidbody2D.h"
#include "Vector2.h"
#include "Collider.h"
#include "Collision.h"


void Physics2D::Update()
{

	if (!m_isActive) return;


	//デルタタイムの取得(落下速度を一定にする為)
	float dt = Time::GetInstance()->GetDeltaTime();

	// 登録されているActor2Dのリストをループして、物理演算を行う
	for(auto actor : m_actorList)
	{
		if (actor == nullptr) continue;	// Actor2Dがnullptrの場合はスキップ

		Rigidbody2D& body = actor->m_rigidbody2d;

		// staticな剛体は物理演算を行わないのでスキップ
		if (body.GetBodyType() == Rigidbody2D::Type::Static) continue;	

		//重力(キネマティックは重力がかからない)
		if (body.GetBodyType() == Rigidbody2D::Type::Dynamic)
		{


			body.velocity.y += Gravity * body.gravityScale * dt;	

			float speed = body.velocity.y;

			//落下速度の制限(最大落下速度を超えないようにする)
			if (body.velocity.y > LimitSpeedFall)
			{
				body.velocity.y = LimitSpeedFall;	
			}

		}

		// 移動
		actor->m_transform.position += body.velocity;
	}




	//衝突判定のペア作成
	std::list<Pair> pairList;	//仮のペアリスト
	for(auto it1 = m_actorList.begin(); it1 != m_actorList.end(); ++it1)
	{
		// 内側のループの開始位置を外側のループの次の要素に設定(同じペアを調べないようにする為)
		auto it2 = it1;	
		++it2;			

		for (; it2 != m_actorList.end(); ++it2)
		{

			Actor2D* actor1 = *it1;
			Actor2D* actor2 = *it2;

			if (actor1 == nullptr || actor2 == nullptr) continue;	// Actor2Dがnullptrの場合はスキップ

			// 静的オブジェクト同士はスキップ
			if (actor1->m_rigidbody2d.GetBodyType() == Rigidbody2D::Type::Static &&
				actor2->m_rigidbody2d.GetBodyType() == Rigidbody2D::Type::Static) continue;

			// 衝突判定の形状が無かったらスキップ
			if (!actor1->GetCollider() || 
				!actor2->GetCollider()) continue;

			// 相手が無視すべきタグならスキップ
			if (actor1->GetCollider()->GetPhysicsBehavior(actor2->GetTag()) == PhysicsBehavior::Ignore ||
				actor2->GetCollider()->GetPhysicsBehavior(actor1->GetTag()) == PhysicsBehavior::Ignore) continue;

			// 一定以上離れているものはスキップ(全ての当たり判定を調べていると処理の回数が多くなるから)
			if ((actor1->GetPosition() - actor2->GetPosition()).SqrMagnitude() > LimitDistance) continue;

			// ペア登録
			pairList.push_back(Pair(actor1, actor2));

		}
	}

	// 衝突判定
	std::unordered_map<Actor2D*, std::unordered_set<Actor2D*>> callbackList;
	int loopCount = 0;
	while (true)	//複数回ループさせることによってバグによるめり込みや高速物体での壁貫通を防ぐことができる
	{
		for (auto& pair : pairList)
		{
			Actor2D* actor1 = pair.actor1;
			Actor2D* actor2 = pair.actor2;
	
			Collision::HitInfo hitInfo =
				actor1->GetCollider()->CheckCollision(
					actor1->GetTransform(),
					actor2->GetTransform(),
					actor2->GetCollider()
				);
	
			// 当たっていない
			if (!hitInfo.isHit) continue;
	
			// コールバック登録
			callbackList[actor1].insert(actor2);


			//位置補正
			// 
			// 相手がトリガータグなら位置調整しない
			if (actor1->GetCollider()->GetPhysicsBehavior(actor2->GetTag()) == PhysicsBehavior::Trigger) continue;
			if (actor2->GetCollider()->GetPhysicsBehavior(actor1->GetTag()) == PhysicsBehavior::Trigger) continue;

			// あまりにも修正値が小さい場合は、ある程度の大きさまで拡張する(物体がガタガタ震えるバグの原因になりえるから)
			if (hitInfo.resolve.SqrMagnitude() < 0.1f)
			{
				hitInfo.resolve = hitInfo.resolve.Normalized() * 0.1f;
			}

	
	
			Rigidbody2D& body1 = actor1->m_rigidbody2d;
			Rigidbody2D& body2 = actor2->m_rigidbody2d;
	
			// 静的オブジェクトの場合、相手の重さを0にして相手だけ跳ね返させる	
			if (body1.GetBodyType() == Rigidbody2D::Type::Static) body2.mass = 0;
			if (body2.GetBodyType() == Rigidbody2D::Type::Static) body1.mass = 0;
	
			// 重さと反発率の合算
			const float TotalMass = body1.mass + body2.mass;	//合計重量(重さによって動きやすさが変わるから)
			const float RefRate = (1 + body1.bounciness * body2.bounciness); //反発率(完全非弾性衝突を防ぐために +1 をしている)
	
			// 反射ベクトルを算出
			const Vector2 Resolve = hitInfo.resolve.Normalized();	//どの方向に押し出すか
			const float Dot = Vector2::Dot(		 //物体が壁に向かう速度
				body1.velocity - body2.velocity, //相対速度(どのぐらいの速さで近づいているか)
				Resolve							 //衝突方向の速度
			);	
			const Vector2 Reflect = (RefRate * Dot / TotalMass) * Resolve;	//反発する力(壁に向かう速度が-10 → +10みたいに速度の変化量を求めている)
	
			// 多めに押し出す
			hitInfo.resolve = hitInfo.resolve / TotalMass * 1.01f;	//普通に押し出すと少し重なる可能性があるから
	

			// 位置と速度を設定
			actor1->m_transform.position += -body2.mass * hitInfo.resolve;
			actor1->m_rigidbody2d.velocity  = -body2.mass * Reflect + body1.velocity;
			actor2->m_transform.position +=  body1.mass * hitInfo.resolve;
			actor2->m_rigidbody2d.velocity  =  body1.mass * Reflect + body2.velocity;
	
		}

		loopCount++;
		if (loopCount >= 3) break;
	}

	// コールバック処理
	for (auto pair : callbackList)
	{
		auto actor1 = pair.first;	//リストの中の最初の要素を取得

		for (auto actor2 : pair.second)	//リストの中の2番目以降の要素を取得
		{
			// 前回の衝突判定で、同じ組み合わせがいたか
			auto it = m_prevCallbackList.find(actor1);	//前回 actor1 と衝突していたか？(要素(今回ならactor1)の場所を返す)

			if (it != m_prevCallbackList.end()	//前回 actor1 と衝突していた(end()はコンテナの「最後の次」= 存在しない)
				&& it->second.find(actor2) != it->second.end())	
			{
				// いたので「衝突中」
				actor1->OnCollision(actor2);
				actor2->OnCollision(actor1);

				// 前回の衝突リストから、組み合わせを削除
				it->second.erase(actor2);
			}
			else
			{
				// いなかったので「新規の衝突」
				actor1->OnCollisionEnter(actor2);
				actor2->OnCollisionEnter(actor1);
			}
		}
	}

	// この時点で前回の衝突リストに残っているのは「衝突終了」
	for (auto pair : m_prevCallbackList)
	{
		auto actor1 = pair.first;	//リストの中の最初の要素を取得

		// 生存チェック(クラッシュ防止)
		if (std::find(m_actorList.begin(), m_actorList.end(), actor1) == m_actorList.end()) continue;

		for (auto actor2 : pair.second)
		{
			// 生存チェック(クラッシュ防止)
			if (std::find(m_actorList.begin(), m_actorList.end(), actor2) == m_actorList.end()) continue;

			actor1->OnCollisionExit(actor2);
			actor2->OnCollisionExit(actor1);
		}
	}

	// 衝突リストを覚えておく
	m_prevCallbackList = callbackList;
}


#ifdef _DEBUG
void Physics2D::Draw() const
{
	for (auto actor : m_actorList)
	{
		auto col = actor->GetCollider();
		if (col) col->Draw(actor->GetTransform());
	}
}
#endif
