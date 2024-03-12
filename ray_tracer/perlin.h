#ifndef PERLIN_H
#define PERLIN_H

#include "utility.h"
#include "vec3.h"

class Perlin {
public:
	Perlin();
	~Perlin();

	// Hash function to change a 3D point to a random number
	double noise_hash(const Point3& p) const;

	double turbulence(const Point3& p, int depth = 7) const;

private:
	static const int point_count = 256;	// We will store 256 different random numbers for our Perlin Noise
										// 256 = 8 bits

	Vec3* random_vec_list;				// A list of normalized vectors from the range [-1, 1] that exist on the lattice points
	int* perm_x;						// Permutation of indices for the hashed x values for 3D points
	int* perm_y;						// Permutation of indices for the hashed y values for 3D points
	int* perm_z;						// Permutation of indices for the hashed z values for 3D points

	int* generate_perm();

};

#endif