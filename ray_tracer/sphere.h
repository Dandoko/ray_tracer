#ifndef SPHERE_H
#define SPHERE_H

#include "aabb.h"
#include "hittable.h"

class Sphere : public Hittable {
public:
	Sphere(Point3 in_centre_start, double r, std::shared_ptr<Material> material);						// Stationary
	Sphere(Point3 in_centre_start, Point3 centre_end, double r, std::shared_ptr<Material> material);	// Moving
	
	virtual bool hit(const Ray& r, Interval t_interval, HitRecord& rec) const override;
	virtual AABB bounding_box() const override;

private:
	Point3 centre_start;
	double radius;
	std::shared_ptr<Material> mat;
	bool is_moving;
	Vec3 centre_disp_vec;
	AABB b_box;

	Point3 calculate_current_centre(double time) const; // Gets the position of the sphere at the specified ray time
};

#endif