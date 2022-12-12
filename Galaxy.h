#ifndef GALAXY
#define GALAXY
#include "SolarSystem.h"

class Galaxy {
	std::vector<SolarSystem*> solar_systems;
public:
	Galaxy(std::vector<SolarSystem*> solar_systems);
	std::vector<SolarSystem*> get_solar_systems() const;
	void add_solar_System(SolarSystem* system);
	void draw(sf::RenderWindow& w);
};

#endif