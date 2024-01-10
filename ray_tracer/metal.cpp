#include "metal.h"
#include "vec3.h"

Metal::Metal(const Color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

bool Metal::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
	Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
	scattered = Ray(rec.p, reflected + fuzz * random_unit_vector(), r_in.time());
	attenuation = albedo;
	return dot(scattered.direction(), rec.normal) > 0;
}