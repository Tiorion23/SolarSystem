#include "Galaxy.h"

Galaxy::Galaxy(std::vector<SolarSystem*> solar_systems) {
	this->solar_systems = solar_systems;
}

std::vector<SolarSystem*> Galaxy::get_solar_systems() const {
	return solar_systems;
}

void Galaxy::add_solar_System(SolarSystem* system) {
	this->solar_systems.push_back(system);
}

void Galaxy::draw(sf::RenderWindow& w) {
	for (const auto& a : solar_systems) {
		a->draw(w);
	}
}