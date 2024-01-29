#include "sphere.h"

Sphere::Sphere(Point3 in_centre_start, double r, std::shared_ptr<Material> material) : centre_start(in_centre_start), radius(r), mat(material), is_moving(false) {
	// centre_disp_vec has garbage value for stationary spheres

	Vec3 radius_vec = Vec3(radius, radius, radius);
	b_box = AABB(centre_start - radius_vec, centre_start + radius_vec);
}

Sphere::Sphere(Point3 in_centre_start, Point3 centre_end, double r, std::shared_ptr<Material> material) : centre_start(in_centre_start), radius(r), mat(material), is_moving(true) {
	centre_disp_vec = centre_end - centre_start;

	// Creates a bouding box around the sphere at time = 0 and time = 1
	Vec3 radius_vec = Vec3(radius, radius, radius);
	AABB start_box = AABB(centre_start - radius_vec, centre_start + radius_vec);
	AABB end_box = AABB(centre_end - radius_vec, centre_end + radius_vec);

	// Creates a bounding box that surrounds both of the bounding boxes above
	b_box = AABB(start_box, end_box);
}

bool Sphere::hit(const Ray& r, Interval t_interval, HitRecord& rec) const {
	// Using a simplified quadratic equation
	Point3 centre = is_moving ? calculate_current_centre(r.time()) : centre_start;
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
	get_sphere_uv(outward_normal, rec.u, rec.v);
	rec.set_face_normal(r, outward_normal);
	rec.mat = mat;
	
	return true;
}

AABB Sphere::bounding_box() const {
	return b_box;
}

Point3 Sphere::calculate_current_centre(double time) const {
	// Linear interpolates for time [0, 1]
	return centre_start + time * centre_disp_vec;
}

void Sphere::get_sphere_uv(const Point3& p, double u, double v) {
	double theta = acos(-p.y());
	double phi = atan2(-p.z(), p.x()) + PI;

	u = phi / (2 * PI);
	v = theta / PI;
}