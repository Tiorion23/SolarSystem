#include "CosmicBody.h"

std::string cosmic_body_type_to_str(CosmicBodyType type) {
	switch (type) {
	default:
	case CosmicBodyType::STAR: return "star";
	case CosmicBodyType::PLANET: return "planet";
	case CosmicBodyType::SATELLITE: return "satellite";
	}
}

CosmicBody::CosmicBody(CosmicBodyType tp, std::string nm, long double diam, long double m, long double xc, long double yc, Vectorld2d sp, sf::CircleShape shp): name(nm) {
	type = tp;
	diameter = diam;
	mass = m;
	coords = Vectorld2d(xc, yc);
	global_coords = Vectorld2d(xc, yc);	
	bounding_volume = Volume(global_coords, diameter / 2);
	speed = sp;
	acceleration = Vectorld2d(0, 0);
	phi = (pow(sqrt(pow(xc,2)+pow(yc,2)), 2) + pow(sqrt(pow(xc, 2) + pow(yc, 2)), 2) - pow(sqrt(pow(sp[0], 2) + pow(sp[1], 2)), 2)) / (2 * sqrt(pow(xc, 2) + pow(yc, 2)) * sqrt(pow(xc, 2) + pow(yc, 2)));
	shape = shp;
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

CosmicBodyType CosmicBody::get_type() { return type; }
std::string CosmicBody::get_name() const { return name; }
long double CosmicBody::get_diameter() { return diameter; }
Vectorld2d CosmicBody::get_speed() const { return speed; }
void CosmicBody::set_speed(Vectorld2d sp) { speed = sp; }
Vectorld2d CosmicBody::get_acceleration() { return acceleration; }
void CosmicBody::set_acceleration(Vectorld2d acc) { acceleration = acc; }
long double CosmicBody::get_mass() const { return mass; }
void CosmicBody::set_mass(long double m) { mass = m; }

long double CosmicBody::get_x() const { return coords.x; }
void CosmicBody::set_x(long double arg) { coords.x = arg; }
long double CosmicBody::get_y() const { return coords.y; }
void CosmicBody::set_y(long double arg) { coords.y = arg; }
long double CosmicBody::get_global_x() { return global_coords.x; }
long double CosmicBody::get_global_y() { return global_coords.y; }
void CosmicBody::set_global_x(long double arg) { global_coords.x = arg; }
void CosmicBody::set_global_y(long double arg) { global_coords.y = arg; }

Vectorld2d CosmicBody::get_coords() { return coords; }
void CosmicBody::set_coords(Vectorld2d c) { coords = c; }
Vectorld2d CosmicBody::get_global_coords() { return global_coords; }
void CosmicBody::set_global_coords(Vectorld2d c) { global_coords = c; }

	//////////////////////////////////////////////////////////////////
	///////////////////// PHYSICAL INTERACTIONS //////////////////////
	//////////////////////////////////////////////////////////////////
	// including friend functions for calculating gravitational force and pull from given vector of bodies, distance between 
	// two bodies

const long double distance(const CosmicBody& cb1, const CosmicBody& cb2) {
	return sqrt(pow(cb2.coords.x - cb1.coords.x, 2) + pow(cb2.coords.y - cb1.coords.y, 2));
}

Vectorld2d grav_force(const CosmicBody& cb, std::vector<CosmicBody*> bodies) {
	Vectorld2d f = Vectorld2d(0, 0);
	if (bodies.size() == 0)
		return f;
	for (int i = 0; i < bodies.size(); i++) {
		long double fl = 0;
		if (distance(cb, *bodies[i]) != 0)
			fl = (G * cb.get_mass() * bodies[i]->get_mass()) / pow(distance(cb, *bodies[i]), 2);
		else
			fl = 0;
		long double alpha = acos(fabs(bodies[i]->get_x() - cb.get_x()) / distance(cb, *bodies[i]));
		long double fx = 0, fy = 0;
		if (bodies[i]->get_x() < cb.get_x())
			fx = (-fl * cos(alpha));
		else
			fx = (fl * cos(alpha));
		if (bodies[i]->get_y() < cb.get_y())
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

void grav_pull(CosmicBody& cb, std::vector<CosmicBody*> bodies) {
	Vectorld2d f = grav_force(cb, bodies);
	cb.set_acceleration(f * (1e0 / cb.get_mass()));
}

void CosmicBody::update_speed(int astep) {
	speed = speed + acceleration * astep; }

void CosmicBody::move(int step) {
	coords = coords + (speed * step);
}

	//////////////////////////////////////////////////////////////////
	//////////////////////// UTILITY FUNCTIONS ///////////////////////
	//////////////////////////////////////////////////////////////////
	// includes friend function that returns vector of bodies without given body
	// draw and other graphic related functions

std::vector<CosmicBody*> interaction_list(const CosmicBody& cb, std::vector<CosmicBody*> bodies) {
	std::vector<CosmicBody*> result;
	for (const auto& a : bodies) {
		if (*a != cb)
			result.push_back(a);
	}
	return result;
}

void CosmicBody::resize_shape(float s) {
	/*if (shape.getRadius() == diameter / 2 && s < 1)
		return;*/
	shape.scale(s, s);
}

void CosmicBody::update_bounding_volume() {
	bounding_volume.set_coordinates(global_coords);
}

void CosmicBody::draw(sf::RenderWindow& w) {
	shape.setPosition(global_coords.x, global_coords.y);
	bounds.setPosition(global_coords.x, global_coords.y);
	w.draw(shape);
	//w.draw(bounds);		//uncomment to draw bounding volume bounds
}

bool CosmicBody::is_clicked(sf::Vector2f pointer)
{
	return bounding_volume.isPointInVolume(Vectorld2d(pointer.x, pointer.y));
}

	//////////////////////////////////////////////////////////////////
	///////////////// COMPARISON OPERATORS OVERLOAD //////////////////
	//////////////////////////////////////////////////////////////////

bool operator==(const CosmicBody& cb1, const CosmicBody& cb2)
{
	if (cb1.name == cb2.name)
		return true;
	return false;
}

bool operator!=(const CosmicBody& cb1, const CosmicBody& cb2)
{
	if (cb1.name != cb2.name)
		return true;
	return false;
}