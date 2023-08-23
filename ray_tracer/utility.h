#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Constants
const double INF = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;
const double REFRACTION_INDEX_AIR = 1.0;

// Utility functions
double degrees_to_radians(double degrees);
double random_double();							// Returns a random real number in [0, 1)
double random_double(double min, double max);	// Returns a random real number in [min, max)

#endif