#ifndef PAUSE_MENU
#define PAUSE_MENU
#include "State.h"

class PauseMenuState: public State
{
	sf::View view;		// pause menu screen view
	std::map<std::string, Ui> ui_system;	// UI of pause menu screen
public:
	virtual void handle_input();
	virtual void update(const float dt);
	virtual void draw(const float dt);

	PauseMenuState(Engine* engine);
};

#endif