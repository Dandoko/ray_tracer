#ifndef CHECKER_TEXTURE_H
#define CHECKER_TEXTURE_H

#include "texture.h"

class CheckerTexture : public Texture {
private:
	double my_inversed_scale;
	std::shared_ptr<Texture> my_even_texture;
	std::shared_ptr<Texture> my_odd_texture;
public:
	CheckerTexture(double scale, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd);
	CheckerTexture(double scale, Color c1, Color c2);

	Color value(double u, double v, const Point3& p) const override;
};

#endif