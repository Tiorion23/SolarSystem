#include "ShapesManager.h"

ShapesManager::ShapesManager() {}

void ShapesManager::add_shape(std::string& name, float radius, sf::Color color) {
	this->shapes[name] = sf::CircleShape(radius);
	this->shapes[name].setFillColor(color);
	this->shapes[name].setOrigin(this->shapes[name].getRadius(), this->shapes[name].getRadius());
}

sf::CircleShape& ShapesManager::get_shape(const std::string& shape) {
	return this->shapes.at(shape);
}