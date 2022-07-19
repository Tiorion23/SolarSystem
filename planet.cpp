#include "planet.h"

Planet::Planet(std::string nm, long double diam, long double m, long double xc, long double yc, Vectorld2d sp,
	sf::Color color, float shapesize): name(nm) {
	diameter = diam;
	mass = m;
	x = xc;
	y = yc;
	bounding_volume = Volume(Vectorld2d(x, y), diameter / 2);
	speed = sp;
	acceleration = Vectorld2d(0, 0);
	phi = (pow(sqrt(pow(xc,2)+pow(yc,2)), 2) + pow(sqrt(pow(xc, 2) + pow(yc, 2)), 2) - pow(sqrt(pow(sp[0], 2) + pow(sp[1], 2)), 2)) / (2 * sqrt(pow(xc, 2) + pow(yc, 2)) * sqrt(pow(xc, 2) + pow(yc, 2)));
	shape = sf::CircleShape(shapesize);
	shape.setFillColor(color);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	//shape.setPosition(x / 1000000000 + 640, y / 1000000000 + 360);
	shape.setPosition(x , y );
}

//Planet::~Planet() {}

std::string Planet::get_name() const { return name; }
Vectorld2d Planet::get_speed() const { return speed; }
long double Planet::get_diameter() { return diameter; }
void Planet::set_speed(Vectorld2d sp) { speed = sp; }
void Planet::update_speed(int astep) { 
	Vectorld2d temp = acceleration * astep;
	Vectorld2d temp1 = speed + temp;
	speed = temp1; }
Vectorld2d Planet::get_acceleration() { return acceleration; }
void Planet::set_acceleration(Vectorld2d acc) { acceleration = acc; }
long double Planet::get_mass() const { return mass; }
long double Planet::get_x() const { return x; }
void Planet::set_x(long double arg) { x = arg;  }

long double Planet::get_y() const { return y; }
void Planet::set_y(long double arg) { y = arg; }

void Planet::move(int step) {
	x += speed[0] * step;
	y += speed[1] * step;
	bounding_volume = Volume(Vectorld2d(x, y), diameter / 2);;
	//shape.setPosition(x / 1000000000 + 640, y / 100000000 + 360);
	//shape.setPosition(x , y );
}

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

const long double distance(const Planet& p1, const Planet& p2) {
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
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
		f[0] += fx;
		f[1] += fy;
	}
	return f;
}

void grav_pull(Planet& p, std::vector<Planet*> planets) {
	Vectorld2d f = grav_force(p, planets);
	p.set_acceleration(f * (1e0 / p.get_mass()));
}

std::vector<Planet*> interaction_list(const Planet& p, std::vector<Planet*> planets) {
	std::vector<Planet*> result;
	for (const auto& a : planets) {
		if (*a != p)
			result.push_back(a);
	}
	return result;
}

void Planet::resize_shape(float s) {
	if (shape.getRadius() == diameter / 2 && s < 1)
		return;
	shape.scale(s, s);
}

void Planet::draw_planet(sf::RenderWindow &w) {
	shape.setPosition(x, y);
	w.draw(shape);
}
/*
void Planet::draw_planet(sf::RenderWindow& w, long double xx, long double yy) {
	shape.setPosition((xx + x) / 1000000000 + 640, (yy + y) / 1000000000 + 360);
	w.draw(shape);
}*/

void Planet::draw_planet(sf::RenderWindow& w, long double xx, long double yy) {
	shape.setPosition((xx + x), (yy + y));
	w.draw(shape);
}

bool Planet::is_clicked(sf::Vector2f pointer)
{
	return bounding_volume.isPointInVolume(Vectorld2d(pointer.x, pointer.y));
}
