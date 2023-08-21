#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

void write_color(std::ostream& out, const Color& pixel_color, int samples_per_pixel);

double linear_to_gamma(double linear_component); // Using Gamma 2

#endif