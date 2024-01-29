#include "lambertian.h"
#include "solid_color.h"

Lambertian::Lambertian(const Color& a) : albedo(std::make_shared<SolidColor>(a))
{
}

Lambertian::Lambertian(std::shared_ptr<Texture> a) : albedo(a)
{
}

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
    Vec3 scatter_direction = rec.normal + random_unit_vector();

    // Edge case for when the scatter direction is zero from the normal being exactly opposite to the random vector
    if (scatter_direction.near_zero())
    {
        scatter_direction = rec.normal;
    }

    scattered = Ray(rec.p, scatter_direction, r_in.time());
    attenuation = albedo->value(rec.u, rec.v, rec.p);
    return true;
}