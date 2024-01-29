#include "solid_color.h"

SolidColor::SolidColor(Color c) : my_color(c) {}

SolidColor::SolidColor(double r, double g, double b) : my_color(r, g, b) {}

Color SolidColor::value(double u, double v, const Point3& p) const {
	return my_color;
}