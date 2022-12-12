#ifndef COSMIC_BODY
#define COSMIC_BODY

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>
#include <array>
#include <string>
#include "Vectorld2d.h"
#include "Volume.h"
#include "MaterialPoint.h"
#include "PlanetSystem.h"
#define G 6.67e-11
#define PI atan(1) * 4

enum class CosmicBodyType {STAR, PLANET, SATELLITE};
std::string cosmic_body_type_to_str(CosmicBodyType type);
class MaterialPoint;
class PlanetSystem;

// The class for all kinds of cosmic bodies: stars, planets, sattelites, in future - asteroids and comets
// inherits from Material Point all necessary physical parameters and interactions
class CosmicBody: public MaterialPoint
{	
	// physical parameters
	CosmicBodyType type;		// type of cosmic body, not const, because eventually after collision realization bodies will be able to change types
	const std::string name;
	long double diameter;		// diameter of planet	
	Vectorld2d global_coords;	// global x, y coordinates of planet, used for bounbing volume click detection (T0D0: collision detection)
	//Volume bounding_volume; //bounding volume in global coordinates, click on which is considered click on planet
	long double phi;  // angular speed of planet, rad/s
	// members for graphical representation of cosmic body
	sf::CircleShape* shape;

public:
	PlanetSystem* system;
	// constructor
	// type - type of cosmic body, may be STAR, PLANET, SATELLITE for now
	// name - name of the cosmic body, 
	// diam - diameter, m - mass in kg, 
	// coords in planet system's coordinate system, 
	// sp - speed in planetary system,
	// shape - pointer to assigned shape, that is graphical representation of body
	CosmicBody(CosmicBodyType type, std::string name, long double diam, long double m, Vectorld2d coords, Vectorld2d sp, sf::CircleShape* shp);

	//////////////////////////////////////////////////////////////////
	///////////////// INTERFACE: GETTERS AND SETTERS /////////////////
	//////////////////////////////////////////////////////////////////
	// getter for planetary system in which this body is currently situated
	PlanetSystem* get_system() const;
	// sets planetary system
	void set_system(PlanetSystem* system);
	// getter for body type
	CosmicBodyType get_type() const;
	//getter for name
	std::string get_name() const;

	//getter for diameter
	long double get_diameter() const;

	// returns vector that represents global coords of body
	Vectorld2d get_global_coords() const;
	// sets global coordinates of body
	void set_global_coords(Vectorld2d c);

	//////////////////////////////////////////////////////////////////
	//////////////////////// UTILITY FUNCTIONS ///////////////////////
	//////////////////////////////////////////////////////////////////
	// includes friend function that returns vector of bodies without given body
	// draw and other graphic related functions

	//resizes shape of body by
	void resize_shape(float s);

	//updates position of bounding volume based on current global coordinates
	//void update_bounding_volume();

	//draws this body by its global coordinates
	void draw(sf::RenderWindow& w);

	//////////////////////////////////////////////////////////////////
	///////////////// COMPARISON OPERATORS OVERLOAD //////////////////
	//////////////////////////////////////////////////////////////////

	//operator == overload for Planet class
	friend bool operator== (const CosmicBody& cb1, const CosmicBody& cb2);
	//operator != overload for Planet class
	friend bool operator!= (const CosmicBody& cb1, const CosmicBody& cb2);
};

#endif