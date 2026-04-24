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
#include "Sprite.h"
#include "Transform.h"
#include "Button.h"
#include "Animation2D.h"
#include "SpriteRegion.h"


//Collider
#include "BoxCollider.h"
#include "Collider.h"

//Input
#include "Mouse.h"
#include "Keyboard.h"
#include "Input.h"

//Loader
#include "ImageLoader.h"
#include "SoundLoader.h"
#include "LoaderBase.h"

//Math
#include "Easing.h"
#include "Vector2.h"
#include "Math.hpp"

//Physics
#include "Collision.h"
#include "Physics2D.h"
#include "PhysicsBehavior.h"

//Scene
#include "SceneBase.h"
#include "SceneManager.h"

//Utility
#include "Debug.h"
#include "ScreenFade.h"
#include "Time.hpp"

#include "NumberDrawer.h"
#include "DrawLayer.h"


