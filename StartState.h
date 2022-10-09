#ifndef START_STATE
#define START_STATE
#include "State.h"
#include "SimState.h"
#include "Ui.h"
// class for start screen/main menu
class StartState : public State
{
	sf::View view;		// start screen/main menu view
	std::map<std::string, Ui> ui_system;	// UI of start screen/main menu
	void start_simulation();				// going to simulation, puts simulation state on to the state stack
public:
	virtual void handle_input();
	virtual void update(const float dt);
	virtual void draw(const float dt);

	StartState(Engine* engine);
};

#endif