#include <iostream>

#include "color.h"

void write_color(std::ostream& out, const Color& pixel_color) {
	// Writing the translated [0, 255] value of each color component
	int r = static_cast<int>(255.999 * pixel_color.x());
	int g = static_cast<int>(255.999 * pixel_color.y());
	int b = static_cast<int>(255.999 * pixel_color.z());
	out << r << " " << g << " " << b << " " << "\n";
}
