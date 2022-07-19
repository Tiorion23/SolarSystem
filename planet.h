#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>
#include <array>
#include <string>
#include "Vectorld2d.h"
#include "Volume.h"
#define G 6.67e-11
#define PI atan(1) * 4

//The class for Planets
class Planet
{
	//physical parameters
	const std::string name;
	long double diameter; // diameter of planet
	long double mass; // mass of planet
	long double x;    // x coordinate of planet in Planetary system (NOT GLOBAL COORDINATE)
	long double y;    // y coodrdinate of planet in Planetary system (NOT GLOBAL COORDINATE)
	Volume bounding_volume; //bounding volume in planetary system's coordinates, click on which is considered click on planet
	long double phi;  // angular speed of planet, rad/s
	Vectorld2d speed; // speed of planet on x-axis and y axis
	Vectorld2d acceleration; //acceleration of planet on x-axis and y axis
	//graphical parameters
	sf::CircleShape shape;	

public:
	// constructor
	// nm - name of the planet, 
	// diam - diameter, m - mass in kg, 
	// xc - x coordinate in Planetary system's coordinates,
	// yc - y coordinate in planetary system's coordinates, 
	// sp - speed in planetary system,
	//color - color of planet on display, shapesize - size of planet on display in pixels
	Planet(std::string nm, long double diam, long double m, long double xc, long double yc, Vectorld2d sp,
		sf::Color color, float shapesize);

	//destructor
	//~Planet();

	//operator == overload for Planet class
	friend bool operator== (const Planet& p1, const Planet& p2);
	//operator != overload for Planet class
	friend bool operator!= (const Planet& p1, const Planet& p2);

	//calculates distance between two planets
	friend const long double distance(const Planet& p1, const Planet& p2);

	//calculates summary vector of gravitational force on planet p from planets
	friend Vectorld2d grav_force(const Planet& p, std::vector<Planet*> planets);

	//calculates summary vector of acceleration from gravitational force on planet p from planets and sets planet's acceleration to it
	friend void grav_pull(Planet& p, std::vector<Planet*> planets);

	//returns list of planets without planet p
	friend std::vector<Planet*> interaction_list(const Planet& p, std::vector<Planet*> planets);

	//resizes shape of planet by
	void resize_shape(float s);

	//getter for name
	std::string get_name() const;

	//getter for diameter
	long double get_diameter();

	//getter for speed vector
	Vectorld2d get_speed() const;

	//setter for speed of planet
	void set_speed(Vectorld2d sp);

	//updates speed with current acceleration with given step
	void update_speed(int astep);

	//getter for acceleration
	Vectorld2d get_acceleration();

	//setter for acceleration
	void set_acceleration(Vectorld2d acc);

	//getter for mass
	long double get_mass() const;

	//getter for x coordinate
	long double get_x() const;

	//sets x coordinate of Planet
	void set_x(long double arg);

	//getter for y coordinate
	long double get_y() const;

	//sets y coordinate of Planet
	void set_y(long double arg);

	//moves planet and its shape on display by adding to current coordinates current speed
	void move(int step);

	//draws this planet's shape
	void draw_planet(sf::RenderWindow &w);

	//draws this planet's shape taking in account coordinates of (0, 0) of planetary system xx and yy in solar system
	void draw_planet(sf::RenderWindow& w, long double xx, long double yy);

	//checks if planet is clicked
	bool is_clicked(sf::Vector2f pointer);
};

