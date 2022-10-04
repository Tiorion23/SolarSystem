#pragma once
#include "State.h"
#include "SimState.h"
#include "Ui.h"

class StartState : public State
{
	sf::View view;
	void start_simulation();
	std::map<std::string, Ui> ui_system;
public:
	virtual void handle_input();
	virtual void update(const float dt);
	virtual void draw(const float dt);

	StartState(Engine* engine);
};

