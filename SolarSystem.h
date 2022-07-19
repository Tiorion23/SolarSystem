#pragma once
#include <vector>
#include "Vectorld2d.h"
#include "PlanetSystem.h"

class SolarSystem
{
	std::vector<PlanetSystem*> systems; //list of planetary systems that solar system consists of
	long double x; //x-coordinate of solar system's (0,0) in global coordinate system
	long double y; //y-coordinate of solar system's (0,0) in global coordinate system
	Volume bounding_volume; //bounding volume in global coordinates, click on which is considered click on solar system
	Vectorld2d speed; //speed of solar system's (0,0)
	Vectorld2d acceleration; //acceleration of solar system
public:
	SolarSystem(std::vector<PlanetSystem*> systs, long double ax, long double ay, Vectorld2d sp);

	//getter for mass of the system as sum of masses of planet systems
	long double get_mass() const;
	//getter for planetary systems
	std::vector<PlanetSystem*> get_systems() const;
	//getter for x-coordinate
	long double get_x() const;
	//getter for y-coordinate 
	long double get_y() const;
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
	//adds planetary system to solar system, changes coordinates of planetary system according to coordinates os solar system
	void add_system(PlanetSystem* ps);

	//moves system to specified coordinates
	void move(int astep);

	//finds baricenter coordinates of planetary system in its coordinate system
	std::vector<long double> baricenter();

	// simulates moving of elemets of planetary system
	void simulate(int step);

	//checks if solar system is clicked
	bool is_clicked(sf::Vector2f pointer);

	//resizes shapes of all planets in solar system
	void resize_shapes(float s);

	//draws all elemets of the system
	void draw_system(sf::RenderWindow& w);

	//calculates distance between two planetary systems
	friend const long double distance(const SolarSystem& ps1, const SolarSystem& ps2);

	//calculates summary vector of gravitational force on planet system from planet systems
	friend Vectorld2d grav_force(const SolarSystem& ps, std::vector<SolarSystem*> psystems);

	//calculates summary vector of acceleration from gravitational force on planet system from planet systems and sets planet's acceleration to it
	friend void grav_pull(SolarSystem& ps, std::vector<SolarSystem*> psystems);
};

