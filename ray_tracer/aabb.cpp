#include "aabb.h"

AABB::AABB() {}

AABB::AABB(const Interval& iX, const Interval& iY, const Interval& iZ) : x(iX), y(iY), z(iZ) {}

AABB::AABB(const Point3& a, const Point3& b) {
    // Creating a bounding box using two vertices that are part of the same bounding box
    x = Interval(fmin(a[0], b[0]), fmax(a[0], b[0]));
    y = Interval(fmin(a[1], b[1]), fmax(a[1], b[1]));
    z = Interval(fmin(a[2], b[2]), fmax(a[2], b[2]));
}

AABB::AABB(const AABB& box0, const AABB& box1) {
    // Creating a bounding box using the bigger component of both boxes
    x = Interval(box0.x, box1.x);
    y = Interval(box0.y, box1.y);
    z = Interval(box0.z, box1.z);
}

const Interval& AABB::axis(int i) const {
    if (0 == i) {
        return x;
    }
    else if (1 == i) {
        return y;
    }
    else {
        return z;
    }
}

bool AABB::hit(const Ray& r, Interval t) const {
    // There is a hit if all three x/y/z component intervals overlap

    // Looping once for each x/y/z component
    for (int i = 0; i < 3; i++) {
        // Getting the ray's interval in the current component via an optimized method
        double inverse_axis_ray_direction = 1 / r.direction()[i];
        double axis_ray_origin = r.origin()[i];
        double axis_bouding_box_min_edge = axis(i).min;
        double axis_bounding_box_max_edge = axis(i).max;

        double t0 = (axis_bouding_box_min_edge - axis_ray_origin) * inverse_axis_ray_direction;
        double t1 = (axis_bounding_box_max_edge - axis_ray_origin) * inverse_axis_ray_direction;

        // If the inverse direction is negative, then the negative max is smaller than the negative min so swap
        if (0 > inverse_axis_ray_direction) {
            std::swap(t0, t1);
        }
        
        // Updating the t-interval to be as small as possible as it iterates through each component
        t.min = fmax(t0, t.min);
        t.max = fmin(t1, t.max);

        // Checking if any of the intervals don't overlap 
        if (t.max <= t.min) {
            return false;
        }
    }
    
    return true;
}