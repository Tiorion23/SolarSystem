#ifndef SIM_STATE
#define SIM_STATE
#include "State.h"
#include "PauseMenuState.h"
#include "SolarSystem.h"
#include "Ui.h"
#include "DynamicUi.h"

enum class ActionState { NONE, PANNING, FOCUSED };
enum class SimulationState {RUNNING, PAUSED};

class SimState : public State
{
	sf::View sim_view;	// view used to draw simulated objects
	sf::View ui_view;	// view used to draw UI

	std::map<std::string, Ui> static_ui_system;		// static (not-moving) UI elements
	std::map<std::string, DynamicUi> dynamic_ui_system;		// dynamic (moving) UI elements

	float default_scale;
	float scale;

	ActionState action_state;
	SimulationState simulation_state;

	sf::Vector2i oldPos;
	sf::Vector2i pointerPos;

	SolarSystem* sol;
	CosmicBody* focus;				// object currently in focus
	unsigned long long int time;	// number of simulated seconds
	int step;						// simulation time-step
	// contains simulation speed in hours per second for simulation (can be changed) and paused state (always 0)
	std::map<SimulationState, int> simulation_speed;

	~SimState();

	// functions called once in constructor
	// creates all objects in solar system
	SolarSystem* initialize_solar_system();
	// creates all static and dynamic UI elements and puts them into corresponding maps
	void initialize_ui();
	// pause menu, puts new pause menu on stack
	void go_to_pause();

public:
	virtual void handle_input();
	// calls update_simulation() and update_ui()
	virtual void update(const float dt);
	// updates simulation depending on previous frame time and simulation speed
	void update_simulation(const float dt);
	// updates UI
	void update_ui();
	// draws objects in simulation
	virtual void draw(const float dt);

	SimState(Engine* engine);
};

#endif