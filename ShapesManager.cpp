#include "ShapesManager.h"

ShapesManager::ShapesManager() {}

void ShapesManager::add_shape(const std::string& name, float radius, sf::Color color) {
	this->shapes[name] = sf::CircleShape(radius);
	this->shapes[name].setFillColor(color);
	this->shapes[name].setOrigin(this->shapes[name].getRadius(), this->shapes[name].getRadius());
}

bool ShapesManager::is_shape_available(const std::string& shape) {
	if (this->shapes.count(shape) != 0)
		return true;
	return false;
}

sf::CircleShape& ShapesManager::get_shape(const std::string& shape) {
	if (this->is_shape_available(shape))
		return this->shapes.at(shape);
}