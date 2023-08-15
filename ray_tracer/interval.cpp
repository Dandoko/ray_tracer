#include "interval.h"

Interval::Interval() : min(INF), max(-INF) {};

Interval::Interval(double iMin, double iMax) : min(iMin), max(iMax) {}

bool Interval::contains(double x) {
	return min <= x && x <= max;
}

bool Interval::surrounds(double x) {
	return min < x && x < max;
}