#ifndef AABB_H
#define AABB_H

#include "interval.h"
#include "ray.h"
#include "vec3.h"

class AABB {
public:
	Interval x, y, z; // Intervals for the x, y, z components

	AABB();
	AABB(const Interval& iX, const Interval& iY, const Interval& iZ);
	AABB(const Point3& a, const Point3& b); // a and b are bounding box points
	AABB(const AABB& box0, const AABB& box1);

	AABB pad() const;

	const Interval& axis(int i) const;

	bool hit(const Ray& r, Interval t) const;
};

#endif