#include <iostream>

#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "interval.h"
#include "ray.h"
#include "sphere.h"
#include "utility.h"
#include "vec3.h"

Color ray_color(const Ray& r, const Hittable& world) {
    HitRecord rec;
    if (world.hit(r, Interval{0, INF}, rec)) {
        return 0.5 * (rec.normal + Color(1, 1, 1));
    }

    // Colors the background (linearly blended gradient)
    Vec3 unit_direction = unit_vector(r.direction());                   // Scaling to unit length
    double a = 0.5 * (unit_direction.y() + 1.0);                        // 0.0 <= t <= 1.0
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0); // lerp value = (1 - t) * startVal + t * endVal
}

int main() {
    // World
    HittableList world{};
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    Camera camera{};
    camera.render(world);
}