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
	long double diameter;		// diameter of planet
	long double mass;			// mass of planet
	Vectorld2d coords;			// x, y coordinates of planet in planetary system, used for interaction between planets in planetary system	
	Vectorld2d global_coords;	// global x, y coordinates of planet, used for bounbing volume click detection (T0D0: collision detection)
	Volume bounding_volume; //bounding volume in global coordinates, click on which is considered click on planet
	long double phi;  // angular speed of planet, rad/s
	Vectorld2d speed; // speed of planet on x-axis and y axis
	Vectorld2d acceleration; //acceleration of planet on x-axis and y axis
	//graphical parameters
	sf::CircleShape shape;
	sf::RectangleShape bounds;

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

	//////////////////////////////////////////////////////////////////
	///////////////// INTERFACE: GETTERS AND SETTERS /////////////////
	//////////////////////////////////////////////////////////////////
	
	//getter for name
	std::string get_name() const;

	//getter for diameter
	long double get_diameter();

	//getter for speed vector
	Vectorld2d get_speed() const;
	//setter for speed of planet
	void set_speed(Vectorld2d sp);

	//getter for acceleration
	Vectorld2d get_acceleration();
	//setter for acceleration
	void set_acceleration(Vectorld2d acc);

	//getter for mass
	long double get_mass() const;
	//setter for mass
	void set_mass(long double m);

	//getter for x coordinate
	long double get_x() const;
	//sets x coordinate of Planet
	void set_x(long double arg);
	//getter for global x
	long double get_global_x();	
	//seter global x coordinate of Planet
	void set_global_x(long double arg);

	//getter for y coordinate
	long double get_y() const;
	//sets y coordinate of Planet
	void set_y(long double arg);
	//getter for global y coordinate
	long double get_global_y();	
	//sets global y coordinate of Planet
	void set_global_y(long double arg);
	//getter for coodrds
	Vectorld2d get_coords();
	//setter for coords
	void set_coords(Vectorld2d c);
	//getter for global coords
	Vectorld2d get_global_coords();
	//setter for global coords
	void set_global_coords(Vectorld2d c);

	//////////////////////////////////////////////////////////////////
	///////////////////// PHYSICAL INTERACTIONS //////////////////////
	//////////////////////////////////////////////////////////////////
	// including friend functions for calculating gravitational force and pull from given vector of planets, distance between 
	// two planets

	//calculates distance between two planets
	friend const long double distance(const Planet& p1, const Planet& p2);

	//calculates summary vector of gravitational force on planet p from planets
	friend Vectorld2d grav_force(const Planet& p, std::vector<Planet*> planets);

	//calculates summary vector of acceleration from gravitational force on planet p from planets and sets planet's acceleration to it
	friend void grav_pull(Planet& p, std::vector<Planet*> planets);

	//updates speed with current acceleration with given step
	void update_speed(int astep);

	//moves planet (both local and global coordinates and bounding volume) according to current speed and given time-step
	void move(int step);

	//////////////////////////////////////////////////////////////////
	//////////////////////// UTILITY FUNCTIONS ///////////////////////
	//////////////////////////////////////////////////////////////////
	// includes friend function that returns vector of planets without given planet
	// draw and other graphic related functions

	//returns list of planets without planet p
	friend std::vector<Planet*> interaction_list(const Planet& p, std::vector<Planet*> planets);

	//resizes shape of planet by
	void resize_shape(float s);

	//updates position of bounding volume based on current global coordinates
	void update_bounding_volume();

	//draws this planet's shape by its global coordinates
	void draw_planet(sf::RenderWindow& w);

	//checks if planet is clicked
	bool is_clicked(sf::Vector2f pointer);

	//////////////////////////////////////////////////////////////////
	///////////////// COMPARISON OPERATORS OVERLOAD //////////////////
	//////////////////////////////////////////////////////////////////

	//operator == overload for Planet class
	friend bool operator== (const Planet& p1, const Planet& p2);
	//operator != overload for Planet class
	friend bool operator!= (const Planet& p1, const Planet& p2);

	

	
};

