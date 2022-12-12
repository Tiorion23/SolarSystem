#ifndef PLANET_SYSTEM
#define PLANET_SYSTEM
#include <vector>
#include "Vectorld2d.h"
#include "CosmicBody.h"
#include "SolarSystem.h"
#include "Volume.h"
#include <iostream>
class MaterialPoint;
class CosmicBody;
class SolarSystem;
// class for planetary system that consists of 1+ planets, has its own coordinate system with (0, 0) in the baricenter (center of mass)
// for purpose of cross system interaction inherits from MaterialPoint all necessary parameters and interactions
class PlanetSystem: public MaterialPoint
{
	std::string name;
	std::vector<CosmicBody*> planets; // Cosmic bodies that system consists of
	Vectorld2d global_coords;	// global coordinates of planetary system's baricenter (0,0) 
public:
	SolarSystem* system;
	//constructor
	//ps - Planets (1+) that PlanetSystem consists of; 
	//ax - x coordinate of of Planetary system's (0, 0) in solar system's coordinate system;
	//ay - y coordinate of of Planetary system's (0, 0) in solar system's coordinate system; 
	//sp - speed of Planetary system in solar system's coordinate system
	PlanetSystem(std::vector<CosmicBody*> ps, Vectorld2d coords, Vectorld2d sp);

	//////////////////////////////////////////////////////////////////
	///////////////// INTERFACE: GETTERS AND SETTERS /////////////////
	//////////////////////////////////////////////////////////////////
	
	std::string get_name();
	//getter for cosmic bodies that planetary system consists of
	std::vector<CosmicBody*> get_planets() const;
	// returns solar system, in which this planet system is situated
	SolarSystem* get_system() const;
	// sets solar system, in which this planet system is situated
	void set_system(SolarSystem* system);
	// returns names of all cosmic bodies in planetary system
	std::string get_name() const;
	// returns global coordinates of planetary system's baricenter
	Vectorld2d get_global_coords() const;
	// sets global coordinates of planetary system's baricenter
	void set_global_coords(Vectorld2d c);

	//////////////////////////////////////////////////////////////////
	///////////////////// PHYSICAL INTERACTIONS //////////////////////
	//////////////////////////////////////////////////////////////////

	// simulates moving of elemets of planetary system
	void simulate(float step);

	//////////////////////////////////////////////////////////////////
	//////////////////////// UTILITY FUNCTIONS ///////////////////////
	//////////////////////////////////////////////////////////////////
	// includes friend function that returns vector of planetary systems without given planetary system
	// draw functions
	 
	//returns list of planetary systems without system ps
	friend std::vector<PlanetSystem*> interaction_list(const PlanetSystem& ps, std::vector<PlanetSystem*> psystems);

	//finds baricenter coordinates of planetary system in its coordinate system
	Vectorld2d baricenter();

	//resizes shapes of all planets in planetary system
	void resize_shapes(float s);

	//draws all elemets of the system
	void draw(sf::RenderWindow& w);

	//////////////////////////////////////////////////////////////////
	///////////////// COMPARISON OPERATORS OVERLOAD //////////////////
	//////////////////////////////////////////////////////////////////
	
	//operator == overload for PlanetSystem  class
	friend bool operator== (const PlanetSystem& ps1, const PlanetSystem& ps2);
	//operator != overload for PlanetSystem class
	friend bool operator!= (const PlanetSystem& ps1, const PlanetSystem& ps2);
};

#endif