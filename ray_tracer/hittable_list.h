// Stores a list of Hittables

#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using namespace std;

class HittableList : public Hittable {
private:
	vector<shared_ptr<Hittable>> objects;
public:
	HittableList();

	void clear();
	void add(shared_ptr<Hittable> object);

	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
};

#endif