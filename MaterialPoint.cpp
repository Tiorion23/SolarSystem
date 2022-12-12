#include "MaterialPoint.h"

MaterialPoint::MaterialPoint(Vectorld2d coords, long double mass, Vectorld2d speed) {
	this->coords = coords;
	this->mass = mass;
	this->speed = speed;
	this->acceleration = Vectorld2d();
}

Vectorld2d MaterialPoint::get_speed() const {
	return speed;
}

void MaterialPoint::set_speed(Vectorld2d speed) {
	this->speed = speed;
}

Vectorld2d MaterialPoint::get_acceleration() const {
	return acceleration;
}

void MaterialPoint::set_acceleration(Vectorld2d acceleration) {
	this->acceleration = acceleration;
}

long double MaterialPoint::get_mass() const {
	return mass;
}

void MaterialPoint::set_mass(long double mass) {
	this->mass = mass;
}

Vectorld2d MaterialPoint::get_coords() const {
	return coords;
}

void MaterialPoint::set_coords(Vectorld2d coords) {
	this->coords = coords;
}

const long double MaterialPoint::distance(const MaterialPoint& point)
{
	return sqrt(pow(point.get_coords().x - this->coords.x, 2) + pow(point.get_coords().y - this->coords.y, 2));
}

void MaterialPoint::update_speed(float timestep) {
	speed = speed + acceleration * timestep;
	acceleration = Vectorld2d();
}

void MaterialPoint::move(float timestep) {
	coords = coords + (speed * timestep);
}

Vectorld2d MaterialPoint::grav_force(MaterialPoint* point)
{
	Vectorld2d f = Vectorld2d();
	long double dist = distance(*point);
	if (this == point)
		return f;
	long double fl = 0;
	if (dist != 0)
		fl = (G * this->mass * point->get_mass()) / pow(dist, 2);
	else
		fl = 0;
	long double alpha = acos(fabs(point->get_coords().x - this->coords.x) / dist);
	long double fx = 0, fy = 0;
	if (point->get_coords().x < this->coords.x)
		fx = (-fl * cos(alpha));
	else
		fx = (fl * cos(alpha));
	if (point->get_coords().y < this->coords.y)
		fy = (-fl * sin(alpha));
	else
		fy = (fl * sin(alpha));
	f.x += fx;
	f.y += fy;
	return f;
}

void MaterialPoint::grav_pull(MaterialPoint* point) {
	Vectorld2d f = grav_force(point);
	this->acceleration = acceleration + (f * (1e0 / this->mass));
	f.mirror();
	point->acceleration = point->acceleration + (f * (1e0 / point->mass));
}

