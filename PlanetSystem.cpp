#include "PlanetSystem.h"

PlanetSystem::PlanetSystem(std::vector<Planet*> ps, long double ax, long double ay, Vectorld2d sp) {
	planets = ps;
	x = ax;
	y = ay;
	long double max_distance = 0;
	if (planets.size() != 0) {
		if (planets.size() != 1) {
			for (const auto& p : interaction_list(*planets[0], planets)) {
				if (distance(*planets[0], *p) > max_distance)
					max_distance = distance(*planets[0], *p);
			}
		}
		else {
			max_distance = ps[0]->get_diameter() * 1.5;
		}
		bounding_volume = Volume(Vectorld2d(x, y), max_distance);
		std::vector<long double> baric = baricenter();
		for (auto& a : planets) {
			a->set_x(a->get_x() - baric[0]);
			a->set_y(a->get_y() - baric[1]);
		}
	}	
	sspeed = sp;
	acceleration = Vectorld2d();
}

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

const long double distance(const PlanetSystem& ps1, const PlanetSystem& ps2)
{
	return sqrt(pow(ps2.x - ps1.x, 2) + pow(ps2.y - ps1.y, 2));
}

std::vector<Planet*> PlanetSystem::get_planets() const { return planets; }

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

long double PlanetSystem::get_x() const { return x; }
void PlanetSystem::set_x(long double ax) { x = ax;  }
long double PlanetSystem::get_y() const { return y; }

void PlanetSystem::set_y(long double ay) { y = ay; }

Vectorld2d PlanetSystem::get_speed() const { return sspeed; }

void PlanetSystem::set_speed(Vectorld2d sp) { sspeed = sp; }

void PlanetSystem::update_speed(int astep) {
	Vectorld2d temp = acceleration * astep;
	Vectorld2d temp1 = sspeed + temp;
	sspeed = temp1; 
}

Vectorld2d PlanetSystem::get_acceleration() { return acceleration; }
void PlanetSystem::set_acceleration(Vectorld2d acc) { acceleration = acc; }

void PlanetSystem::add_planet(Planet* p)
{
	planets.push_back(p);
	p->set_x(x + p->get_x());
	p->set_y(y + p->get_y());
	long double max_distance = 0;
	if (planets.size() != 1) {
		for (const auto& p : interaction_list(*planets[0], planets)) {
			if (distance(*planets[0], *p) > max_distance)
				max_distance = distance(*planets[0], *p);
		}
	}
	else {
		max_distance = planets[0]->get_diameter() * 1.5;
	}
	bounding_volume = Volume(Vectorld2d(x, y), max_distance);
	/*std::vector<long double> baric = baricenter();
	for (auto& a : planets) {
		a->set_x(a->get_x() - baric[0]);
		a->set_y(a->get_y() - baric[1]);
	}*/
}

void PlanetSystem::move(int astep) {
	x = x + sspeed[0] * astep;
	//shape.setPosition(x / 1000000000 + 640, y / 1000000000 + 360);
	y = y + sspeed[1] * astep;
	bounding_volume = Volume(Vectorld2d(x, y), bounding_volume.get_size());
	
}

std::vector<long double> PlanetSystem::baricenter()
{
	std::vector<long double> result {0, 0};
	for (const auto& a : planets) {
		result[0] += a->get_mass() * a->get_x() / get_mass();
		result[1] += a->get_mass() * a->get_y() / get_mass();
	}
	return result;
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
		f[0] += fx;
		f[1] += fy;		
	}
	return f;
}

void grav_pull(PlanetSystem& ps, std::vector<PlanetSystem*> psystems) {
	Vectorld2d f = grav_force(ps, psystems);
	ps.set_acceleration (f * (1e0 / ps.get_mass()));
}

void PlanetSystem::simulate(int astep) {
	for (const auto& a : planets) { //for each planet in planetary system
		//std::cout << b->get_name() << " x=" << b->get_x() << " y=" << b->get_y() << "\n";
		grav_pull(*a, interaction_list(*a, planets));
		a->update_speed(astep);
		a->move(astep);
	}
	std::vector<long double> baric = baricenter(); //calculating baricenter
	for (auto& a : planets) {			   //moving each planetaccording to baricenter
		a->set_x(a->get_x() - baric[0]);
		a->set_y(a->get_y() - baric[1]);
	}
}

bool PlanetSystem::is_clicked(sf::Vector2f pointer)
{
	return bounding_volume.isPointInVolume(Vectorld2d(pointer.x, pointer.y));
}

void PlanetSystem::resize_shapes(float s) {
	for (const auto& a : planets)
		a->resize_shape(s);
}

std::vector<PlanetSystem*> interaction_list(const PlanetSystem& p, std::vector<PlanetSystem*> planets) {
	std::vector<PlanetSystem*> result;
	for (const auto& a : planets) {
		if (*a != p)
			result.push_back(a);
	}
	return result;
}

void PlanetSystem::draw_system(sf::RenderWindow &w) {
	for (const auto& a : planets)
		a->draw_planet(w, x, y); //x and y are coordinates of planetary system's 0,0 in solar system's coordinates
		//a->draw_planet(w);
}

void PlanetSystem::draw_system(sf::RenderWindow& w, long double ax, long double ay) {
	for (const auto& a : planets)
		a->draw_planet(w, ax + x, ay + y);
}
