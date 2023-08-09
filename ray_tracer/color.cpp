#include <iostream>

#include "color.h"

void write_color(std::ostream& out, Color pixel_color) {
	double r = pixel_color.x();
	double g = pixel_color.y();
	double b = pixel_color.z();

	// Writing the translated [0, 255] value of each color component
	int ir = static_cast<int>(256 * r);
	int ig = static_cast<int>(256 * g);
	int ib = static_cast<int>(256 * b);
	out << ir << " " << ig << " " << ib << " " << "\n";
}
