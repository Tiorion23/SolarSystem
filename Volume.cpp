#include "Volume.h"
Volume::Volume() {};
Volume::Volume(Vectorld2d c, long double s) {
	coordinates = c;
	size = s;
}

Vectorld2d Volume::get_coordinates() { 	return coordinates; }

long double Volume::get_size() { return size; }

bool Volume::isPointInVolume(Vectorld2d p) {
	bool isXIn = p.x <= coordinates.x - size && p.x >= coordinates.x + size;
	bool isYIn = p.y <= coordinates.y - size && p.y >= coordinates.y + size;
	return isXIn && isYIn;
}

