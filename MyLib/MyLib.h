#pragma once

#ifdef _DEBUG
#pragma comment(lib, "MyLib_d.lib")
#else
#pragma comment(lib, "MyLib.lib")
#endif // _DEBUG

//Root
#include "Screen.h"
#include "Tag.h"

// Component
#include "Actor2D.h"
#include "Node.h"
#include "Rigidbody2D.h"
#include "Transform.h"


//Component/Collider
#include "BoxCollider.h"
#include "Collider.h"

//Input
#include "Keyboard.h"
#include "Input.h"

//Loader


//Math
#include "Vector2.h"

//Physics
#include "Collision.h"
#include "Physics2D.h"
#include "PhysicsBehavior.h"

//Scene

//Utility
#include "Debug.h"
#include "Time.h"


