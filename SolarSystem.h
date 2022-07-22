#pragma once
#include <vector>
#include "Vectorld2d.h"
#include "PlanetSystem.h"

class SolarSystem
{
	std::vector<PlanetSystem*> systems; //list of planetary systems that solar system consists of
	Vectorld2d global_coords;
	long double global_x; //x-coordinate of solar system's baricenter (0,0) in global (galaxy) coordinate system
	long double global_y; //y-coordinate of solar system's baricenter (0,0) in global (galaxy) coordinate system
	Volume bounding_volume; //bounding volume in global coordinates, click on which is considered click on solar system
	Vectorld2d speed; //speed of solar system's (0,0)
	Vectorld2d acceleration; //acceleration of solar system
public:
	SolarSystem(std::vector<PlanetSystem*> systs, long double ax, long double ay, Vectorld2d sp);
	
	//////////////////////////////////////////////////////////////////
	///////////////// INTERFACE: GETTERS AND SETTERS /////////////////
	//////////////////////////////////////////////////////////////////
	//provided getters and setters for whole coordinate in vector as well as individual X and Y coordinates
	
	//getter for planetary systems
	std::vector<PlanetSystem*> get_systems() const;
	//getter for mass of the system as sum of masses of planet systems
	long double get_mass() const;
	//getter for x-coordinate
	long double get_global_x() const;
	//setter for x-coordinate
	void set_global_x(long double ax);
	//getter for y-coordinate 
	long double get_global_y() const;
	//setter for y-coordinate
	void set_global_y(long double ay);
	//getter for coords
	Vectorld2d get_global_coords();
	//setter for coords
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
	// including friend functions for calculating gravitational force and pull from given vector of solar systems, distance between 
	// two solar systems

	//calculates distance between two planetary systems
	friend const long double distance(const SolarSystem& ps1, const SolarSystem& ps2);

	//calculates summary vector of gravitational force on planet system from planet systems
	friend Vectorld2d grav_force(const SolarSystem& ps, std::vector<SolarSystem*> psystems);

	//calculates summary vector of acceleration from gravitational force on planet system from planet systems and sets planet's acceleration to it
	friend void grav_pull(SolarSystem& ps, std::vector<SolarSystem*> psystems);

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
	friend std::vector<SolarSystem*> interaction_list(const SolarSystem& ss, std::vector<SolarSystem*> ssystems);

	//finds baricenter coordinates of planetary system in its coordinate system
	Vectorld2d baricenter();	

	// updates position of bounding volume based on current global coordinates
	void update_bounding_volume();

	//checks if solar system is clicked
	bool is_clicked(sf::Vector2f pointer);

	//resizes shapes of all planets in solar system
	void resize_shapes(float s);

	//draws all elemets of the system
	void draw_system(sf::RenderWindow& w);

	//////////////////////////////////////////////////////////////////
	///////////////// COMPARISON OPERATORS OVERLOAD //////////////////
	//////////////////////////////////////////////////////////////////

	//operator == overload for PlanetSystem  class
	friend bool operator== (const SolarSystem& ss1, const SolarSystem& ss2);
	//operator != overload for PlanetSystem class
	friend bool operator!= (const SolarSystem& ss1, const SolarSystem& ss2);

	
};

