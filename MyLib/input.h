#pragma once
#include "Keyboard.h"

class input
{
private:
	input() {};

public:
	static void Update()
	{
		Keyboard::Update();
	}

};