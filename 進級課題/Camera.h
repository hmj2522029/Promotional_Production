#pragma once
#include "MyLib.h"

class Camera
{

private:
    static constexpr float MoveSpeed = 3.5f;
    static constexpr Vector2 SpawnPos = Vector2(0, 0);

    //ステージ用
	Vector2 m_stageVelocity;     // カメラの移動速度
    Vector2 m_stagePos;          // カメラの位置(ステージとかの描画用)

	Vector2 m_playerVelocity;    // カメラの移動速度
	Vector2 m_playerPos;         // カメラの位置(プレイヤー用)
    

public:

    //シングルトン
    static Camera* GetInstance()
    {
        static Camera  instance;
        return &instance;
    }


    Camera();               // コンストラクタ

    void Update();
    void Initialization();

    //カメラを止める・動かす(ステージ)
	void StopStage() { m_stageVelocity = Vector2(0, 0); }
	void MoveStage() { m_stageVelocity = Vector2(MoveSpeed, 0); }

    //カメラが動いているかどうか
	bool IsMovingStage() const { return m_stageVelocity.x != 0; }

    Vector2 GetStagePos() const { return m_stagePos; }        // カメラ位置取得

	//カメラを止める・動かす(プレイヤー)
	void StopPlayer() { m_playerVelocity = Vector2(0, 0); }
	void MovePlayer() { m_playerVelocity = Vector2(MoveSpeed, 0); }

	//カメラが動いているかどうか
	bool IsMovingPlayer() const { return m_playerVelocity.x != 0; }

	Vector2 GetPlayerPos() const { return m_playerPos; } // プレイヤー位置取得


    float GetSpeed() const { return MoveSpeed; }

};