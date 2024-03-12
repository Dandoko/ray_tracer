#ifndef NOISE_TEXTURE
#define NOISE_TEXTURE

#include "texture.h"
#include "perlin.h"

class NoiseTexture : public Texture {
public:
	NoiseTexture(double scale);

	Color value(double u, double v, const Point3& p) const override;

private:
	Perlin my_noise;
	double my_scale;
};

#endif