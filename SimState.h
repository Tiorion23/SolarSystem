#pragma once
#include "State.h"
#include "SolarSystem.h"
#include "Ui.h"

enum class ActionState { NONE, PANNING };

class SimState : public State
{
	sf::View sim_view;
	sf::View ui_view;

	std::map<std::string, Ui> ui_system;

	float default_scale;
	float scale;

	ActionState action_state;

	sf::Vector2i oldPos;
	sf::Vector2i pointerPos;

	SolarSystem* sol;
	unsigned long long int time;	// number of simulated seconds
	int step;
	int simulation_speed;			// simulation speed in hours per second

	SolarSystem* initialize_solar_system();

public:
	virtual void handle_input();
	virtual void update(const float dt);
	virtual void draw(const float dt);

	SimState(Engine* engine);
};

