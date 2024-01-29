#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "texture.h"

class Lambertian : public Material {
public:
	Lambertian(const Color& a);
	Lambertian(std::shared_ptr<Texture> a);
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:
	std::shared_ptr<Texture> albedo;
};

#endif