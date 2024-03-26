#include "quad.h"

#include "aabb.h"

Quad::Quad(const Point3& origin, const Vec3& u, const Vec3& v, std::shared_ptr<Material> mat)
	: my_origin(origin), my_u(u), my_v(v), my_mat(mat)
{
	// Solving for the equation of the plane that contains the quad
	Vec3 n = cross(my_u, my_v);
	my_normal = unit_vector(n);
	my_d = dot(my_normal, origin);

	// Calculating UV constant
	my_w = n / dot(n, n);

	// Setting the bounding box of the quad
	set_bounding_box();
}

AABB
Quad::bounding_box() const
{
	return my_b_box;
}

// Plane-ray intersection algorithm
bool
Quad::hit(const Ray& r, Interval t_interval, HitRecord& rec) const
{
	double denom = dot(my_normal, r.direction());

	// No hit if ray is parallel to plane
	if (1e-8 > fabs(denom))
	{
		return false;
	}

	// No hit if hit point parameer t is outside of ray interval
	double t = (my_d - dot(my_normal, r.origin())) / denom;
	if (!t_interval.contains(t))
	{
		return false;
	}

	// UV bounds testing
	Point3 intersection = r.at(t);
	Vec3 origin_to_hitpoint = intersection - my_origin;
	double alpha = dot(my_w, cross(origin_to_hitpoint, my_v));
	double beta = dot(my_w, cross(my_u, origin_to_hitpoint));
	if (!is_interior(alpha, beta, rec))
	{
		return false;
	}

	// Setting rest of HitRecord
	rec.t = t;
	rec.p = intersection;
	rec.mat = my_mat;
	rec.set_face_normal(r, my_normal);

	return true;
}

void
Quad::set_bounding_box()
{
	my_b_box = AABB(my_origin, my_origin + my_u + my_v).pad();
}

bool
Quad::is_interior(double a, double b, HitRecord& rec) const
{
	// Returns false if hit point in planar coordinates is outside primitive
	if (0 > a || 1 < a || 0 > b || 1 < b) {
		return false;
	}

	// Set HitRecord uv coordinates and return true;
	rec.u = a;
	rec.v = b;

	return true;
}