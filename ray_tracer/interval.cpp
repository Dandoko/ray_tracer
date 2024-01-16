#include "interval.h"

Interval::Interval() : min(INF), max(-INF) {};

Interval::Interval(double iMin, double iMax) : min(iMin), max(iMax) {}

Interval::Interval(const Interval& a, const Interval& b) : min(fmin(a.min, b.min)), max(fmax(a.max, b.max)) {};

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

double Interval::size() const {
	return max - min;
}

Interval Interval::expand(double delta) const {
	double padding = delta / 2;
	return Interval(min - padding, max + padding);
}