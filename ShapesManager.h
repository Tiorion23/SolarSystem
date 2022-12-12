#ifndef SHAPES_MANAGER
#define SHAPES_MANAGER
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
// class that contains all shapes used bu simulation
class ShapesManager
{
	std::map<std::string, sf::CircleShape> shapes;
public:
	// default constructor
	ShapesManager();
	// adding shape of set color radius and name
	void add_shape(const std::string& name, float radius, sf::Color color);
	// checks if there is shape in manager with given name
	bool is_shape_available(const std::string& shape);
	// returns reference to shape by given name
	sf::CircleShape& get_shape(const std::string& shape);
};

#endif