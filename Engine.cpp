#include "Engine.h"

Engine::Engine() {
	window.create(sf::VideoMode(1280, 720), "Solar System");
	window.setFramerateLimit(60);
	graphics_handler = GraphicsHandler();
	load_fonts();
	load_styles();
}

Engine::~Engine() {
	while (!this->states.empty()) pop_state();
}

void Engine::load_fonts() {
	sf::Font font;
	font.loadFromFile("fonts/arial.ttf");
	this->fonts["main_font"] = font;
}

void Engine::load_styles() {
	this->styles["button"] = UiStyle(&this->fonts.at("main_font"), 1,
		sf::Color(0xc6, 0xc6, 0xc6), sf::Color(0x94, 0x94, 0x94), sf::Color(0x00, 0x00, 0x00),
		sf::Color(0x61, 0x61, 0x61), sf::Color(0x94, 0x94, 0x94), sf::Color(0x00, 0x00, 0x00));
	this->styles["text"] = UiStyle(&this->fonts.at("main_font"), 0,
		sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00), sf::Color(0xff, 0xff, 0xff),
		sf::Color(0x00, 0x00, 0x00, 0x00), sf::Color(0x00, 0x00, 0x00), sf::Color(0xff, 0x00, 0x00));
	this->styles["panel"] = UiStyle(&this->fonts.at("main_font"),1,
		sf::Color(0xc6, 0xc6, 0xc6, 128), sf::Color(0x94, 0x94, 0x94, 128), sf::Color(0x00, 0x00, 0x00),
		sf::Color(0x61, 0x61, 0x61), sf::Color(0x94, 0x94, 0x94), sf::Color(0x00, 0x00, 0x00));
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
		this->window.clear();
		peek_state()->draw(dt);
		this->window.display();
	}
}