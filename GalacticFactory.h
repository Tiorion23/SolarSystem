#ifndef GAL_FACTORY
#define GAL_FACTORY
#include "Galaxy.h"
#include "Engine.h"

class Engine;

//singleton class that produces cosmic bodies and their aglomerations
class GalacticFactory {
	GalacticFactory(Engine* engine);
	static GalacticFactory* instance;
	Engine* engine;
public:
	// returns pointer to class instance
	static GalacticFactory* get_instance(Engine* engine);

	// creates cosmic body of type with specified name, diameter, mass, at specified coordinates and speed (in planetary system's coorinates) 
	CosmicBody* create_cosmic_body(CosmicBodyType type, std::string name, long double diam, long double m, Vectorld2d coords, Vectorld2d sp);

	// creates planetary system that consists of cosmic bodies from ps with specified coordinates and speed (in solar system's coordinate system)
	PlanetSystem* create_planet_system(std::vector<CosmicBody*> ps, Vectorld2d coords, Vectorld2d sp);

	// creates shapes for solar system planets  in engines shapes manager
	void create_solar_system_shapes();

	// creates solar system that consists of planetary systems from systs with specified coordinates and speed
	SolarSystem* create_solar_system(std::vector<PlanetSystem*> systs, Vectorld2d coords, Vectorld2d sp);

	// creates galaxy from specified list of solar systems
	Galaxy* create_galaxy(std::vector <SolarSystem*> systems);

	// creates predefined Solar System
	SolarSystem* initialize_solar_system();
};


#endif