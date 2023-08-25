#include <iostream>

#include "camera.h"
#include "color.h"
#include "dielectric.h"
#include "hittable.h"
#include "hittable_list.h"
#include "interval.h"
#include "lambertian.h"
#include "metal.h"
#include "ray.h"
#include "sphere.h"
#include "utility.h"
#include "vec3.h"

int main() {
    // World
    HittableList world{};

    auto material_ground = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    auto material_left = std::make_shared<Metal>(Color(0.84, 0.85, 0.94), 0.0);
    auto material_center = std::make_shared<Lambertian>(Color(0.55, 0.78, 1.0));
    auto material_right = std::make_shared<Lambertian>(Color(1.0, 0.4, 0.4));
    auto material_front = std::make_shared<Dielectric>(1.5);

    world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3(-1.01, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.3), 0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(1.01, 0.0, -1.0), 0.5, material_right));
    world.add(std::make_shared<Sphere>(Point3(0.0, -0.35, 1.0), 0.15, material_front));

    // Camera
    Camera camera{};
    camera.render(world);
}