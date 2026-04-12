#pragma once
#include "TileContext.h"
#include <unordered_map>
#include "MyLib.h"

class Camera;

class ObjectFactory
{

private:

	using TileCreateFunc = Actor2D* (ObjectFactory::*)(const TileContext&, Camera*);	//タイルを生成する関数の型(引数 Vector2 戻り値 Actor2D)
	std::unordered_map<char, TileCreateFunc> m_tileTable;	//マップ記号とタイル生成関数の対応表(キー = タイル文字 値 = 生成する関数)

	Actor2D* CreateGround(const TileContext& tile, Camera* camera);		//地面を生成する関数
	Actor2D* CreateAirGround(const TileContext& tile, Camera* camera); 	//空中ブロックを生成する関数
	Actor2D* CreateEnemy(const TileContext& tile, Camera* camera);		//敵を生成する関数
	Actor2D* CreateSpike(const TileContext& tile, Camera* camera);		//トゲを生成する関数
	Actor2D* CreateHole(const TileContext& tile, Camera* camera);		//落とし穴を生成する関数

	//テーブルの初期化
	void InitializeTileTable();	//マップ記号とタイル生成関数の対応表を初期化する関数

	ObjectFactory() : 
		m_tileTable()
	{
		InitializeTileTable();	//コンストラクタでタイルテーブルを初期化する
	}
public:
	static ObjectFactory* GetInstance()	//シングルトンのインスタンスを取得する関数
	{
		static ObjectFactory instance;	//シングルトンのインスタンス(最初の呼び出し時に初期化される)
		return &instance;
	}


	//生成関数
	Actor2D* CreateObject(const TileContext& tileContext, Camera* camera);	//マップ記号に対応するタイル生成関数を呼び出す関数


};