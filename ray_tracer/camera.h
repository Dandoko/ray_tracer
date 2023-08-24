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
	int samples_per_pixel;		// Number of random samples for each pixel for anti-aliasing
	int max_depth;				// Maximum number of ray bounces
	double v_fov;				// Vertical FOV in degrees
	Point3 look_from;			// The location the camera is looking from
	Point3 look_at;				// The location the camera is looking at
	Vec3 view_up;				// The relative up direction for the camera

	int image_height;			// Rendered image height in pixel count
	Point3 centre;				// Camera centre
	Point3 pixel_upper_left;	// Position of the top leftmost pixel
	Vec3 pixel_delta_u;			// Offset to pixel to the right in the viewport
	Vec3 pixel_delta_v;			// Offset to pixel below in the viewport
	Vec3 u;						// Basis vectors
	Vec3 v;
	Vec3 w;

	Color ray_color(const Ray& r, const Hittable& world, int depth) const;
	Ray get_ray(int i, int j) const;
	Vec3 pixel_sample_square() const;
};

#endif