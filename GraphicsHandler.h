#ifndef GRAPHICS_HANDLER
#define GRAPHICS_HANDLER
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "ShapesManager.h"

class GraphicsHandler
{
	ShapesManager shpmgr;
public:
	// default constructor
	GraphicsHandler();
	// returns reference to shapes manager
	ShapesManager& get_shapes_manager();
};

#endif