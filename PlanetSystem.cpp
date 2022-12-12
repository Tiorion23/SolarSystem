#include "PlanetSystem.h"

PlanetSystem::PlanetSystem(std::vector<CosmicBody*> ps, Vectorld2d coords, Vectorld2d sp): MaterialPoint(coords, 0, sp) {
	global_coords = coords;
	planets = ps;							// vector of planets planetary system consists of
	long double m = 0;
	for (const auto& a : planets) {
		m += a->get_mass();
	}
	this->set_mass(m);				// calculating mass of system
	Vectorld2d baric = baricenter(); //calculates coordinates of baricenter of system
	for (auto& a : planets) {			   //changes coordinates of planets according to baricenter
		a->set_coords(Vectorld2d(a->get_coords().x - baric.x, a->get_coords().y - baric.y));
	}
	for (const auto& a : planets) {
		if (a->get_type() == CosmicBodyType::STAR)
		{
			this->name = a->get_name();
			return;
		}
		if (a->get_type() == CosmicBodyType::PLANET)
			this->name += a->get_name();		
	}
	this->name += " system";
}

	//////////////////////////////////////////////////////////////////
	///////////////// INTERFACE: GETTERS AND SETTERS /////////////////
	//////////////////////////////////////////////////////////////////

std::string PlanetSystem::get_name() {	return this->name; }
std::vector<CosmicBody*> PlanetSystem::get_planets() const { return planets; }

SolarSystem* PlanetSystem::get_system() const { return this->system; }

void PlanetSystem::set_system(SolarSystem* system) {
	for (const auto a : system->get_systems())
		if (a == this) {
			this->system = system;
			return;
		}
	return;
}

std::string PlanetSystem::get_name() const {
	std::string result = "";
	for (const auto& a : planets) {
		result += a->get_name() + " ";
	}
	return result;
}

Vectorld2d PlanetSystem::get_global_coords() const { return global_coords; }
void PlanetSystem::set_global_coords(Vectorld2d c) { global_coords = c; }

	//////////////////////////////////////////////////////////////////
	///////////////////// PHYSICAL INTERACTIONS //////////////////////
	//////////////////////////////////////////////////////////////////

void PlanetSystem::simulate(float astep) {
	for (int i = 0; i < planets.size(); i++) {
		for (int j = i + 1; j < planets.size(); j++) {
			planets[i]->grav_pull(planets[j]);
		}
	}
	for (const auto& a : planets) {					//for each planet in planetary system		
		a->update_speed(astep);								//updating speed according to calculated acceleration and given time-step
		a->move(astep);										//moving planet according to calculated speed and given time-step
	}
	Vectorld2d baric = baricenter();	//calculating new position of baricenter
	for (auto& a : planets) {				//changing each planet's coordinates according to new baricenter
		a->set_coords(Vectorld2d(a->get_coords().x - baric.x, a->get_coords().y - baric.y)); //local coordinates change, as baricenter (0,0) moves
		a->set_global_coords(Vectorld2d(this->global_coords.x + a->get_coords().x, this->global_coords.y + a->get_coords().y));
		//global coordinates change as well, because (0,0) represents material point,
		//which interacts with other planetary systems and is the ccenter of masses
	}
}

//////////////////////////////////////////////////////////////////
//////////////////////// UTILITY FUNCTIONS ///////////////////////
//////////////////////////////////////////////////////////////////

std::vector<PlanetSystem*> interaction_list(const PlanetSystem& p, std::vector<PlanetSystem*> planets) {
	std::vector<PlanetSystem*> result;
	for (const auto& a : planets) {
		if (*a != p)
			result.push_back(a);
	}
	return result;
}

Vectorld2d PlanetSystem::baricenter()
{
	Vectorld2d result;
	for (const auto& a : planets) {
		result.x += a->get_mass() * a->get_coords().x / get_mass();
		result.y += a->get_mass() * a->get_coords().y / get_mass();
	}
	return result;
}

void PlanetSystem::resize_shapes(float s) {
	for (const auto& a : planets)
		a->resize_shape(s);
}

void PlanetSystem::draw(sf::RenderWindow &w) {
	for (const auto& a : planets)
		a->draw(w);
}

	//////////////////////////////////////////////////////////////////
	///////////////// COMPARISON OPERATORS OVERLOAD //////////////////
	//////////////////////////////////////////////////////////////////

bool operator==(const PlanetSystem& ps1, const PlanetSystem& ps2) {
	if (ps1.get_planets() == ps2.get_planets())
		return true;
	return false;
}

bool operator!=(const PlanetSystem& ps1, const PlanetSystem& ps2)
{
	if (ps1.get_planets() != ps2.get_planets())
		return true;
	return false;
}