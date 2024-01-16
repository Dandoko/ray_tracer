#include <algorithm>

#include "bvh.h"
#include "interval.h"
#include "utility.h"

// Ctor chaining
BVHNode::BVHNode(const HittableList& list) : BVHNode(list.objects, 0, list.objects.size()) {}

BVHNode::BVHNode(const std::vector<std::shared_ptr<Hittable>>& src_objects, size_t start, size_t end) {
	std::vector<std::shared_ptr<Hittable>> copied_objects = src_objects;

	int axis = random_int(0, 2);
	auto compareFn = (0 == axis) ? compare_x :
								   (1 == axis) ? compare_y : compare_z;

	size_t list_size = end - start;

	if (1 == list_size) {
		// Duplicate for left and right
		left = copied_objects[start];
		right = copied_objects[start];
	}
	else if (2 == list_size) {
		// Boxes can still overlap because we are assiging the children based on the the interval
		// min only according to the compareFn

		// Inserting to our BVH based on the smaller interval value
		if (compareFn(copied_objects[start], copied_objects[start + 1]) ) {
			left = copied_objects[start];
			right = copied_objects[start + 1];
		}
		else {
			left = copied_objects[start + 1];
			right = copied_objects[start];
		}
	}
	else {
		std::sort(copied_objects.begin() + start, copied_objects.begin() + end, compareFn);

		size_t mid = start + list_size / 2;

		left = std::make_shared<BVHNode>(copied_objects, start, mid);
		right = std::make_shared<BVHNode>(copied_objects, mid, end);
	}

	b_box = AABB(left->bounding_box(), right->bounding_box());
}

bool BVHNode::hit(const Ray& r, Interval t_interval, HitRecord& rec) const {
	if (!b_box.hit(r, t_interval)) {
		return false;
	}

	bool hit_left = left->hit(r, t_interval, rec);

	// If we hit the left child, then we should use the ray intersection point as the new interval max
	double new_interval_max = hit_left ? rec.t : t_interval.max;
	bool hit_right = right->hit(r, Interval(t_interval.min, new_interval_max), rec);

	return hit_left || hit_right;
}

AABB BVHNode::bounding_box() const {
	return b_box;
}

bool BVHNode::compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis) {
	return a->bounding_box().axis(axis).min < b->bounding_box().axis(axis).min;
}

bool BVHNode::compare_x(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
	return compare(a, b, 0);
}

bool BVHNode::compare_y(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
	return compare(a, b, 1);
}

bool BVHNode::compare_z(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
	return compare(a, b, 2);
}