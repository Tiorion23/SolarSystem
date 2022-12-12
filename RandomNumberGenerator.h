#ifndef RNG
#define RNG
#include <cstdlib> // rand() è srand()
#include <ctime> // time()
#include "Engine.h"

// singleton, handles random number generation
class RandomNumberGenerator {
	RandomNumberGenerator();
	static RandomNumberGenerator* instance;
public:
	// returns pointer to this class' only instance, creates one, if there's none
	static RandomNumberGenerator* get_instance();
	// generates random int number between min and max
	int get_random_number(int min, int max);
	// generates random double number between min and max
	double get_random_number(double min, double max);
	// generates random long double number between min and max
	long double get_random_number(long double min, long double max);
};


#endif
