#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "hittable.h"
#include "ray.h"

class Material {
public:
	virtual bool scatter(const Ray& r, const HitRecord& rec, Color& attenuation, Ray& scattered) const = 0;
};

#endif