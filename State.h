#ifndef STATE
#define STATE
#include "Engine.h"

class Engine;
// abstract state class
class State
{

public:
	Engine* engine;
	
	virtual void handle_input() = 0;
	virtual void update(const float dt) = 0;
	virtual void draw(const float dt) = 0;
};

#endif