#ifndef SHAPES_MANAGER
#define SHAPES_MANAGER
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class ShapesManager
{
	std::map<std::string, sf::CircleShape> shapes;
public:
	ShapesManager();
	void add_shape(const std::string& name, float radius, sf::Color color);
	sf::CircleShape& get_shape(const std::string& shape);
};

#endif