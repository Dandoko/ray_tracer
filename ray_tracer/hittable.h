#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class Material;

struct HitRecord {
	Point3 p;					// Point of intersection between the ray and the hittable object
	Vec3 normal;				// The normal vector of the point of intersection that points outwards from the hittable object
	double t;					// The position on the ray that intersected with the hittable object
};

class Hittable {
public:
	// Hits only count if t_min < t < t_max 
	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

#endif