#pragma once
#include "Status.h"
#include "MyLib.h"

class Character : public Actor2D
{
protected:

	bool m_isAction;	//各キャラクターが行動したかどうか

	//テキストファイルからデータを読み込む関数(共通(単体))
	std::unordered_map<std::string, std::string> LoadKeyValueFile(const std::string& path);

public:
	Status m_status;	//ステータス

	Character(	//アニメーション
		const Animation2D& anime,
		const Vector2& gridSize,
		const Vector2& pos = Vector2(),
		const int drawOrder = 0,
		Tag tag = Tag::None,
		Rigidbody2D::Type type = Rigidbody2D::Type::Static
	) :
		Actor2D(anime, gridSize, pos, drawOrder, tag, type),
		m_status(),
		m_isAction(false)
	{
	}
	Character(	//画像
		const SpriteRegion& image,
		const Vector2& gtidSize = Vector2(),
		const Vector2& pos = Vector2(),
		const int drawOrder = 0,
		Tag tag = Tag::None,
		Rigidbody2D::Type type = Rigidbody2D::Type::Static
	) :
		Actor2D(image, gtidSize, pos, drawOrder, tag, type),
		m_status(),
		m_isAction(false)
	{
	}
	Character(
		const char* textureName,
		const Vector2& pos = Vector2(),
		const int drawOrder = 0,
		Tag tag = Tag::None,
		Rigidbody2D::Type type = Rigidbody2D::Type::Static
	) :
		Actor2D(textureName, pos, drawOrder, tag, type),
		m_status(),
		m_isAction(false)
	{
	}
	Character(	//アニメーションなし
		const int drawOrder = 0,
		Tag tag = Tag::None,
		Rigidbody2D::Type type = Rigidbody2D::Type::Static
	) :
		Character(nullptr, Vector2(), drawOrder, tag, type)
	{
	}

	//行動したかどうか
	bool isAction() const { return m_isAction; }

	//行動した
	void Action() { m_isAction = true; }

	//行動をリセット
	void ResetAction() { m_isAction = false; }


};