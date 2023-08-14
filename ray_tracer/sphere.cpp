#include "sphere.h"

Sphere::Sphere(Point3 centre, double r) : centre(centre), radius(r) {}

bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
	// Using a simplified quadratic equation
	Vec3 sphere_centre_to_ray_origin = r.origin() - centre;
    double a = r.direction().length_squared();
    double half_b = dot(sphere_centre_to_ray_origin, r.direction());
    double c = sphere_centre_to_ray_origin.length_squared() - radius * radius;

	double discriminant = half_b * half_b - a * c;

	// No solutions (i.e. no hit)
	if (0 > discriminant) {
		return false;
	}

	// Finding the nearest root that lies in the acceptable range
	double sqrt_discriminant = sqrt(discriminant);
	double root = (-half_b - sqrt_discriminant) / a;
	if (root < t_min || root >= t_max) {
		root = (-half_b + sqrt_discriminant) / a;
		if (root < t_min || root >= t_max) {
			return false;
		}
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	rec.normal = (rec.p - centre) / radius;	// Does the same thing as unit_vector(rec.p - centre) but
											// we need to divide by the radius instead for inverted spheres
	
	return true;
}