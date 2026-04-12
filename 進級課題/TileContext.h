#pragma once
#include "MyLib.h"

//タイルの情報
struct TileContext
{
	char tile;			//タイルの種類を表す文字
	int screenStage;	//
	Vector2 pos;
	int tileSize;
};
