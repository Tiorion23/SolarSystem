#include "SolarSystem.h"

SolarSystem::SolarSystem(std::vector<PlanetSystem*> systs, long double ax, long double ay, Vectorld2d sp) {
	global_coords = Vectorld2d(ax, ay);
	systems = systs;						// vector of planetary systems that solar system consists of
	Vectorld2d baric = baricenter();		//calculates coordinates of baricenter of solar system 
	for (auto& ps : systems) {				//changes coordinates of all planetary systems according to baricenter
		ps->set_x(ps->get_x() - baric.x);
		ps->set_y(ps->get_y() - baric.y);
	}
	long double max_distance = 0;	
	if (systems.size() > 1) {
		for (const auto& s : interaction_list(*systems[0], systems)) {
			if (distance(*systems[0], *s) > max_distance)
				max_distance = distance(*systems[0], *s);
		}
	}
	else if (systems.size() == 1) {
		max_distance = systems[0]->get_planets()[0]->get_diameter() * 2;
	}
	bounding_volume = Volume(global_coords, max_distance);
	for (auto& ps : systems) {								// for each planetary system in solar system
		ps->set_global_x(global_coords.x + ps->get_x());				// set global coordinate according to global coordinate of solar system
		ps->set_global_y(global_coords.y + ps->get_y());				// set global coordinate according to global coordinate of solar system
		ps->update_bounding_volume();
		for (auto& p : ps->get_planets()) {						// for each planet in planetary system
			p->set_global_x(ps->get_global_x() + p->get_x());		// set global coordinate according to global coordinate of planetary
			p->set_global_y(ps->get_global_y() + p->get_y());		// system
			p->update_bounding_volume();
		}
	}
	speed = sp;
	acceleration = Vectorld2d();
}

	//////////////////////////////////////////////////////////////////
	///////////////// INTERFACE: GETTERS AND SETTERS /////////////////
	//////////////////////////////////////////////////////////////////
	//provided getters and setters for whole coordinate in vector as well as individual X and Y coordinates

std::vector<PlanetSystem*> SolarSystem::get_systems() const { return systems; }
long double SolarSystem::get_mass() const {
	long double m = 0;
	for (const auto& a : systems) {
		m += a->get_mass();
	}
	return m;
}
long double SolarSystem::get_global_x() const { return global_coords.x; }
void SolarSystem::set_global_x(long double ax) { global_coords.x = ax; }
long double SolarSystem::get_global_y() const { return global_coords.y; }
void SolarSystem::set_global_y(long double ay) { global_coords.y = ay; }
Vectorld2d SolarSystem::get_global_coords() { return global_coords; }
void SolarSystem::set_global_coords(Vectorld2d c) { global_coords = c; }
Vectorld2d SolarSystem::get_speed() const { return speed; }
void SolarSystem::set_speed(Vectorld2d aspeed) { speed = aspeed; }
Vectorld2d SolarSystem::get_acceleration() { return acceleration; }
void SolarSystem::set_acceleration(Vectorld2d acc) { acceleration = acc; }

	//////////////////////////////////////////////////////////////////
	///////////////////// PHYSICAL INTERACTIONS //////////////////////
	//////////////////////////////////////////////////////////////////
	// including friend functions for calculating gravitational force and pull from given vector of solar systems, distance between 
	// two solar systems

const long double distance(const SolarSystem& ss1, const SolarSystem& ss2)
{
	return sqrt(pow(ss2.global_coords.x - ss1.global_coords.x, 2) + pow(ss2.global_coords.y - ss1.global_coords.y, 2));
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
		long double alpha = acos(fabs(ssystems[i]->get_global_x() - ss.get_global_x()) / distance(ss, *ssystems[i]));
		long double fx = 0, fy = 0;
		if (ssystems[i]->get_global_x() < ss.get_global_x())
			fx = (-fl * cos(alpha));
		else
			fx = (fl * cos(alpha));
		if (ssystems[i]->get_global_y() < ss.get_global_y())
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

void SolarSystem::update_speed(int astep) { 
	speed = speed + acceleration * astep; 
}

void SolarSystem::move(int astep) {
	global_coords = global_coords + (speed * astep);
	bounding_volume = Volume(Vectorld2d(global_x, global_y), bounding_volume.get_size());
}

void SolarSystem::simulate(int step) {
	for (auto& a : systems) {		//for each planetary system in solar system
		grav_pull(*a, interaction_list(*a, systems)); // calculating summary acceleration from all other planetary systems
		a->update_speed(step);	// updating speed of planetary system according to calculated acceleration and give time-step
		a->move(step);			//moving planetary system according to current speed and time-step		
	}
	Vectorld2d baric = baricenter();	//calculating new baricenter (0,0) of solar system
	for (auto& a : systems) {			//changing coordinates of planetary systems according to new baricenter
		a->set_x(a->get_x() - baric.x);			//local coordinates of planetary systems change, as (0,0) moves
		a->set_y(a->get_y() - baric.y);
		a->set_global_x(a->get_x() + global_coords.x);	//changing global coordinates according to current global coordinates of solar system,
		a->set_global_y(a->get_y() + global_coords.y);	//and calculated local coordinates of planetary system
		a->update_bounding_volume();
	}
	for (auto& a : systems)		// after defining new coordinates of all planetary systems
		a->simulate(step);					// simulating movement of planets in each planetary system
}

	//////////////////////////////////////////////////////////////////
	//////////////////////// UTILITY FUNCTIONS ///////////////////////
	//////////////////////////////////////////////////////////////////
	// includes friend function that returns vector of planetary systems without given planetary system
	// draw functions

std::vector<SolarSystem*> interaction_list(const SolarSystem& ss, std::vector<SolarSystem*> ssystems) {
	std::vector<SolarSystem*> result;
	for (const auto& a : ssystems) {
		if (*a != ss)
			result.push_back(a);
	}
	return result;
}

Vectorld2d SolarSystem::baricenter() {
	Vectorld2d result;
	for (const auto& a : systems) {
		result.x += a->get_mass() * a->get_x() / get_mass();
		result.y += a->get_mass() * a->get_y() / get_mass();
	}
	return result;
}

void SolarSystem::update_bounding_volume() {
	bounding_volume.set_coordinates(Vectorld2d(global_x, global_y));
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

	//////////////////////////////////////////////////////////////////
	///////////////// COMPARISON OPERATORS OVERLOAD //////////////////
	//////////////////////////////////////////////////////////////////

//T0D0: come up with the way of solar systems comparison
// 
//bool operator==(const SolarSystem& ss1, const SolarSystem& ss2)
//{
//	if (ss1.name == ss2.name)
//		return true;
//	return false;
//}
//
//bool operator!=(const SolarSystem& ss1, const SolarSystem& ss2)
//{
//	if (ss1.name != ss2.name)
//		return true;
//	return false;
//}
