#include "sphere.h"

Sphere::Sphere(Point3 centre, double r, std::shared_ptr<Material> material) : centre(centre), radius(r), mat(material) {}

bool Sphere::hit(const Ray& r, Interval t_interval, HitRecord& rec) const {
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

	// Finding the closest root to the camera that lies in the acceptable range
	double sqrt_discriminant = sqrt(discriminant);
	double root = (-half_b - sqrt_discriminant) / a;
	if (!t_interval.surrounds(root)) {
		root = (-half_b + sqrt_discriminant) / a;
		if (!t_interval.surrounds(root)) {
			return false;
		}
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	Vec3 outward_normal = (rec.p - centre) / radius;	// Does the same thing as unit_vector(rec.p - centre) but
														// we need to divide by the radius for inverted spheres
	rec.set_face_normal(r, outward_normal);
	rec.mat = mat;
	
	return true;
}