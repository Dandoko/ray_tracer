#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class Vec3 {
public:
	Vec3();
	Vec3(double x, double y, double z);

	double x() const;
	double y() const;
	double z() const;

	Vec3 operator-() const;

	double operator[](int i) const; // read only
	double& operator[](int i);		// can modify

	Vec3& operator+=(const Vec3& v);
	Vec3& operator*=(const double t);
	Vec3& operator/=(const double t);

	double length() const;
	double length_squared() const;

	static Vec3 random();
	static Vec3 random(double min, double max);

	bool near_zero() const; // Return true is vector is close to zero in all components

private:
	double components[3]; // x, y, z
};

// Utility functions
std::ostream& operator<<(std::ostream& out, const Vec3& v);
Vec3 operator+(const Vec3& u, const Vec3& v);
Vec3 operator-(const Vec3& u, const Vec3& v);
Vec3 operator*(const Vec3& u, const Vec3& v);
Vec3 operator*(const Vec3& v, double t);
Vec3 operator*(double t, const Vec3& v); // Additional vector-scalor multiplication function for commutativity
Vec3 operator/(const Vec3& v, double t);

double dot(const Vec3& u, const Vec3& v);
Vec3 cross(const Vec3& u, const Vec3& v);

Vec3 unit_vector(const Vec3& v);

Vec3 random_in_unit_sphere();					// Gets a random vector in a unit sphere
Vec3 random_unit_vector();						// Gets a random vector on a unit sphere
Vec3 random_on_hemisphere(const Vec3& normal);	// Gets a random normalized vector on the same side as the normal

Vec3 reflect(const Vec3& v, const Vec3& n);

// Class aliases
using Point3 = Vec3;	// 3D point
using Color = Vec3;		// RGB color

#endif 