#include "PlanetSystem.h"

PlanetSystem::PlanetSystem(std::vector<CosmicBody*> ps, long double ax, long double ay, Vectorld2d sp) {
	coords = Vectorld2d(ax, ay);
	global_coords = coords;
	planets = ps;							// vector of planets planetary system consists of
	long double max_distance = 0;	
	if (planets.size() > 1) { //if number of planets in system >1 calculates most distant planet in system
		for (const auto& p : interaction_list(*planets[0], planets)) {
			if (distance(*planets[0], *p) > max_distance)
				max_distance = distance(*planets[0], *p);
		}
	}
	else if (planets.size() == 1) { // if theres only one planet in system sets max distance as 1.5 of planets radius
		max_distance = ps[0]->get_diameter() * 0.75; 
	}
	bounding_volume = Volume(global_coords, max_distance); // defines bounding volume of planetary system by calculated distance
	/*std::cout << this->get_name() << " x = " << global_x << " y = " << global_y << "\n";
	std::cout << this->get_name() << " bvx = " << bounding_volume.get_coordinates().x << " bvy = " << bounding_volume.get_coordinates().y << " bvsize " << bounding_volume.get_size() << "\n";*/
	Vectorld2d baric = baricenter(); //calculates coordinates of baricenter of system
	for (auto& a : planets) {			   //changes coordinates of planets according to baricenter
		a->set_x(a->get_x() - baric.x);
		a->set_y(a->get_y() - baric.y);
	}
	sspeed = sp;
	acceleration = Vectorld2d();
}

	//////////////////////////////////////////////////////////////////
	///////////////// INTERFACE: GETTERS AND SETTERS /////////////////
	//////////////////////////////////////////////////////////////////

std::vector<CosmicBody*> PlanetSystem::get_planets() const { return planets; }

std::string PlanetSystem::get_name() const {
	std::string result = "";
	for (const auto& a : planets) {
		result += a->get_name() + " ";
	}
	return result;
}

long double PlanetSystem::get_mass() const {
	long double m = 0;
	for (const auto& a : planets) {
		m += a->get_mass();
	}
	return m;
}

long double PlanetSystem::get_x() const { return coords.x; }
void PlanetSystem::set_x(long double ax) { coords.x = ax; }
long double PlanetSystem::get_y() const { return coords.y; }
void PlanetSystem::set_y(long double ay) { coords.y = ay; }

long double PlanetSystem::get_global_x() { return global_coords.x; }
void PlanetSystem::set_global_x(long double arg) { global_coords.x = arg; }
long double PlanetSystem::get_global_y() { return global_coords.y; }
void PlanetSystem::set_global_y(long double arg) { global_coords.y = arg; }

Vectorld2d PlanetSystem::get_coords() { return coords; }
void PlanetSystem::set_coords(Vectorld2d c) { coords = c; }
Vectorld2d PlanetSystem::get_global_coords() { return global_coords; }
void PlanetSystem::set_global_coords(Vectorld2d c) { global_coords = c; }

Vectorld2d PlanetSystem::get_speed() const { return sspeed; }
void PlanetSystem::set_speed(Vectorld2d sp) { sspeed = sp; }

Vectorld2d PlanetSystem::get_acceleration() { return acceleration; }
void PlanetSystem::set_acceleration(Vectorld2d acc) { acceleration = acc; }

	//////////////////////////////////////////////////////////////////
	///////////////////// PHYSICAL INTERACTIONS //////////////////////
	//////////////////////////////////////////////////////////////////

const long double distance(const PlanetSystem& ps1, const PlanetSystem& ps2)
{
	return sqrt(pow(ps2.coords.x - ps1.coords.x, 2) + pow(ps2.coords.y - ps1.coords.y, 2));
}

Vectorld2d grav_force(const PlanetSystem& ps, std::vector<PlanetSystem*> psystems) {
	Vectorld2d f = Vectorld2d(0, 0);
	if (psystems.size() == 0)
		return f;
	for (int i = 0; i < psystems.size(); i++) {
		long double fl = 0;  //variable for Force vector length
		if (distance(ps, *psystems[i]) != 0)
			fl = (G * ps.get_mass() * psystems[i]->get_mass()) / pow(distance(ps, *psystems[i]), 2);
		else
			fl = 0;
		long double cosa = fabs(psystems[i]->get_x() - ps.get_x()) / distance(ps, *psystems[i]);
		long double alpha = acos(fabs(psystems[i]->get_x() - ps.get_x()) / distance(ps, *psystems[i]));
		//long double alpha = acos((psystems[i]->get_x() - ps.get_x()) / distance(ps, *psystems[i]));
		//fx = (fl * cos(alpha)); //WHY??? THIS DOESNT WORK??? if i remove fabs in alpha
		//fy = (fl * sin(alpha));
		long double fx = 0, fy = 0;
		if (psystems[i]->get_x() < ps.get_x())
			fx = (-fl * cos(alpha));
		else
			fx = (fl * cos(alpha));
		if (psystems[i]->get_y() < ps.get_y())
			fy = (-fl * sin(alpha));
		else
			fy = (fl * sin(alpha));
		f.x += fx;
		f.y += fy;
	}
	return f;
}

void grav_pull(PlanetSystem& ps, std::vector<PlanetSystem*> psystems) {
	Vectorld2d f = grav_force(ps, psystems);
	ps.set_acceleration(f * (1e0 / ps.get_mass()));
}

void PlanetSystem::update_speed(int astep) {
	sspeed = sspeed + acceleration * astep;
}

void PlanetSystem::move(int astep) {
	coords = coords + (sspeed * astep);
}

void PlanetSystem::simulate(int astep) {
	for (const auto& a : planets) { //for each planet in planetary system
		grav_pull(*a, interaction_list(*a, planets)); //calculating summary acceleration from all other planets
		a->update_speed(astep);								//updating speed according to calculated acceleration and given time-step
		a->move(astep);										//moving planet according to calculated speed and given time-step
	}
	Vectorld2d baric = baricenter();	//calculating new position of baricenter
	for (auto& a : planets) {				//changing each planet's coordinates according to new baricenter
		a->set_x(a->get_x() - baric.x);			//local coordinates change, as (0,0) moves
		a->set_y(a->get_y() - baric.y);
		a->set_global_x(this->get_global_x() + a->get_x());	//global coordinates change as well, because (0,0) represents material point,
		a->set_global_y(this->get_global_y() + a->get_y());	//which interacts with other planetary systems and is the ccenter of masses
		a->update_bounding_volume();
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
		result.x += a->get_mass() * a->get_x() / get_mass();
		result.y += a->get_mass() * a->get_y() / get_mass();
	}
	return result;
}

void PlanetSystem::update_bounding_volume() {
	bounding_volume.set_coordinates(global_coords);
}

bool PlanetSystem::is_clicked(sf::Vector2f pointer)
{
	return bounding_volume.isPointInVolume(Vectorld2d(pointer.x, pointer.y));
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