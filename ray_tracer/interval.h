#ifndef INTERVAL_H
#define INTERVAL_H

#include "utility.h"

class Interval {
public:
	double min;
	double max;

	Interval();
	Interval(double iMin, double iMax);
	Interval(const Interval& a, const Interval& b); // Creates a new interval that is the union of both intervals

	bool contains(double x);
	bool surrounds(double x);

	double clamp(double x) const;

	double size() const;
	Interval expand(double delta) const; // Adds a little padding to the interval if the interval is NaN
};

#endif