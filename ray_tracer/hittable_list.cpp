#include "hittable_list.h"

HittableList::HittableList() {}

void HittableList::clear() {
	objects.clear();
}

void HittableList::add(std::shared_ptr<Hittable> object) {
	objects.push_back(object);
}

bool HittableList::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
	HitRecord temp_record{};
	bool hit_something = false;
	double closest_so_far = t_max;

	// Moving from the farthest point of the ray to the closest point of the ray and updating the closet_so_far value
	for (const std::shared_ptr<Hittable>& obj : objects) {
		if (obj->hit(r, t_min, closest_so_far, temp_record)) {
			hit_something = true;
			closest_so_far = temp_record.t;
			rec = temp_record;
		}
	}

	return hit_something;
}