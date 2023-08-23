#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"

class Dielectric : public Material {
public:
	Dielectric(double refraction_index);

	virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const;

private:
	double refraction_index;

	static double reflectance(double cosine, double n1, double n2);	// Schlick's approximation
																	// Needs to be static because scatter is a const function
};

#endif