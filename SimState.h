#ifndef SIM_STATE
#define SIM_STATE
#include "State.h"
#include "PauseMenuState.h"
#include "SolarSystem.h"
#include "Ui.h"
#include "DynamicUi.h"
#include "Camera.h"
#include "GalacticFactory.h"
#include "Simulation.h"

enum class ActionState { NONE, PANNING, FOCUSED, FOCUSEDPANNING };
enum class FocusType {NONE, SOLARSYSTEM, PLANETSYSTEM, BODY};

class SimState : public State
{
	Camera* camera;

	std::map<std::string, Ui> static_ui_system;		// static (not-moving) UI elements
	std::map<MaterialPoint*, DynamicUi> dynamic_ui_system;		// dynamic (moving) UI elements attached to cosmic bodies, planet systems and solar systems

	ActionState action_state;
	FocusType focus_type;

	sf::Vector2i oldPos;
	sf::Vector2i pointerPos;

	GalacticFactory* galactic_factory;

	Simulation* simulation;
	CosmicBody* focus_body;				// object currently in focus REWORK FOCUS SYSTEM TO BE ABLE TO FOCUS ON SOLAR SYSTEMS, PLANET SYSTEMS, PLANETS, UI AS WELL!
	PlanetSystem* focus_ps;
	SolarSystem* focus_solar_system;

	~SimState();

	// creates all static and dynamic UI elements and puts them into corresponding maps, called once when state is constructed
	void initialize_ui();
	
	// pause menu, puts new pause menu on the state stack
	void go_to_pause();

	void set_focus(SolarSystem* target);
	void set_focus(PlanetSystem* target);
	void set_focus(CosmicBody* target);

	void remove_cosmic_body_focus();
	void remove_planet_system_focus(PlanetSystem* target);
	void remove_solar_system_focus(CosmicBody* target);

	void stop_focus(ActionState new_state);

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