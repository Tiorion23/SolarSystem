#ifndef PLANET_SYSTEM
#define PLANET_SYSTEM
#include <vector>
#include "Vectorld2d.h"
#include "CosmicBody.h"
#include "Volume.h"
#include <iostream>
// class for planetary system that consists of 1+ planets, has its own coordinate system with (0, 0) in the baricenter (center of mass)
class PlanetSystem
{
	std::vector<CosmicBody*> planets; // Cosmic bodies that system consists of
	//long double x; // x-coordinate of Planetary system's baricenter (0, 0) in solar system's coordinate system
	//long double y; // y-coordinate of Planetary system's baricenter (0, 0) in solar system's coordinate system
	Vectorld2d coords;			// coordinates of planetary system's baricenter (0,0) in solar system's coordinate system
	//long double global_x; // global x-coordinate of Planetary system's (0,0)
	//long double global_y; // global y-coordinate of Planetary system's (0,0)
	Vectorld2d global_coords;	// global coordinates of planetary system's baricenter (0,0) 
	Volume bounding_volume; //bounding volume in global coordinates, click on which is considered click on planetary system
	Vectorld2d sspeed; //speed of Planetary system (0, 0) in solar system's coordinate system
	Vectorld2d acceleration; //acceleration of Planetary system (0, 0) in solar system's coordinate system
public:
	//constructor
	//ps - Planets (1+) that PlanetSystem consists of; 
	//ax - x coordinate of of Planetary system's (0, 0) in solar system's coordinate system;
	//ay - y coordinate of of Planetary system's (0, 0) in solar system's coordinate system; 
	//sp - speed of Planetary system in solar system's coordinate system
	PlanetSystem(std::vector<CosmicBody*> ps, long double ax, long double ay, Vectorld2d sp);

	//////////////////////////////////////////////////////////////////
	///////////////// INTERFACE: GETTERS AND SETTERS /////////////////
	//////////////////////////////////////////////////////////////////
	//provided getters and setters for whole coordinate in vector as well as individual X and Y coordinates
	
	//getter for cosmic bodies that planetary system consists of
	std::vector<CosmicBody*> get_planets() const;
	// returns names of all cosmic bodies in planetary system
	std::string get_name() const;
	//getter for mass of the system as sum of masses of its cosmic bodies
	long double get_mass() const;
	//getter for x-coordinate
	long double get_x() const;
	//setter for x-coordinate
	void set_x(long double ax);
	//getter for y-coordinate 
	long double get_y() const;
	//setter for y-coordinate
	void set_y(long double ay);
	//getter for global x
	long double get_global_x();
	// setter for global x
	void set_global_x(long double arg);
	// getter for global y
	long double get_global_y();
	// setter for global y
	void set_global_y(long double arg);
	//getter for coords
	Vectorld2d get_coords();
	//setter for coords
	void set_coords(Vectorld2d c);
	//getter for global coords
	Vectorld2d get_global_coords();
	//setter for global coords
	void set_global_coords(Vectorld2d c);
	// getter for speed
	Vectorld2d get_speed() const;
	// setter for speed
	void set_speed(Vectorld2d sp);
	//getter for acceleration
	Vectorld2d get_acceleration();
	//setter for acceleration
	void set_acceleration(Vectorld2d acc);

	//////////////////////////////////////////////////////////////////
	///////////////////// PHYSICAL INTERACTIONS //////////////////////
	//////////////////////////////////////////////////////////////////
	// including friend functions for calculating gravitational force and pull from given vector of planetary systems, distance between 
	// two planetary systems

	//calculates distance between two planetary systems
	friend const long double distance(const PlanetSystem& ps1, const PlanetSystem& ps2);

	//calculates summary vector of gravitational force on planet system from planet systems
	friend Vectorld2d grav_force(const PlanetSystem& ps, std::vector<PlanetSystem*> psystems);

	//calculates summary vector of acceleration from gravitational force on planet system from planet systems and sets planet's acceleration to it
	friend void grav_pull(PlanetSystem& ps, std::vector<PlanetSystem*> psystems);

	//updates speed with current acceleration with given step
	void update_speed(int astep);

	//moves system according to current speed and given time-step
	void move(int astep);

	// simulates moving of elemets of planetary system
	void simulate(int step);

	//////////////////////////////////////////////////////////////////
	//////////////////////// UTILITY FUNCTIONS ///////////////////////
	//////////////////////////////////////////////////////////////////
	// includes friend function that returns vector of planetary systems without given planetary system
	// draw functions
	 
	//returns list of planetary systems without system ps
	friend std::vector<PlanetSystem*> interaction_list(const PlanetSystem& ps, std::vector<PlanetSystem*> psystems);

	//finds baricenter coordinates of planetary system in its coordinate system
	Vectorld2d baricenter();

	// updates position of bounding volume based on current global coordinates
	void update_bounding_volume();

	//checks if planetary system is clicked
	bool is_clicked(sf::Vector2f pointer);

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