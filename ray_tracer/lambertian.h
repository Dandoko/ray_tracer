#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

class Lambertian : public Material {
public:
	Lambertian(const Color& a);
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:
	Color albedo;
};

#endif