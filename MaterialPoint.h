#ifndef MAT_PT
#define MAT_PT
#include <math.h>
#include <vector>
#include "Vectorld2d.h"
#define G 6.67e-11
#define PI atan(1) * 4
// class representing material point, that has coordinates, mass, speed and acceleration,
// handles physical interactions betwen material points such as gravitational interaction,
// also able to calculate distance to another material point 
class MaterialPoint {
protected:
	Vectorld2d coords;			// x, y coordinates of material point
	long double mass;			// mass of object, material point represents
	Vectorld2d speed;			// speed of material point on x-axis and y-axis
	Vectorld2d acceleration;	// acceleration of material point on x-axis and y axis
public:
	MaterialPoint(Vectorld2d coords, long double mass, Vectorld2d speed);

	// returns speed vector
	Vectorld2d get_speed() const;
	// sets speed of material point
	void set_speed(Vectorld2d speed);

	// returns vector that conatins acceleration of material point
	Vectorld2d get_acceleration() const;
	// sets acceleration of material point
	void set_acceleration(Vectorld2d acceleration);

	// returns mass of material point
	long double get_mass() const;
	// sets mass of material point
	void set_mass(long double mass);

	// returns vector that represents coodrds of material point
	Vectorld2d get_coords() const;
	// sets coordinates of material point
	void set_coords(Vectorld2d coords);

	//calculates distance between this and another material point
	const long double distance(const MaterialPoint& point);

	//updates speed with current acceleration with given time-step
	void update_speed(float timestep);

	// moves material point according to its speed and given time-step
	void move(float timestep);

	// calculates vector of gravitational force on this material point from other material point
	Vectorld2d grav_force(MaterialPoint* point);

	// updates acceleration of both material points accordig to their mutual gravitational interaction
	void grav_pull(MaterialPoint* point);
};

#endif