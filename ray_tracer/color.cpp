#include <iostream>

#include "color.h"
#include "interval.h"

void write_color(std::ostream& out, const Color& pixel_color, int samples_per_pixel) {
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // Divide the color by the number of samples for anti-aliasing to get the average color
    double scale = 1.0 / samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;

    // Applying linear to gamma transformatin
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // Writing the translated [0, 255] value of each color component
    static const Interval intensity(0.000, 0.999);
    out << static_cast<int>(256 * intensity.clamp(r)) << ' '
        << static_cast<int>(256 * intensity.clamp(g)) << ' '
        << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}

double linear_to_gamma(double linear_component) {
    // Using Gamma 2
    return sqrt(linear_component);
}