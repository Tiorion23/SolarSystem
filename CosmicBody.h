#ifndef COSMIC_BODY
#define COSMIC_BODY

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>
#include <array>
#include <string>
#include "Vectorld2d.h"
#include "Volume.h"
#define G 6.67e-11
#define PI atan(1) * 4

enum class CosmicBodyType {STAR, PLANET, SATELLITE};
std::string cosmic_body_type_to_str(CosmicBodyType type);

//The class for all kinds of cosmic bodies: stars, planets, sattelites, in future - asteroids and comets
class CosmicBody
{
	//physical parameters
	CosmicBodyType type;
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
	// nm - name of the cosmic body, 
	// diam - diameter, m - mass in kg, 
	// xc - x coordinate in Planetary system's coordinates,
	// yc - y coordinate in planetary system's coordinates, 
	// sp - speed in planetary system,
	// shape - assigned shape, that is graphical representation of body
	CosmicBody(CosmicBodyType tp, std::string nm, long double diam, long double m, long double xc, long double yc, Vectorld2d sp, sf::CircleShape shp);

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
	//sets x coordinate of body
	void set_x(long double arg);
	//getter for global x
	long double get_global_x();	
	//seter global x coordinate of body
	void set_global_x(long double arg);

	//getter for y coordinate
	long double get_y() const;
	//sets y coordinate of body
	void set_y(long double arg);
	//getter for global y coordinate
	long double get_global_y();	
	//sets global y coordinate of body
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
	// including friend functions for calculating gravitational force and pull from given vector of bodies, distance between 
	// two bodies

	//calculates distance between centers of two bodies
	friend const long double distance(const CosmicBody& cb1, const CosmicBody& cb2);

	//calculates summary vector of gravitational force on body cb from any number of other bodies
	friend Vectorld2d grav_force(const CosmicBody& cb, std::vector<CosmicBody*> bodies);

	//calculates summary vector of acceleration from gravitational force on body cb from any number of other bodies and sets it's acceleration to calculated value
	friend void grav_pull(CosmicBody& cb, std::vector<CosmicBody*> bodies);

	//updates speed with current acceleration with given step
	void update_speed(int astep);

	//moves body (both local and global coordinates and bounding volume) according to current speed and given time-step
	void move(int step);

	//////////////////////////////////////////////////////////////////
	//////////////////////// UTILITY FUNCTIONS ///////////////////////
	//////////////////////////////////////////////////////////////////
	// includes friend function that returns vector of bodies without given body
	// draw and other graphic related functions

	//returns list of bodies without body cb
	friend std::vector<CosmicBody*> interaction_list(const CosmicBody& cb, std::vector<CosmicBody*> bodies);

	//resizes shape of body by
	void resize_shape(float s);

	//updates position of bounding volume based on current global coordinates
	void update_bounding_volume();

	//draws this body by its global coordinates
	void draw(sf::RenderWindow& w);

	//checks if body is clicked
	bool is_clicked(sf::Vector2f pointer);

	//////////////////////////////////////////////////////////////////
	///////////////// COMPARISON OPERATORS OVERLOAD //////////////////
	//////////////////////////////////////////////////////////////////

	//operator == overload for Planet class
	friend bool operator== (const CosmicBody& cb1, const CosmicBody& cb2);
	//operator != overload for Planet class
	friend bool operator!= (const CosmicBody& cb1, const CosmicBody& cb2);
};

#endif