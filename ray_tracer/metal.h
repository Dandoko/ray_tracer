#ifndef METAL_H
#define METAL_H

#include "material.h"

class Metal : public Material {
public:
	Metal(const Color& a);
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:
	Color albedo;

};

#endif