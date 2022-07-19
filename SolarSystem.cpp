#include "SolarSystem.h"

SolarSystem::SolarSystem(std::vector<PlanetSystem*> systs, long double ax, long double ay, Vectorld2d sp) {
	systems = systs;
	x = ax;
	y = ay;
	long double max_distance = 0;
	if (systems.size() != 0) {
		if (systems.size() != 1) {
			for (const auto& s : interaction_list(*systems[0], systems)) {
				if (distance(*systems[0], *s) > max_distance)
					max_distance = distance(*systems[0], *s);
			}
		}
		else {
			max_distance = systems[0]->get_planets()[0]->get_diameter() * 2;
		}
		bounding_volume = Volume(Vectorld2d(x, y), max_distance);
	}	
	speed = sp;
	acceleration = Vectorld2d();
}

long double SolarSystem::get_mass() const {
	long double m = 0;
	for (const auto& a : systems) {
		m += a->get_mass();
	}
	return m;
}

std::vector<PlanetSystem*> SolarSystem::get_systems() const { return systems; }

long double SolarSystem::get_x() const { return x; }
long double SolarSystem::get_y() const { return y; }
Vectorld2d SolarSystem::get_speed() const { return speed; }
void SolarSystem::set_speed(Vectorld2d aspeed) { speed = aspeed; }
void SolarSystem::update_speed(int astep) { 
	Vectorld2d temp = acceleration * astep;
	Vectorld2d temp1 = speed + temp;
	speed = temp1; }
Vectorld2d SolarSystem::get_acceleration() { return acceleration; }
void SolarSystem::set_acceleration(Vectorld2d acc) { acceleration = acc; }

void SolarSystem::add_system(PlanetSystem* ps)
{
	systems.push_back(ps);
	ps->set_x(x + ps->get_x());
	ps->set_y(y + ps->get_y());
}

void SolarSystem::move(int astep) {
	x += speed[0] * astep;
	//shape.setPosition(x / 1000000000 + 640, y / 1000000000 + 360);
	y += speed[1] * astep;
	bounding_volume = Volume(Vectorld2d(x, y), bounding_volume.get_size());
}

std::vector<long double> SolarSystem::baricenter() {
	std::vector<long double> result{ 0, 0 };
	for (const auto& a : systems) {
		result[0] += a->get_mass() * a->get_x() / get_mass();
		result[1] += a->get_mass() * a->get_y() / get_mass();
	}
	return result;
}

void SolarSystem::simulate(int step) {
	for (auto& a : systems) {
		a->simulate(step);
		grav_pull(*a, interaction_list(*a, get_systems()));
		a->update_speed(step);
		a->move(step);
	}
	std::vector<long double> baric = baricenter();
	for (auto& a : systems) {
		a->set_x(a->get_x() - baric[0]);
		a->set_y(a->get_y() - baric[1]);
	}
}

bool SolarSystem::is_clicked(sf::Vector2f pointer)
{
	return bounding_volume.isPointInVolume(Vectorld2d(pointer.x, pointer.y));
}

void SolarSystem::resize_shapes(float s) {
	for (const auto& a : systems)
		a->resize_shapes(s);
}

void SolarSystem::draw_system(sf::RenderWindow& w) {
	for (const auto& a : systems) {
		a->draw_system(w);
	}
}

const long double distance(const SolarSystem& ss1, const SolarSystem& ss2)
{
	return sqrt(pow(ss2.x - ss1.x, 2) + pow(ss2.y - ss1.y, 2));
}

Vectorld2d grav_force(const SolarSystem& ss, std::vector<SolarSystem*> ssystems) {
	Vectorld2d f = Vectorld2d(0, 0);
	if (ssystems.size() == 0)
		return f;
	for (int i = 0; i < ssystems.size(); i++) {
		long double fl = 0;
		if (distance(ss, *ssystems[i]) != 0)
			fl = (G * ss.get_mass() * ssystems[i]->get_mass()) / pow(distance(ss, *ssystems[i]), 2);
		else
			fl = 0;
		long double alpha = acos(fabs(ssystems[i]->get_x() - ss.get_x()) / distance(ss, *ssystems[i]));
		long double fx = 0, fy = 0;
		if (ssystems[i]->get_x() < ss.get_x())
			fx = (-fl * cos(alpha));
		else
			fx = (fl * cos(alpha));
		if (ssystems[i]->get_y() < ss.get_y())
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

void grav_pull(SolarSystem& ss, std::vector<SolarSystem*> ssystems) {
	Vectorld2d f = grav_force(ss, ssystems);
	ss.set_acceleration(f * (1e0 / ss.get_mass()));
}
