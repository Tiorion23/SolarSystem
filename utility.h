#pragma once
#include "planet.h"
#include "PlanetSystem.h"
#include <math.h>
#include <string>
#include <sstream> // для stringstream
#define G 6.67e-11
#define PI atan(1) * 4

class utility
{
public:
	//calculate module of arg
	static long double mod(long double arg);

	//calculates length of vector
	static long double vector_length(std::vector<long double> v);

	//modify vector by number times
	static std::vector<long double> mod_vector(std::vector<long double> v, float n);

	//calculates vector sum of two vectors
	static std::vector<long double> vector_sum(std::vector<long double> v1, std::vector<long double> v2);

	//rotates vector by angle in radians
	static std::vector<long double> rotate_vector(std::vector<long double> v, long double angle);

	//summary of gravitational FORCE of planet p from planets, format {module, x axis component, y axis component}
	//static std::vector<long double> grav_force(const Planet& p, std::vector<Planet*> planets);

	//summary of gravitational FORCE of planet p from planets, format {module, x axis component, y axis component}
	//overload for planetary systems
	//static std::vector<long double> grav_force(const PlanetSystem& ps, std::vector<PlanetSystem*> psystems);

	//summary of gravitational accelerations of planet p from planets, format {x-axis component, y-axis component}
	//static std::vector<long double> grav_pull(Planet* p, std::vector<Planet*> planets);

	//summary of gravitational accelerations of planetary system ps from planetary systems, format {x-axis component, y-axis component}
	//overload for planetary systems
	//static std::vector<long double> grav_pull(PlanetSystem* ps, std::vector<PlanetSystem*> psystems);

	//creates vector with obects planet p interacts with
	//static std::vector<Planet*> interaction_list(Planet* p, std::vector<Planet*> planets);

	//creates vector with objects planetary system ps interacts with
	//overload for planetary systems
	//static std::vector<PlanetSystem*> interaction_list(PlanetSystem* ps, std::vector<PlanetSystem*> psystems);

	//timer string maker
	static std::string timer(unsigned long long int time);

	//info string, displays module of summary of gravity forces, its x- and y-components, speed of each planet in planet system
	static std::string info(const std::vector<Planet*> &planets);
	//info string, displays module of summary of gravity forces, its x- and y-components, speed of each planet in planet system
	static std::string info(const PlanetSystem& ps);

	//info string, displays module of summary of gravity forces, its x- and y-components, speed of each planet in planet systems
	// overload for planet system
	static std::string info(const std::vector<PlanetSystem*>& psystems);
};

