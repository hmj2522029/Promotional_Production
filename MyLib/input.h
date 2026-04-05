#pragma once
#include "Keyboard.h"
#include "Mouse.h"

class input
{
private:
	input() {};

public:
	static void Update()
	{
		Mouse::Update();
		Keyboard::Update();
	}

};