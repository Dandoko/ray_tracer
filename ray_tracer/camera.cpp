#include "camera.h"
#include "material.h"
#include "vec3.h"

Camera::Camera(double aspect_ratio, int image_width, int samples_per_pixel, int depth, int v_fov, const Point3& look_from,
                const Point3& look_at, const Vec3& view_up, float defocus_angle, double focus_dist)
    : my_aspect_ratio(aspect_ratio), my_image_width(image_width), my_samples_per_pixel(samples_per_pixel),
    my_max_depth(depth), my_v_fov(v_fov), my_look_from(look_from), my_look_at(look_at), my_view_up(view_up),
    my_defocus_angle(defocus_angle), my_focus_dist(focus_dist)
{
    my_image_height = my_image_width / my_aspect_ratio;

    // Camera world position
    my_centre = my_look_from;

    // Viewport dimensions
    double focal_length = my_focus_dist;                               // Image grid is on the focus plane
    double theta = degrees_to_radians(my_v_fov);
    double v_fov_height = tan(theta / 2);
    double viewport_height = 2.0 * (v_fov_height * focal_length);   // Arbitrary viewport height scale of 2
    double viewport_width = viewport_height *                       // Don't use aspect ratio because it might not be the actual ratio between the
        (static_cast<double>(my_image_width) / my_image_height);    // image width and height since the height and width are ints, not real numbers

    my_w = unit_vector(my_look_from - my_look_at);
    my_u = unit_vector(cross(my_view_up, my_w));
    my_v = cross(my_w, my_u);

    // Horizontal and vertical vectors along the viewport edges
    Vec3 viewport_u = viewport_width * my_u;       // Left edge to right edge of viewport
    Vec3 viewport_v = viewport_height * -my_v;     // Top edge to bottom edge of viewport

    // Horizontal and vertical delta vectors for the offset of a pixel in the viewport
    my_pixel_delta_u = viewport_u / my_image_width;
    my_pixel_delta_v = viewport_v / my_image_height;

    // The location of the upper left corner of the viewport and the zeroth pixel
    // Global axes: y-axis goes up, x-axis goes right, z-axis goes out of the viewport
    Point3 viewport_upper_left = my_centre - (focal_length * my_w) - viewport_u / 2 - viewport_v / 2;
    my_pixel_upper_left = viewport_upper_left + 0.5 * (my_pixel_delta_u + my_pixel_delta_v);

    double defocus_radius = my_focus_dist * tan(degrees_to_radians(my_defocus_angle / 2));
    my_defocus_disk_u = my_u * defocus_radius;
    my_defocus_disk_v = my_v * defocus_radius;
}

void Camera::render(const Hittable& world) {
    std::cout << "P3\n" << my_image_width << ' ' << my_image_height << "\n255\n";

    // Image is rendered top to bottom, left to right
    for (int j = 0; j < my_image_height; j++) {
        std::clog << "\rScanlines remaining: " << (my_image_height - j) << ' ' << std::flush;
        for (int i = 0; i < my_image_width; i++) {
            
            // Anti-aliasing
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < my_samples_per_pixel; s++) {
                Ray r = get_ray(i, j);
                pixel_color += ray_color(r, world, my_max_depth);
            }
            write_color(std::cout, pixel_color, my_samples_per_pixel);
        }
    }
}

Color Camera::ray_color(const Ray& r, const Hittable& world, int depth) const {
    if (0 >= depth) {
        return Color(0, 0, 0);
    }

    HitRecord rec;
    if (world.hit(r, Interval{ 0.001, INF }, rec)) {
        Ray scattered;
        Color attenuation;
        
        if (rec.mat->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth - 1);
        }

        // Absorb rays that scatter below the surface from fuzzing for metals
        return Color(0, 0, 0);
    }

    // Colors the background (linearly blended gradient)
    Vec3 unit_direction = unit_vector(r.direction());                   // Scaling to unit length
    double a = 0.5 * (unit_direction.y() + 1.0);                        // 0.0 <= t <= 1.0
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0); // lerp value = (1 - t) * startVal + t * endVal
}

Ray Camera::get_ray(int i, int j) const {
    Point3 pixel_centre = my_pixel_upper_left + (i * my_pixel_delta_u) + (j * my_pixel_delta_v);
    Point3 pixel_sample = pixel_centre + pixel_sample_square();

    // Gets a random camera ray that is on the camera defocus disk
    Point3 ray_origin = (my_defocus_angle <= 0) ? my_centre : defocus_disk_sample();
    Vec3 ray_direction = pixel_sample - ray_origin;

    // Ray time is between [0, 1)
    // Start time is 0, end time is 1
    double ray_time = random_double();

    return Ray(ray_origin, ray_direction, ray_time);
}

Vec3 Camera::pixel_sample_square() const {
    double px = -0.5 + random_double();
    double py = -0.5 + random_double();
    return (px * my_pixel_delta_u) + (py * my_pixel_delta_v);
}

Point3 Camera::defocus_disk_sample() const {
    Point3 p = random_in_unit_disk();
    return my_centre + (p.x() * my_defocus_disk_u) + (p.y() * my_defocus_disk_v);
}