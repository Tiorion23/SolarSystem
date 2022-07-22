#pragma once
#include "Vectorld2d.h"
class Volume
{
	Vectorld2d coordinates; //coordinates of center of volume
	long double size;		//half-size of side of volume, assuming it is sqare
public:
	//default constructor
	Volume();
	//constructor from coordinates c and side size s
	Volume(Vectorld2d c, long double s);
	//returns coordinates of center of volume
	Vectorld2d get_coordinates() const;
	//sets coordinates of volume
	void set_coordinates(Vectorld2d c);
	//returns half-size of side of volume
	long double get_size() const;
	//returns true, if point with coordinates p is in this volume
	bool isPointInVolume(Vectorld2d p);
};

