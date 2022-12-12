#include "SolarSystem.h"

SolarSystem::SolarSystem(std::vector<PlanetSystem*> systems, Vectorld2d coords, Vectorld2d sp, std::string aname) : MaterialPoint(coords, 0, sp), name((aname == "") ? ("SS-" + id):(aname)) {
	SolarSystem::id += 1;
	this -> systems = systems;						// vector of planetary systems that solar system consists of
	long double m = 0;
	for (const auto& a : systems) { // calculating mass of system
		m += a->get_mass();
	}
	this->set_mass(m);					// setting mass of system	
	Vectorld2d baric = baricenter();		//calculates coordinates of baricenter of solar system 
	for (auto& ps : systems) {				//changes coordinates of all planetary systems according to baricenter
		ps->set_coords(Vectorld2d(ps->get_coords().x - baric.x, ps->get_coords().y - baric.y));
	}
	for (auto& ps : systems) {								// for each planetary system in solar system
		ps->set_global_coords(Vectorld2d(this->coords.x + ps->get_coords().x, this->coords.y + ps->get_coords().y)); // set global coordinates according to global coordinate of solar system
		for (auto& p : ps->get_planets()) {						// for each planet in planetary system
			p->set_global_coords(Vectorld2d(ps->get_global_coords().x + p->get_coords().x, ps->get_global_coords().y + p->get_coords().y));
			// set global coordinate according to global coordinate of planetary system
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
std::string SolarSystem::get_name() { return this->name; }
long double SolarSystem::get_mass() const {
	long double m = 0;
	for (const auto& a : systems) {
		m += a->get_mass();
	}
	return m;
}

	//////////////////////////////////////////////////////////////////
	///////////////////// PHYSICAL INTERACTIONS //////////////////////
	//////////////////////////////////////////////////////////////////

void SolarSystem::simulate(float astep) {
	/*sf::Clock clock;
	sf::Time elapsed = clock.restart();
	long double dt = elapsed.asSeconds();
	std::cout << std::setprecision(7) << "Simulation tick took " << dt << " seconds" << "\n";*/
	for (int i = 0; i < systems.size(); i++) {
		for (int j = i + 1; j < systems.size(); j++) {
			systems[i]->grav_pull(systems[j]);
		}
	}
	for (const auto& a : systems) {					//for each planet system in solar system		
		a->update_speed(astep);								//updating speed according to calculated acceleration and given time-step
		a->move(astep);										//moving planet according to calculated speed and given time-step
	}
	Vectorld2d baric = baricenter();	//calculating new position of baricenter
	for (auto& a : systems) {				//changing each planet system's coordinates according to new baricenter
		a->set_coords(Vectorld2d(a->get_coords().x - baric.x, a->get_coords().y - baric.y)); //local coordinates change, as baricenter (0,0) moves
		a->set_global_coords(Vectorld2d(this->coords.x + a->get_coords().x, this->coords.y + a->get_coords().y));
		//global coordinates change as well, because (0,0) represents material point,
		//which interacts with other planetary systems and is the ccenter of masses
	}
	for (auto& a : systems)		// after defining new coordinates of all planetary systems
		a->simulate(astep);					// simulating movement of planets in each planetary system
}

	//////////////////////////////////////////////////////////////////
	//////////////////////// UTILITY FUNCTIONS ///////////////////////
	//////////////////////////////////////////////////////////////////
	// includes friend function that returns vector of planetary systems without given planetary system
	// draw functions

Vectorld2d SolarSystem::baricenter() {
	Vectorld2d result;
	for (const auto& a : systems) {
		result.x += a->get_mass() * a->get_coords().x / get_mass();
		result.y += a->get_mass() * a->get_coords().y / get_mass();
	}
	return result;
}

void SolarSystem::resize_shapes(float s) {
	for (const auto& a : systems)
		a->resize_shapes(s);
}

void SolarSystem::draw(sf::RenderWindow& w) {
	for (const auto& a : systems) {
		a->draw(w);
	}
}

#ifndef SSID
#define SSID
int SolarSystem::id = 0;
#endif

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
