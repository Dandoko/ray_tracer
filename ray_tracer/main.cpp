#include <iostream>

#include "bvh.h"
#include "camera.h"
#include "color.h"
#include "dielectric.h"
#include "hittable.h"
#include "hittable_list.h"
#include "interval.h"
#include "lambertian.h"
#include "metal.h"
#include "noise_texture.h"
#include "quad.h"
#include "ray.h"
#include "sphere.h"
#include "checker_texture.h"
#include "utility.h"
#include "vec3.h"

void simple_world() {
    // World
    HittableList world{};

    auto checker_texture = std::make_shared<CheckerTexture>(0.32, Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));

    auto material_ground = std::make_shared<Lambertian>(checker_texture);
    auto material_left = std::make_shared<Metal>(Color(0.84, 0.85, 0.94), 0.0);
    auto material_center = std::make_shared<Lambertian>(Color(0.55, 0.78, 1.0));
    auto material_right = std::make_shared<Lambertian>(Color(1.0, 0.4, 0.4));
    auto material_front = std::make_shared<Dielectric>(1.5);
    auto material_left_front = std::make_shared<Lambertian>(Color(1.0, 0.4, 0.4));

    world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3(-1.01, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.3), 0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(1.01, 0.0, -1.0), 0.5, material_right));
    
    Point3 centre_front = Point3(0.0, -0.35, 1.0);
    Point3 centre_left_front = Point3(-1.0, -0.35, 1.0);
    world.add(std::make_shared<Sphere>(centre_front, centre_front + Vec3(0, 0.1, 0), 0.15, material_front));
    world.add(std::make_shared<Sphere>(centre_left_front, centre_left_front + Vec3(0, 0.12, 0), 0.15, material_left_front));

    world = HittableList(std::make_shared<BVHNode>(world));

    // Camera
    Camera camera{ 16.0/9.0, 400, 50, 50, 20, Point3(0, 0, 6), Point3(0, 0, 0), Vec3(0, 1, 0), 0.05, 6 };
    camera.render(world);
}

void two_spheres() {
    HittableList world{};

    auto checker_texture = std::make_shared<CheckerTexture>(0.3, Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));

    auto material_ground = std::make_shared<Lambertian>(checker_texture);

    world.add(std::make_shared<Sphere>(Point3(0.0, -10.0, -0), 10.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3(0.0,  10.0, -0), 10.0, material_ground));

    Camera camera{ 16.0 / 9.0, 400, 50, 50, 20, Point3(13, 2, 3), Point3(0, 0, 0), Vec3(0, 1, 0), 0 , 10 };
    camera.render(world);
}

void two_perlin_spheres() {
    HittableList world{};

    auto perlin_texture = std::make_shared<NoiseTexture>(4);

    world.add(std::make_shared<Sphere>(Point3(0.0, -1000.0, 0.0), 1000.0, std::make_shared<Lambertian>(perlin_texture)));
    world.add(std::make_shared<Sphere>(Point3(0.0, 2, 0.0), 2.0, std::make_shared<Lambertian>(perlin_texture)));

    Camera camera{ 16.0 / 9.0, 400, 50, 50, 20, Point3(13, 2, 3), Point3(0, 0, 0), Vec3(0, 1, 0), 0 , 10 };
    camera.render(world);
}

void quads()
{
    HittableList world{};

    auto left_red = std::make_shared<Lambertian>(Color(1.0, 0.2, 0.2));
    auto back_green = std::make_shared<Lambertian>(Color(0.2, 1.0, 0.2));
    auto right_blue = std::make_shared<Lambertian>(Color(0.2, 0.2, 1.0));
    auto upper_orange = std::make_shared<Lambertian>(Color(1.0, 0.5, 0.0));
    auto lower_teal = std::make_shared<Lambertian>(Color(0.2, 0.8, 0.8));

    world.add(std::make_shared<Quad>(Point3(-3, -2, 5), Vec3(0, 0, -4), Vec3(0, 4, 0), left_red));
    world.add(std::make_shared<Quad>(Point3(-2, -2, 0), Vec3(4, 0, 0), Vec3(0, 4, 0), back_green));
    world.add(std::make_shared<Quad>(Point3(3, -2, 1), Vec3(0, 0, 4), Vec3(0, 4, 0), right_blue));
    world.add(std::make_shared<Quad>(Point3(-2, 3, 1), Vec3(4, 0, 0), Vec3(0, 0, 4), upper_orange));
    world.add(std::make_shared<Quad>(Point3(-2, -3, 5), Vec3(4, 0, 0), Vec3(0, 0, -4), lower_teal));

    Camera camera{ 1.0, 400, 50, 50, 80, Point3(0, 0, 9), Point3(0, 0, 0), Vec3(0, 1, 0), 0, 10 };
    camera.render(world);
}

int main() {
    //simple_world();
    //two_spheres();
    //two_perlin_spheres();
    quads();

    return 0;
}