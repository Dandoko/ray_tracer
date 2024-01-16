// Stores a list of Hittables

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "aabb.h"
#include "hittable.h"

#include <memory>
#include <vector>

class HittableList : public Hittable {
private:
	AABB b_box;
public:
	HittableList();
	HittableList(std::shared_ptr<Hittable> object);

	void clear();
	void add(std::shared_ptr<Hittable> object);

	virtual bool hit(const Ray& r, Interval t_interval, HitRecord& rec) const override;
	virtual AABB bounding_box() const override;

	std::vector<std::shared_ptr<Hittable>> objects;
};

#endif