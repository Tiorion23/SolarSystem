#include "Engine.h"
Engine::Engine() {
	window.create(sf::VideoMode(1280, 720), "Solar System");

}

Engine::~Engine() {
	while (!this->states.empty()) pop_state();
}

void Engine::push_state(State* state) {
	this->states.push(state);
}

void Engine::pop_state() {
	delete this->states.top();  // deletes state from memory pile
	this->states.pop();			// removes pointer to that state from states stack
}

void Engine::change_state(State* state) {
	if (!this->states.empty())	// if state stack is not empty
		pop_state();			// removes top state from it
	push_state(state);			// pushes new one on top
}

State* Engine::peek_state() {
	if (this->states.empty()) 
		return nullptr;
	return this->states.top();
}

void Engine::run() {
	sf::Clock clock;
	while (this->window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (peek_state() == nullptr) continue;
		peek_state()->handle_input();
		peek_state()->update(dt);
		this->window.clear(sf::Color::Black);
		peek_state()->draw(dt);
		this->window.display();
	}
}