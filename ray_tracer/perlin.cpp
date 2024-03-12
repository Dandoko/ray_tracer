#include "perlin.h"

Perlin::Perlin() {
	// Initializes random numbers that represent the hashed values
	random_vec_list = new Vec3[point_count];
	for (int i = 0; i < point_count; i++) {
		random_vec_list[i] = unit_vector(Vec3::random(-1, 1));
	}

	perm_x = generate_perm();
	perm_y = generate_perm();
	perm_z = generate_perm();
}

Perlin::~Perlin() {
	delete[] random_vec_list;
	delete[] perm_x;
	delete[] perm_y;
	delete[] perm_z;
}

double Perlin::noise_hash(const Point3& p) const {
	// How far the input point is from the lattice point
	double u = p.x() - floor(p.x());
	double v = p.y() - floor(p.y());
	double w = p.z() - floor(p.z());

	// The lattice point closed to the input point
	int x = static_cast<int>(floor(p.x()));
	int y = static_cast<int>(floor(p.y()));
	int z = static_cast<int>(floor(p.z()));

	// Populating the nearest eight lattice points
	Vec3 interpolating_hashes[2][2][2];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				interpolating_hashes[i][j][k] = random_vec_list[perm_x[(x + i) & 255] ^
																perm_y[(y + j) & 255] ^
																perm_z[(z + k) & 255]];
			}
		}
	}

	// Applying cublic Hermite spline to smoothen interpolation values
	double u_k1 = u * u * (3 - 2 * u);
	double v_k1 = v * v * (3 - 2 * v);
	double w_k1 = w * w * (3 - 2 * w);

	// Trilinear interpolation using the lattice points
	double total = 0.0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				Vec3 offset(u - i, v - j, w - k); // Offset from each lattice point

				total += (i * u_k1 + (1 - i) * (1 - u_k1)) *
						 (j * v_k1 + (1 - j) * (1 - v_k1)) *
						 (k * w_k1 + (1 - k) * (1 - w_k1)) *
						 dot(interpolating_hashes[i][j][k], offset);
			}
		}
	}

	return total;
}

double Perlin::turbulence(const Point3& p, int depth) const {
	double total = 0.0;
	Point3 temp_p = p;
	double weight = 1.0;

	for (int i = 0; i < depth; i++) {
		total += weight * noise_hash(temp_p);
		weight *= 0.5;
		temp_p *= 2;
	}

	return fabs(total); // Returning absolute value because noise_hash output could be negative
}

int* Perlin::generate_perm() {
	// Initializes the indices with values from 0 to 255
	int* perm = new int[point_count];
	for (int i = 0; i < point_count; i++) {
		perm[i] = i;
	}

	// Permutes the indices
	for (int i = point_count - 1; i > 0; i--) {
		int swapIndex = random_int(0, i);
		std::swap(perm[i], perm[swapIndex]);
	}

	return perm;
}
