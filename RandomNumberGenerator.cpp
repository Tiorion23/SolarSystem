#include "RandomNumberGenerator.h"

RandomNumberGenerator* RandomNumberGenerator::instance = nullptr;

RandomNumberGenerator::RandomNumberGenerator() {
	srand(static_cast<unsigned int>(time(0)));
}

RandomNumberGenerator* RandomNumberGenerator::get_instance() {
	if (instance == nullptr) {
		instance = new RandomNumberGenerator();
		return instance;
	}
	return instance;
}

int RandomNumberGenerator::get_random_number(int min, int max) {
	return min + (rand() % (max - min + 1));
}

double RandomNumberGenerator::get_random_number(double min, double max) {
	return min + (rand()/double(RAND_MAX) * (max - min));
}

long double RandomNumberGenerator::get_random_number(long double min, long double max) {
	return min + (rand() / long double(RAND_MAX) * (max - min));
}