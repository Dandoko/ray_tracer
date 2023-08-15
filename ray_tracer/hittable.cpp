#include "hittable.h"

// Precondition: outward_normal must have unit length
void HitRecord::set_face_normal(const Ray& r, const Vec3& outward_normal) {
	is_front_face = dot(r.direction(), outward_normal) < 0;
	normal = is_front_face ? outward_normal : -outward_normal;
}