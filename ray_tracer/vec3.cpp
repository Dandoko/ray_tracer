#include "vec3.h"
#include "utility.h"

//=============================================================================
// Member functions
//=============================================================================

Vec3::Vec3() : components{ 0,0,0 } {}

Vec3::Vec3(double x, double y, double z) : components{ x, y, z } {}

double Vec3::x() const {
	return components[0];
}

double Vec3::y() const {
	return components[1];
}

double Vec3::z() const {
	return components[2];
}

Vec3 Vec3::operator-() const {
	return Vec3(-components[0], -components[1], -components[2]);
}

double Vec3::operator[](int i) const {
	return components[i];
}

double& Vec3::operator[](int i) {
	return components[i];
}

Vec3& Vec3::operator+=(const Vec3& v) {
	for (int i = 0; i < 3; i++) {
		components[i] += v.components[i];
	}
	return *this;
}

Vec3& Vec3::operator*=(const double t) {
	for (int i = 0; i < 3; i++) {
		components[i] *= t;
	}
	return *this;
}

Vec3& Vec3::operator/=(const double t) {
	return *this *= (1 / t);
}

double Vec3::length() const {
	return sqrt(length_squared());
}

double Vec3::length_squared() const {
	return components[0] * components[0] + components[1] * components[1] + components[2] * components[2];
}

Vec3 Vec3::random() {
	return Vec3(random_double(), random_double(), random_double());
}

Vec3 Vec3::random(double min, double max) {
	return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

bool Vec3::near_zero() const {
	double threshold = 1e-8;
	return (fabs(components[0]) < threshold) && (fabs(components[1]) < threshold) && (fabs(components[2]) < threshold);
}

//=============================================================================
// Utility functions
//=============================================================================

std::ostream& operator<<(std::ostream& out, const Vec3& v) {
	return out << v.x() << " " << v.y() << " " << v.z();
}

Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

Vec3 operator*(const Vec3& v, double t) {
	return Vec3(t * v.x(), t * v.y(), t * v.z());
}

Vec3 operator*(double t, const Vec3& v) {
	return v * t;
}

Vec3 operator/(const Vec3& v, double t) {
	return v * (1 / t);
}

double dot(const Vec3& u, const Vec3& v) {
	return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

Vec3 cross(const Vec3& u, const Vec3& v) {
	return Vec3(u.y() * v.z() - u.z() * v.y(),
		u.z() * v.x() - u.x() * v.z(),
		u.x() * v.y() - u.y() * v.x());
}

Vec3 unit_vector(const Vec3& v) {
	return v / v.length();
}

Vec3 random_in_unit_sphere() {
	while (true) {
		Vec3 randomPoint = Vec3::random(-1, 1);
		if (randomPoint.length_squared() < 1) {
			return randomPoint;
		}
	}
}

Vec3 random_unit_vector() {
	return unit_vector(random_in_unit_sphere());
}

Vec3 random_on_hemisphere(const Vec3& normal) {
	Vec3 on_unit_sphere = random_unit_vector();
	if (dot(on_unit_sphere, normal) > 0.0) {
		return on_unit_sphere;
	}
	else {
		return -on_unit_sphere;
	}
}

Vec3 random_in_unit_disk() {
	while (true) {
		Vec3 p = Vec3(random_double(-1, 1), random_double(-1, 1), 0);
		if (p.length_squared() < 1)
			return p;
	}
}

Vec3 reflect(const Vec3& v, const Vec3& n) {
	return v - 2 * dot(v, n) * n;
}

// Solving for the refracted ray using the perpendicular and parallel components of the refracted ray
// Precondition: v and n must be unit vectors
Vec3 refract(const Vec3& v, const Vec3& n, double refraction_ratio) {
	double cos_theta = fmin(dot(-v, n), 1.0);
	Vec3 refracted_ray_perp = refraction_ratio * (v + cos_theta * n);
	Vec3 refracted_ray_parallel = -sqrt(fabs(1.0 - refracted_ray_perp.length_squared())) * n;
	return refracted_ray_perp + refracted_ray_parallel;
}