#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class Material;

struct HitRecord {
	Point3 p;					// Point of intersection between the ray and the hittable object
	Vec3 normal;				// The normal vector at the point of intersection
	double t;					// The position on the ray that intersected with the hittable object
	bool is_front_face;			// Equals true when the ray is coming from outside of the object

	// Precondition: outward_normal must have unit length
	void set_face_normal(const Ray& r, const Vec3& outward_normal);
};

class Hittable {
public:
	// Hits only count if t_min < t < t_max 
	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

#endif