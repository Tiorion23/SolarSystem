#ifndef SOLAR_SYSTEM
#define SOLAR_SYSTEM
#include <vector>
#include <iomanip>
#include "Vectorld2d.h"
#include "PlanetSystem.h"

class MaterialPoint;
class CosmicBody;
class PlanetSystem;

class SolarSystem: public MaterialPoint
{
	static int id;
	const std::string name;
	std::vector<PlanetSystem*> systems; //list of planetary systems that solar system consists of
public:
	SolarSystem(std::vector<PlanetSystem*> systems, Vectorld2d coords, Vectorld2d sp, std::string aname = "");
	
	//////////////////////////////////////////////////////////////////
	///////////////// INTERFACE: GETTERS AND SETTERS /////////////////
	//////////////////////////////////////////////////////////////////
	//provided getters and setters for whole coordinate in vector as well as individual X and Y coordinates

	std::string get_name();
	
	//getter for planetary systems
	std::vector<PlanetSystem*> get_systems() const;
	//getter for mass of the system as sum of masses of planet systems
	long double get_mass() const;

	//////////////////////////////////////////////////////////////////
	///////////////////// PHYSICAL INTERACTIONS //////////////////////
	//////////////////////////////////////////////////////////////////

	// simulates moving of elemets of planetary system
	void simulate(float step);

	// cosmic body leaves planetary system
	void planet_leaves(CosmicBody* body);

	//////////////////////////////////////////////////////////////////
	//////////////////////// UTILITY FUNCTIONS ///////////////////////
	//////////////////////////////////////////////////////////////////
	// includes friend function that returns vector of planetary systems without given planetary system
	// draw functions

	//returns list of planetary systems without system ps
	friend std::vector<SolarSystem*> interaction_list(const SolarSystem& ss, std::vector<SolarSystem*> ssystems);

	//finds baricenter coordinates of planetary system in its coordinate system
	Vectorld2d baricenter();	

	//resizes shapes of all planets in solar system
	void resize_shapes(float s);

	//draws all elemets of the system
	void draw(sf::RenderWindow& w);

	//////////////////////////////////////////////////////////////////
	///////////////// COMPARISON OPERATORS OVERLOAD //////////////////
	//////////////////////////////////////////////////////////////////

	////operator == overload for PlanetSystem  class
	//friend bool operator== (const SolarSystem& ss1, const SolarSystem& ss2);
	////operator != overload for PlanetSystem class
	//friend bool operator!= (const SolarSystem& ss1, const SolarSystem& ss2);	
};

#endif

