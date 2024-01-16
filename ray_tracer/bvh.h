#ifndef BVH_H
#define BVH_H

#include "hittable.h"
#include "hittable_list.h"

class BVHNode : public Hittable {
private:
	std::shared_ptr<Hittable> left;
	std::shared_ptr<Hittable> right;
	AABB b_box;

	// Functions used to sort the BVH
	static bool compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis);
	static bool compare_x(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
	static bool compare_y(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
	static bool compare_z(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);

public:
	BVHNode(const HittableList& list);
	BVHNode(const std::vector<std::shared_ptr<Hittable>>& src_objects, size_t start, size_t end);

	virtual bool hit(const Ray& r, Interval t_interval, HitRecord& rec) const override;
	virtual AABB bounding_box() const override;
};

#endif