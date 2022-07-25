#pragma once
#include "Engine.h"

class State
{
public:
	Engine* engine;
	
	virtual void handle_input(const float dt) = 0;
	virtual void update(const float dt) = 0;
	virtual void draw() = 0;
};

