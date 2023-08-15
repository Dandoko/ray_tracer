#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class Sphere : public Hittable {
public:
	Sphere(Point3 centre, double r);
	virtual bool hit(const Ray& r, Interval t_interval, HitRecord& rec) const override;

private:
	Point3 centre;
	double radius;
};

#endif