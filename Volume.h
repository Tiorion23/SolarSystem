#pragma once
#include "Vectorld2d.h"
class Volume
{
	Vectorld2d coordinates;
	long double size;
public:
	Volume();
	Volume(Vectorld2d c, long double s);
	Vectorld2d get_coordinates();
	long double get_size();
	bool isPointInVolume(Vectorld2d p);
};

