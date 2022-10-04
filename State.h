#pragma once
#include "Engine.h"

class Engine;
class State
{

public:
	Engine* engine;
	
	virtual void handle_input() = 0;
	virtual void update(const float dt) = 0;
	virtual void draw(const float dt) = 0;
};

