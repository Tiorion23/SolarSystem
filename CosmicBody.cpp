#include "CosmicBody.h"

std::string cosmic_body_type_to_str(CosmicBodyType type) {
	switch (type) {
	default:
	case CosmicBodyType::STAR: return "star";
	case CosmicBodyType::PLANET: return "planet";
	case CosmicBodyType::SATELLITE: return "satellite";
	}
}

CosmicBody::CosmicBody(CosmicBodyType type, std::string name, long double diam, long double m, Vectorld2d coords, Vectorld2d sp, sf::CircleShape* shp): 
	MaterialPoint(coords, m, sp), name(name) {
	this->type = type;
	diameter = diam;
	global_coords = coords;
	phi = (pow(sqrt(pow(coords.x,2)+pow(coords.y,2)), 2) + pow(sqrt(pow(coords.x, 2) + pow(coords.y, 2)), 2) - pow(sqrt(pow(sp[0], 2) + pow(sp[1], 2)), 2)) / (2 * sqrt(pow(coords.x, 2) + pow(coords.y, 2)) * sqrt(pow(coords.x, 2) + pow(coords.y, 2)));
	shape = shp;
	shape->setPosition(global_coords.x , global_coords.y);
}

	//////////////////////////////////////////////////////////////////
	///////////////// INTERFACE: GETTERS AND SETTERS /////////////////
	//////////////////////////////////////////////////////////////////
PlanetSystem* CosmicBody::get_system() const { return system; }
void CosmicBody::set_system(PlanetSystem* system) { this->system = system; }
CosmicBodyType CosmicBody::get_type() const { return type; }
std::string CosmicBody::get_name() const { return name; }
long double CosmicBody::get_diameter() const { return diameter; }
Vectorld2d CosmicBody::get_global_coords() const { return global_coords; }
void CosmicBody::set_global_coords(Vectorld2d c) { global_coords = c; }

	//////////////////////////////////////////////////////////////////
	//////////////////////// UTILITY FUNCTIONS ///////////////////////
	//////////////////////////////////////////////////////////////////
	// includes friend function that returns vector of bodies without given body
	// draw and other graphic related functions

void CosmicBody::resize_shape(float s) {
	shape->scale(s, s);
}

void CosmicBody::draw(sf::RenderWindow& w) {
	shape->setPosition(global_coords.x, global_coords.y);
	w.draw(*shape);
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