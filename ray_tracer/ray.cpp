#include "ray.h"

Ray::Ray() {}

Ray::Ray(const Point3& origin, const Vec3& direction, double time = 0.0) : org(origin), dir(direction), tm(time) {}

Point3 Ray::origin() const {
	return org;
}

Vec3 Ray::direction() const {
	return dir;
}

double Ray::time() const {
	return tm;
}

Point3 Ray::at(double t) const {
	return org + t * dir;
}