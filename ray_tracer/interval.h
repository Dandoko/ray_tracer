#ifndef INTERVAL_H
#define INTERVAL_H

#include "utility.h"

class Interval {
public:
	double min;
	double max;

	Interval();
	Interval(double iMin, double iMax);

	bool contains(double x);
	bool surrounds(double x);

	double clamp(double x) const;
};

#endif