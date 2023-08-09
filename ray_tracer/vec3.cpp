#include "vec3.h"

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