#ifndef QUAD_H
#define QUAD_H

#include "hittable.h"
#include "material.h"
#include "utility.h"

class Quad : public Hittable {
public:
	Quad(const Point3& origin, const Vec3& u, const Vec3& v, std::shared_ptr<Material> mat);

	virtual AABB bounding_box() const override;
	virtual bool hit(const Ray& r, Interval t_interval, HitRecord& rec) const override;
	
	void set_bounding_box();

private:
	bool is_interior(double a, double b, HitRecord& rec) const;

	Point3 my_origin;	// Lower left corner of the Quad
	Vec3 my_u;			// Side vector from origin towards lower right corner
	Vec3 my_v;			// Side vector from origin towards upper left corner

	std::shared_ptr<Material> my_mat;
	AABB my_b_box;
	
	Vec3 my_normal;
	double my_d;		// The constant value in the plane equation: Ax + By + Cz = D
	Vec3 my_w;			// Constant used to calculate intersection point in UV coordinate
};

#endif