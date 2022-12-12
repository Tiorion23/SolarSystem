#ifndef UTILITY
#define UTILITY
#include "CosmicBody.h"
#include "PlanetSystem.h"
#include <string>
#include <sstream> // для stringstream
#define G 6.67e-11
#define PI atan(1) * 4
// clas for various utility functions
class utility
{
public:
	//calculate module of arg
	static long double mod(long double arg);

	//calculates length of vector
	static long double vector_length(std::vector<long double> v);

	//modify vector by number times
	static std::vector<long double> mod_vector(std::vector<long double> v, float n);

	//calculates vector sum of two vectors
	static std::vector<long double> vector_sum(std::vector<long double> v1, std::vector<long double> v2);

	//rotates vector by angle in radians
	static std::vector<long double> rotate_vector(std::vector<long double> v, long double angle);

	//timer string maker
	static std::string timer(unsigned long long int time);

	//info string, displays module of summary of gravity forces, its x- and y-components, speed of each planet in planet system
	static std::string info(const std::vector<CosmicBody*> &planets);
	//info string, displays module of summary of gravity forces, its x- and y-components, speed of each planet in planet system
	static std::string info(const PlanetSystem& ps);

	//info string, displays module of summary of gravity forces, its x- and y-components, speed of each planet in planet systems
	// overload for planet system
	static std::string info(const std::vector<PlanetSystem*>& psystems);
};

#endif