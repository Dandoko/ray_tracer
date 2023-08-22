#include "metal.h"
#include "vec3.h"

Metal::Metal(const Color& a) : albedo(a) {}

bool Metal::scatter(const Ray& r_in, const HitRecord& record, Color& attenuation, Ray& scattered) const {
	Vec3 reflected = reflect(unit_vector(r_in.direction()), record.normal);
	scattered = Ray(record.p, reflected);
	attenuation = albedo;
	return true;
}