#include "Actor2D.h"
#include "Collider.h"
#include "Physics2D.h"


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


