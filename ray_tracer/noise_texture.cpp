#include "noise_texture.h"

NoiseTexture::NoiseTexture(double scale) : my_scale(scale) {}

Color NoiseTexture::value(double u, double v, const Point3& p) const {
	Point3 scaled_p = p * my_scale;
	double noise_val = sin(scaled_p.z() + 10 * my_noise.turbulence(scaled_p));
	noise_val = 0.5 * (1.0 + noise_val); // Converting to [0, 1] range since sine can be negative
	return Color(1, 1, 1) * noise_val;
}