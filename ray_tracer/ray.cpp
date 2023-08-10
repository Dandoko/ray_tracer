#include "ray.h"

Ray::Ray() {}

Ray::Ray(const Point3& origin, const Vec3& direction) : org(origin), dir(direction) {}

Point3 Ray::origin() const {
	return org;
}

Vec3 Ray::direction() const {
	return dir;
}

Point3 Ray::at(double t) const {
	return org + t * dir;
}