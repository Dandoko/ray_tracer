#include "checker_texture.h"
#include "solid_color.h"

CheckerTexture::CheckerTexture(double scale, std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd)
	: my_inversed_scale(1.0 / scale), my_even_texture(even), my_odd_texture(odd)
{
}

CheckerTexture::CheckerTexture(double scale, Color c1, Color c2)
	: my_inversed_scale(1.0 / scale), my_even_texture(std::make_shared<SolidColor>(c1)), my_odd_texture(std::make_shared<SolidColor>(c2))
{
}

Color
CheckerTexture::value(double u, double v, const Point3& p) const
{
	int x = static_cast<int>(std::floor(my_inversed_scale * p.x()));
	int y = static_cast<int>(std::floor(my_inversed_scale * p.y()));
	int z = static_cast<int>(std::floor(my_inversed_scale * p.z()));

	bool is_odd = (x + y + z) % 2;

	return is_odd ? my_odd_texture->value(u, v, p) : my_even_texture->value(u, v, p);
}