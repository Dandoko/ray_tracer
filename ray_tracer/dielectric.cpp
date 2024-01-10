#include "dielectric.h"

#include "color.h"
#include "utility.h"

Dielectric::Dielectric(double refraction_index) : refraction_index(refraction_index) {}

bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
    double n1 = rec.is_front_face ? REFRACTION_INDEX_AIR : refraction_index;
    double n2 = rec.is_front_face ? refraction_index : REFRACTION_INDEX_AIR;
    double refraction_ratio = n1 / n2;
    Vec3 r_in_unit_direction = unit_vector(r_in.direction());
    double cos_theta = fmin(dot(-r_in_unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    bool must_reflect = refraction_ratio * sin_theta > 1.0;
    Vec3 direction;
    
    if (must_reflect || reflectance(cos_theta, n1, n2) > random_double()) {
        direction = reflect(r_in_unit_direction, rec.normal);
    }
    else {
        direction = refract(r_in_unit_direction, rec.normal, refraction_ratio);
    }

    scattered = Ray(rec.p, direction, r_in.time());
    attenuation = Color(1, 1, 1); // Dielectrics absorb nothing
    return true;
}

double Dielectric::reflectance(double cosine, double n1, double n2) {
    double r0 = (n1 - n2) / (n1 + n2);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}