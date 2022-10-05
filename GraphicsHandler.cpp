#include "GraphicsHandler.h"

GraphicsHandler::GraphicsHandler() {
	shpmgr = ShapesManager();
}

ShapesManager& GraphicsHandler::get_shapes_manager() {
	return this->shpmgr;
}
