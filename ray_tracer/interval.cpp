#include "interval.h"

Interval::Interval() : min(INF), max(-INF) {};

Interval::Interval(double iMin, double iMax) : min(iMin), max(iMax) {}

bool Interval::contains(double x) {
	return min <= x && x <= max;
}

bool Interval::surrounds(double x) {
	return min < x && x < max;
}

double Interval::clamp(double x) const {
	if (x < min) {
		return min;
	}
	else if (x > max) {
		return max;
	}
	else {
		return x;
	}
}