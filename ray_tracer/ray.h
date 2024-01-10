#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
public:
	Ray();
	Ray(const Point3& origin, const Vec3& direction, double time);

	Point3 origin() const;
	Vec3 direction() const;
	double time() const;

	// P(t) = A * tb = origin + t * direction
	Point3 at(double t) const;

private:
	Point3 org;
	Vec3 dir;
	double tm; // The exact time for the ray between [0, 1)
};

#endif