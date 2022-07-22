#include "Volume.h"
#include <iostream>
Volume::Volume() {};
Volume::Volume(Vectorld2d c, long double s) {
	coordinates = c;
	size = s;
}

Vectorld2d Volume::get_coordinates() const { return coordinates; }
void Volume::set_coordinates(Vectorld2d c) { coordinates = c; }

long double Volume::get_size() const { return size; }

bool Volume::isPointInVolume(Vectorld2d p) {
	bool isXIn = p.x >= coordinates.x - size && p.x <= coordinates.x + size;
	bool isYIn = p.y >= coordinates.y - size && p.y <= coordinates.y + size;
	return isXIn && isYIn;
}

