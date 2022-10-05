#ifndef CAMERA
#define CAMERA
#include <SFML/Graphics.hpp>

class Camera
{
	int xRes; //resolution x size
	int yRes; // resoultion y size
	float default_scale;  // default display scale
	float scale; //current display scale
	const sf::View startingView; //starting camera view, used for getting back to default camera state
	sf::View view; //current camera view
	sf::View ui_view; //interface view

public:
	// default constructor
	Camera();
	// constructor, takes in starting point and window resolution
	Camera(sf::Vector2f startCoords, sf::Vector2f resolution);

	//getter for current view
	sf::View getView() const;
	//getter for UI view
	sf::View getUIView() const;
	//getter for starting view
	sf::View getStartingView() const;
	//getter for current scale
	float get_scale();

	//setter for view by new view
	void setView(sf::View newView);
	//setter for view by center and size
	void setView(sf::Vector2f center, sf::Vector2f size);
	//resizes after change of size of window
	void resize(int newWidth, int newHeight);
	//camera move
	void move(sf::Vector2i oldPosition, sf::Vector2i newPosition);
	//resets camera to default 
	void reset();
	//changes camera scale
	void rescale(float s);
};

#endif