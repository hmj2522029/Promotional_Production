#include "Actor2D.h"
#include "Collider.h"
#include "Physics2D.h"


Actor2D::Actor2D(
	const Animation2D& anime,
	const Vector2& gridSize,
	const Vector2& pos,
	Tag tag,
	Rigidbody2D::Type type
) :
	m_tag(tag),
	m_rigidbody2d(type),
	m_sprite(nullptr),
	m_collider(nullptr)
{
	m_transform.position = pos;

	//Sprite‚Ì‹N“®
	m_sprite = new Sprite();

	//“o˜^
	m_sprite->Register(anime);
	m_sprite->gridSize = gridSize;
}
Actor2D::Actor2D(
	const char* textureName,
	const Vector2& pos,
	Tag tag,
	Rigidbody2D::Type type
) :
	m_tag(tag),
	m_rigidbody2d(type),
	m_sprite(nullptr),
	m_collider(nullptr)
{
	m_transform.position = pos;

	//‰æ‘œ‚Ìw’è‚³‚ê‚Ä‚¢‚½‚ç
	if (textureName)
	{
		//Sprite‚Ì‹N“®
		m_sprite = new Sprite();

		//“o˜^
		m_sprite->Register(textureName);
	}

}

void Actor2D::Load()
{
	if (m_collider)
	{
		Physics2D::GetInstance()->Register(this);
	}


}

void Actor2D::Release()
{



	if (m_collider)
	{
		Physics2D::GetInstance()->Remove(this);
		delete m_collider;
		m_collider = nullptr;
	}

}

void Actor2D::Draw()
{


}

void Actor2D::TreeUpdate()
{
	// Node–{—ˆ‚ÌTreeUpdate‚ğÀs
	Node::TreeUpdate();


}


