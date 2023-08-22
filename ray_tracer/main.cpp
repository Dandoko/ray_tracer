#include <iostream>

#include "camera.h"
#include "color.h"
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

    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    auto material_left = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
    auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

    // Camera
    Camera camera{};
    camera.render(world);
}