#include "DynamicUi.h"

DynamicUi::DynamicUi(int padding, UiStyle& style, std::pair<std::string, std::string> entry)
{
	visible = false;
	this->style = style;
	//this->dimensions = dimensions;
	this->padding = padding;
	// Construct the background shape
	sf::RectangleShape shape;
	//shape.setSize(dimensions);
	shape.setFillColor(style.bodyCol);
	shape.setOutlineThickness(-style.borderSize);
	shape.setOutlineColor(style.borderCol);
	// Construct the text
	sf::Text text;
	text.setString(entry.first);
	text.setFont(*style.font);
	text.setFillColor(style.textCol);
	text.setCharacterSize(20);
	sf::FloatRect rect = text.getGlobalBounds();
	// changing shape size to fit text size
	this->dimensions = sf::Vector2f(rect.width + (padding + style.borderSize) * 2, rect.height + (padding + style.borderSize) * 2);
	shape.setSize(dimensions);
	// construct entry
	this->entry = UiEntry(entry.second, shape, text);
}

void DynamicUi::set_position(sf::Vector2f pos) {
	this->entry.shape.setPosition(pos);
	// adding padding to text position to prevent text from starting at border
	this->entry.text.setPosition(sf::Vector2f(pos.x + padding, pos.y));
}

void DynamicUi::show() {
	this->visible = true;
}

void DynamicUi::hide() {
	this -> visible = false;
}

bool DynamicUi::isMouseOver(const sf::Vector2f mousePos) {
	if (!this->visible)
		return false;
	// Translate point to use the entry's local coordinates.
	sf::Vector2f point = mousePos;
	point += this->entry.shape.getOrigin();
	point -= this->entry.shape.getPosition();
	// if pointer is not in shape coordinates in one of the axis, going to the next shape, else returns its index
	if (point.x < 0 || point.x > this->entry.shape.getScale().x * this->dimensions.x) return false;
	if (point.y < 0 || point.y > this->entry.shape.getScale().y * this->dimensions.y) return false;
	return true;
}

void DynamicUi::highlight(const bool mouseover) {
	if (mouseover)
	{
		this->entry.shape.setFillColor(style.bodyHighlightCol);
		this->entry.shape.setOutlineColor(style.borderHighlightCol);
		this->entry.text.setFillColor(style.textHighlightCol);
	}
	else
	{
		this->entry.shape.setFillColor(style.bodyCol);
		this->entry.shape.setOutlineColor(style.borderCol);
		this->entry.text.setFillColor(style.textCol);
	}
}

std::string DynamicUi::activate(const sf::Vector2f mousePos) {
	if (isMouseOver(mousePos))
		return this->entry.message;
	return "null";
}

void DynamicUi::draw(sf::RenderWindow& w) const {
	if (!visible)
		return;
	w.draw(this->entry.shape);
	w.draw(this->entry.text);
}