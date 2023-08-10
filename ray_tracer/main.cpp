#include <iostream>

#include "color.h"
#include "ray.h"
#include "vec3.h"

Color ray_color(const Ray& r) {
    // Colors the background (linearly blended gradient)
    Vec3 unit_direction = unit_vector(r.direction());                   // Scaling to unit length
    double t = 0.5 * (unit_direction.y() + 1.0);                        // 0.0 <= t <= 1.0
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0); // lerp value = (1 - t) * startVal + t * endVal
}

int main() {
    // Image
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = image_width / aspect_ratio;

    // Camera
    double focal_length = 1.0;
    double viewport_height = 2.0;                                               // Arbitrary viewport height
    double viewport_width = viewport_height *                                   // Don't use aspect ratio because it might not be the actual ratio between the
                            (static_cast<double>(image_width)/image_height);    // image width and height since the height and width are ints, not real numbers
    Point3 camera_centre = Point3(0, 0, 0);

    // Horizontal and vertical vectors along the viewport edges
    Vec3 viewport_u = Vec3(viewport_width, 0, 0);   // Left edge to right edge of viewport
    Vec3 viewport_v = Vec3(0, -viewport_height, 0); // Top edge to bottom edge of viewport

    // Horizontal and vertical delta vectors for the size of a pixel in the viewport
    Vec3 pixel_delta_u = viewport_u / image_width;
    Vec3 pixel_delta_v = viewport_v / image_height;

    // The location of the upper left corner of the viewport and the zeroth pixel
    //=========================================================================
    // z-axis goes INTO the viewport?????
    // Global axes: y-axis goes up, x-axis goes right, z-axis goes into the viewport
    //=========================================================================
    Point3 viewport_upper_left = camera_centre - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    Point3 pixel_upper_left = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // Image is rendered top to bottom, left to right
    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            Point3 pixel_centre = pixel_upper_left + (i * pixel_delta_u) + (j * pixel_delta_v);
            Vec3 ray_direction = pixel_centre - camera_centre;
            Ray r(camera_centre, ray_direction);

            Color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
}