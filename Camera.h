#ifndef CAMERA
#define CAMERA
#include <SFML/Graphics.hpp>
#include "Vectorld2d.h"

class Camera
{
public:
	float default_world_display_scale;  // default world display scale
	float world_display_scale; //current world display scale
	sf::View world_view; //world camera view
	sf::View ui_view; //interface view
	sf::Vector2i input_offset;  // offset from user input
	Vectorld2d world_offset;  // offset from world, used in case of focusing on some object

	// default constructor
	Camera();
	// constructor, takes in window resolution
	Camera(sf::Vector2f resolution);

	void set_input_offset(sf::Vector2i offset);
	void set_world_offset(Vectorld2d offset);
	void reset_offsets();
	
	//resizes after change of size of window
	void resize(float newWidth, float newHeight);
	// moves camera by both input and world offsets
	void move();
	// moves camera to given coordinates
	void move_to(sf::Vector2f coords);
	//camera move by old position of pointer and new one
	void move(sf::Vector2i old_pos, sf::Vector2i new_pos);
	// camera move by required camera offset given in float values for offset given in world coordinates
	void move_by_world_offset();
	// camera move by given by camera offset given in int values, mostly for offset of mouse movement given in in-window coordinates
	void move_by_input_offset();

	// zooms in world view
	void zoom();
	// zooms out world view
	void zoom_out();
};

#endif