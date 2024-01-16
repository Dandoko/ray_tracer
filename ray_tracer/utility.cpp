#include "utility.h"

double degrees_to_radians(double degrees) {
	return degrees * PI / 180.0;
}

double random_double() {
	return rand() / (RAND_MAX + 1.0);
}

double random_double(double min, double max) {
	return min + (max - min) * random_double();
}

int random_int(int min, int max) {
	return static_cast<int>(random_double(min, max + 1));
}