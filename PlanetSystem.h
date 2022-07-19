#pragma once
#include <vector>
#include "Vectorld2d.h"
#include "planet.h"
#include "Volume.h"
#include <iostream>
//#include "utility.h"  //including causes loop inclusion 
// class for planetary system that consists of 1+ planets, has its own coordinate system with (0, 0) in the baricenter (center of mass)
class PlanetSystem
{
	std::vector<Planet*> planets; // Planet objects that system consists of
	long double x; // x-coordinate of Planetary system's (0, 0) in solar system's coordinate system (NOT GLOBAL COORDINATE)
	long double y; // y-coordinate of Planetary system's (0, 0) in solar system's coordinate system (NOT GLOBAL COORDINATE)
	Volume bounding_volume; //bounding volume in solar systems coordinates, click on which is considered click on planetary system
	Vectorld2d sspeed; //speed of Planetary system (0, 0) in solar system's coordinate system
	Vectorld2d acceleration; //acceleration of Planetary system (0, 0) in solar system's coordinate system
public:
	//constructor
	//ps - Planets (1+) that PlanetSystem consists of; 
	//ax - x coordinate of of Planetary system's (0, 0) in solar system's coordinate system;
	//ay - y coordinate of of Planetary system's (0, 0) in solar system's coordinate system; 
	//sp - speed of Planetary system in solar system's coordinate system
	PlanetSystem(std::vector<Planet*> ps, long double ax, long double ay, Vectorld2d sp);

	//operator == overload for PlanetSystem  class
	friend bool operator== (const PlanetSystem& ps1, const PlanetSystem& ps2);
	//operator != overload for PlanetSystem class
	friend bool operator!= (const PlanetSystem& ps1, const PlanetSystem& ps2);

	//calculates distance between two planetary systems
	friend const long double distance(const PlanetSystem& ps1, const PlanetSystem& ps2);

	//calculates summary vector of gravitational force on planet system from planet systems
	friend Vectorld2d grav_force(const PlanetSystem& ps, std::vector<PlanetSystem*> psystems);

	//calculates summary vector of acceleration from gravitational force on planet system from planet systems and sets planet's acceleration to it
	friend void grav_pull(PlanetSystem& ps, std::vector<PlanetSystem*> psystems);

	//returns list of planetary systems without system ps
	friend std::vector<PlanetSystem*> interaction_list(const PlanetSystem& ps, std::vector<PlanetSystem*> psystems);

	//returns list of planets 
	
	//getter for planets that planetary system consists of
	std::vector<Planet*> get_planets() const;
	//
	std::string get_name() const;
	//getter for mass of the system as sum of masses of panets
	long double get_mass() const;
	//getter for x-coordinate
	long double get_x() const;
	//setter for x-coordinate
	void set_x(long double ax);
	//getter for y-coordinate 
	long double get_y() const;
	//setter for y-coordinate
	void set_y(long double ay);
	// getter for speed
	Vectorld2d get_speed() const;
	// setter for speed
	void set_speed(Vectorld2d sp);
	//updates speed with current acceleration with given step
	void update_speed(int astep);
	//getter for acceleration
	Vectorld2d get_acceleration();

	//setter for acceleration
	void set_acceleration(Vectorld2d acc);
	//adds planet to planetary system, changes coordinates of planet according to planetary system's coordinates
	void add_planet(Planet* p);
	//moves system to specified coordinates
	void move(int astep);

	//finds baricenter coordinates of planetary system in its coordinate system
	std::vector<long double> baricenter();

	// simulates moving of elemets of planetary system
	void simulate(int step);

	//checks if planetary system is clicked
	bool is_clicked(sf::Vector2f pointer);

	//resizes shapes of all planets in planetary system
	void resize_shapes(float s);

	//draws all elemets of the system
	void draw_system(sf::RenderWindow &w);
	//for drawing planet in planetary system, ax and ay are the coordinates of planetary system in solar system
	void draw_system(sf::RenderWindow& w, long double ax, long double ay);
};

