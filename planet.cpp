#include "planet.h"

Planet::Planet(std::string nm, long double diam, long double m, long double xc, long double yc, Vectorld2d sp,
	sf::Color color, float shapesize): name(nm) {
	diameter = diam;
	mass = m;
	coords = Vectorld2d(xc, yc);
	global_coords = Vectorld2d(xc, yc);	
	bounding_volume = Volume(global_coords, diameter / 2);
	speed = sp;
	acceleration = Vectorld2d(0, 0);
	phi = (pow(sqrt(pow(xc,2)+pow(yc,2)), 2) + pow(sqrt(pow(xc, 2) + pow(yc, 2)), 2) - pow(sqrt(pow(sp[0], 2) + pow(sp[1], 2)), 2)) / (2 * sqrt(pow(xc, 2) + pow(yc, 2)) * sqrt(pow(xc, 2) + pow(yc, 2)));
	shape = sf::CircleShape(shapesize);
	shape.setFillColor(color);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setPosition(global_coords.x , global_coords.y);
	bounds = sf::RectangleShape({ float(bounding_volume.get_size()*2),  float(bounding_volume.get_size()*2) });
	bounds.setOrigin(bounds.getSize() / 2.f);
	bounds.setPosition(global_coords.x, global_coords.y);
	bounds.setOutlineColor(sf::Color::Red);
	bounds.setOutlineThickness(1000000.f);
}

	//////////////////////////////////////////////////////////////////
	///////////////// INTERFACE: GETTERS AND SETTERS /////////////////
	//////////////////////////////////////////////////////////////////

std::string Planet::get_name() const { return name; }
long double Planet::get_diameter() { return diameter; }
Vectorld2d Planet::get_speed() const { return speed; }
void Planet::set_speed(Vectorld2d sp) { speed = sp; }
Vectorld2d Planet::get_acceleration() { return acceleration; }
void Planet::set_acceleration(Vectorld2d acc) { acceleration = acc; }
long double Planet::get_mass() const { return mass; }
void Planet::set_mass(long double m) { mass = m; }

long double Planet::get_x() const { return coords.x; }
void Planet::set_x(long double arg) { coords.x = arg; }
long double Planet::get_y() const { return coords.y; }
void Planet::set_y(long double arg) { coords.y = arg; }
long double Planet::get_global_x() { return global_coords.x; }
long double Planet::get_global_y() { return global_coords.y; }
void Planet::set_global_x(long double arg) { global_coords.x = arg; }
void Planet::set_global_y(long double arg) { global_coords.y = arg; }

Vectorld2d Planet::get_coords() { return coords; }
void Planet::set_coords(Vectorld2d c) { coords = c; }
Vectorld2d Planet::get_global_coords() { return global_coords; }
void Planet::set_global_coords(Vectorld2d c) { global_coords = c; }

	//////////////////////////////////////////////////////////////////
	///////////////////// PHYSICAL INTERACTIONS //////////////////////
	//////////////////////////////////////////////////////////////////
	// including friend functions for calculating gravitational force and pull from given vector of planets, distance between 
	// two planets

const long double distance(const Planet& p1, const Planet& p2) {
	return sqrt(pow(p2.coords.x - p1.coords.x, 2) + pow(p2.coords.y - p1.coords.y, 2));
}

Vectorld2d grav_force(const Planet& p, std::vector<Planet*> planets) {
	Vectorld2d f = Vectorld2d(0, 0);
	if (planets.size() == 0)
		return f;
	for (int i = 0; i < planets.size(); i++) {
		long double fl = 0;
		if (distance(p, *planets[i]) != 0)
			fl = (G * p.get_mass() * planets[i]->get_mass()) / pow(distance(p, *planets[i]), 2);
		else
			fl = 0;
		long double alpha = acos(fabs(planets[i]->get_x() - p.get_x()) / distance(p, *planets[i]));
		long double fx = 0, fy = 0;
		if (planets[i]->get_x() < p.get_x())
			fx = (-fl * cos(alpha));
		else
			fx = (fl * cos(alpha));
		if (planets[i]->get_y() < p.get_y())
			fy = (-fl * sin(alpha));
		else
			fy = (fl * sin(alpha));
		//fx = (fl * cos(alpha)); //WHY??? THIS DOESNT WORK??? if i remove fabs in alpha
		//fy = (fl * sin(alpha));
		f.x += fx;
		f.y += fy;
	}
	return f;
}

void grav_pull(Planet& p, std::vector<Planet*> planets) {
	Vectorld2d f = grav_force(p, planets);
	p.set_acceleration(f * (1e0 / p.get_mass()));
}

void Planet::update_speed(int astep) {
	speed = speed + acceleration * astep; }

void Planet::move(int step) {
	coords = coords + (speed * step);
}

	//////////////////////////////////////////////////////////////////
	//////////////////////// UTILITY FUNCTIONS ///////////////////////
	//////////////////////////////////////////////////////////////////
	// includes friend function that returns vector of planets without given planet
	// draw and other graphic related functions

std::vector<Planet*> interaction_list(const Planet& p, std::vector<Planet*> planets) {
	std::vector<Planet*> result;
	for (const auto& a : planets) {
		if (*a != p)
			result.push_back(a);
	}
	return result;
}

void Planet::resize_shape(float s) {
	/*if (shape.getRadius() == diameter / 2 && s < 1)
		return;*/
	shape.scale(s, s);
}

void Planet::update_bounding_volume() {
	bounding_volume.set_coordinates(global_coords);
}

void Planet::draw_planet(sf::RenderWindow& w) {
	shape.setPosition(global_coords.x, global_coords.y);
	bounds.setPosition(global_coords.x, global_coords.y);
	w.draw(shape);
	//w.draw(bounds);		//uncomment to draw bounding volume bounds
}

bool Planet::is_clicked(sf::Vector2f pointer)
{
	return bounding_volume.isPointInVolume(Vectorld2d(pointer.x, pointer.y));
}

	//////////////////////////////////////////////////////////////////
	///////////////// COMPARISON OPERATORS OVERLOAD //////////////////
	//////////////////////////////////////////////////////////////////

bool operator==(const Planet& p1, const Planet& p2)
{
	if (p1.name == p2.name)
		return true;
	return false;
}

bool operator!=(const Planet& p1, const Planet& p2)
{
	if (p1.name != p2.name)
		return true;
	return false;
}