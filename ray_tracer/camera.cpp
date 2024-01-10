#include "camera.h"
#include "material.h"
#include "vec3.h"

Camera::Camera() {
    // Image
    aspect_ratio = 16.0 / 9.0;
    image_width = 400;
    image_height = image_width / aspect_ratio;

    // Camera orientation
    v_fov = 20;
    look_from = Point3(0, 0, 6);
    look_at = Point3(0, 0, 0);
    view_up = Vec3(0, 1, 0);

    // Camera world position
    centre = look_from;

    // Viewport dimensions
    focus_dist = 6;
    double focal_length = focus_dist;                               // Image grid is on the focus plane
    double theta = degrees_to_radians(v_fov);
    double v_fov_height = tan(theta / 2);
    double viewport_height = 2.0 * (v_fov_height * focal_length);   // Arbitrary viewport height scale of 2
    double viewport_width = viewport_height *                       // Don't use aspect ratio because it might not be the actual ratio between the
        (static_cast<double>(image_width) / image_height);          // image width and height since the height and width are ints, not real numbers

    // Orthonormal basis to describe the camera's orientation
    w = unit_vector(look_from - look_at);
    u = unit_vector(cross(view_up, w));
    v = cross(w, u);

    // Horizontal and vertical vectors along the viewport edges
    Vec3 viewport_u = viewport_width * u;       // Left edge to right edge of viewport
    Vec3 viewport_v = viewport_height * -v;     // Top edge to bottom edge of viewport

    // Horizontal and vertical delta vectors for the offset of a pixel in the viewport
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // The location of the upper left corner of the viewport and the zeroth pixel
    // Global axes: y-axis goes up, x-axis goes right, z-axis goes out of the viewport
    Point3 viewport_upper_left = centre - (focal_length * w) - viewport_u / 2 - viewport_v / 2;
    pixel_upper_left = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Ray tracing specifications
    samples_per_pixel = 50;
    max_depth = 50;

    // Defocus blur
    defocus_angle = 0.05;
    double defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}

void Camera::render(const Hittable& world) {
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // Image is rendered top to bottom, left to right
    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            
            // Anti-aliasing
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++) {
                Ray r = get_ray(i, j);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
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
    Point3 pixel_centre = pixel_upper_left + (i * pixel_delta_u) + (j * pixel_delta_v);
    Point3 pixel_sample = pixel_centre + pixel_sample_square();

    // Gets a random camera ray that is on the camera defocus disk
    Point3 ray_origin = (defocus_angle <= 0) ? centre : defocus_disk_sample();
    Vec3 ray_direction = pixel_sample - ray_origin;

    // Ray time is between [0, 1)
    // Start time is 0, end time is 1
    double ray_time = random_double();

    return Ray(ray_origin, ray_direction, ray_time);
}

Vec3 Camera::pixel_sample_square() const {
    double px = -0.5 + random_double();
    double py = -0.5 + random_double();
    return (px * pixel_delta_u) + (py * pixel_delta_v);
}

Point3 Camera::defocus_disk_sample() const {
    Point3 p = random_in_unit_disk();
    return centre + (p.x() * defocus_disk_u) + (p.y() * defocus_disk_v);
}