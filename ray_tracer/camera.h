#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "hittable.h"
#include "utility.h"

class Camera {
public:
	Camera(double aspect_ratio, int image_width, int samples_per_pixel, int depth, int v_fov, const Point3& look_from,
			const Point3& look_at, const Vec3& view_up, float defocus_angle, double focus_dist);
	void render(const Hittable& world);

private:
	// Image
	double my_aspect_ratio;			// Ratio of image width over height
	int my_image_width;				// Rendered image width in pixel count
	int my_image_height;			// Rendered image height in pixel count

	// Camera orientation
	double my_v_fov;				// Vertical FOV in degrees
	Point3 my_look_from;			// The location the camera is looking from
	Point3 my_look_at;				// The location the camera is looking at
	Vec3 my_view_up;				// The relative up direction for the camera
	Point3 my_centre;				// Camera centre

	// Orthonormal basis to describe the camera's orientation
	Vec3 my_u;
	Vec3 my_v;
	Vec3 my_w;

	Point3 my_pixel_upper_left;		// Position of the top leftmost pixel
	Vec3 my_pixel_delta_u;			// Offset to pixel to the right in the viewport
	Vec3 my_pixel_delta_v;			// Offset to pixel below in the viewport
	
	// Ray tracing specifications
	int my_samples_per_pixel;		// Number of random samples for each pixel for anti-aliasing
	int my_max_depth;				// Maximum number of ray bounces

	// Defocus blur
	double my_focus_dist;			// Distance from camera look_from point to focus plane
	double my_defocus_angle;		// Semiangle of cone with apex at viewport centre and base center at camera
	Vec3 my_defocus_disk_u;			// Defocus disk horizontal radius
	Vec3 my_defocus_disk_v;			// Defocus disk vertical radius

	Color ray_color(const Ray& r, const Hittable& world, int depth) const;
	Ray get_ray(int i, int j) const;
	Vec3 pixel_sample_square() const;
	Point3 defocus_disk_sample() const;	// Returns a random point on the defocus disk
};

#endif