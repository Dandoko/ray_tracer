// Stores a list of Hittables

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

class HittableList : public Hittable {
private:
	std::vector<std::shared_ptr<Hittable>> objects;
public:
	HittableList();

	void clear();
	void add(std::shared_ptr<Hittable> object);

	virtual bool hit(const Ray& r, Interval t_interval, HitRecord& rec) const override;
};

#endif