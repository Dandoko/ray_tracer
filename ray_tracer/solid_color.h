#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H

#include "texture.h"

class SolidColor : public Texture {
private:
	Color my_color;
public:
	SolidColor(Color c);
	SolidColor(double r, double g, double b);

	Color value(double u, double v, const Point3& p) const override;
};

#endif