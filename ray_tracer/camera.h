#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "hittable.h"
#include "utility.h"

class Camera {
public:
	Camera();
	void render(const Hittable& world);

private:
	double aspect_ratio;		// Ratio of image width over height
	int image_width;			// Rendered image width in pixel count
	int image_height;			// Rendered image height in pixel count
	Point3 centre;				// Camera centre
	Point3 pixel_upper_left;	// Position of the top leftmost pixel
	Vec3 pixel_delta_u;			// Offset to pixel to the right in the viewport
	Vec3 pixel_delta_v;			// Offset to pixel below in the viewport

	Color ray_color(const Ray& r, const Hittable& world) const;
};

#endif