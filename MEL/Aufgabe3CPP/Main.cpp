#include <iostream>
#include <random>

#pragma region statics
	static uint64_t notHit = 0;
	static uint64_t target = 0xFEDCBA9876543210;
	static uint64_t globalBeschde = UINT64_MAX;
#pragma endregion

uint64_t random64() {
	uint64_t r = (rand() << 16) | rand();
	r <<= 32;
	return r | (rand() << 16) | rand();
}

uint64_t hammingDistance(uint64_t genA, uint64_t genB) {
	uint64_t x = genA ^ genB;
	uint64_t y = 0;
	while (x) {
		x &= x - 1;
		y++;
	}
	return y;
}

void cross(uint64_t * genA, uint64_t * genB, uint64_t position) {
	uint64_t Mask = ((1 << position) - 1);
	uint64_t aSave = *genA;
	uint64_t bSave = *genB;
	*genA = (aSave & Mask) | (bSave & !Mask);
	*genB = (aSave & !Mask) | (bSave & Mask);
}

uint64_t calculateFitness(uint64_t * P, uint64_t * Pr, uint64_t n, uint64_t * bestThree) {
	uint64_t cumulative = 0;
	uint64_t best0 = UINT64_MAX;
	uint64_t best1 = UINT64_MAX;
	uint64_t best2 = UINT64_MAX;
	bestThree[0] = UINT64_MAX;
	bestThree[1] = UINT64_MAX;
	bestThree[2] = UINT64_MAX;
	for (uint64_t i = 0; i < n; i++) {
		Pr[i] = hammingDistance(target, P[i]);
		cumulative += Pr[i];
		if (Pr[i] < best2) {
			if (Pr[i] < best1) {
				if (Pr[i] < best0) {
					bestThree[2] = bestThree[1];
					bestThree[1] = bestThree[0];
					bestThree[0] = P[i];
					best2 = best1;
					best1 = best0;
					best0 = Pr[i];
				}
				else {
					bestThree[2] = bestThree[1];
					bestThree[1] = P[i];
					best2 = best1;
					best1 = Pr[i];
				}
			}
			else {
				bestThree[2] = P[i];
				best2 = Pr[i];
			}
		}
		if (Pr[i] == 0)
			notHit = i;
	}
	if (best0 < globalBeschde) {
		std::cout << "beschde der Generation: " << std::hex << bestThree[0] << "  Hammingdist: " << std::dec << best0 << std::endl;
		globalBeschde = best0;
	}
	return cumulative;
}

void init(uint64_t * P, uint64_t n) {
	for (uint64_t i = 0; i < n; i++) {
		P[i] = random64();
	}
}

int main() {
	uint64_t * P, * Ps, * Pr, * bestThree;
	uint64_t r(14), popCount(21), mutationRate(2);
	// Population
	P = new uint64_t[popCount];
	// Next Generation
	Ps = new uint64_t[popCount];
	// Fitness of Population
	Pr = new uint64_t[popCount];
	// best three
	bestThree = new uint64_t[3];

	init(P, popCount);
	
	uint64_t cumulativeFitness;
	uint64_t random;
	while (notHit == 0) {
		// besten drei in Ps
		cumulativeFitness = calculateFitness(P, Pr, popCount, Ps);
		// mit hoher wahrscheinlichkeit gute behalten
		for (uint64_t i = 0; i < popCount - r - 3; i++) {
			random = random64() % cumulativeFitness;
			uint64_t increaser = 0;
			uint64_t * current = Pr;
			while ((increaser += *current) < random) {
				++current;
			}
			Ps[i+3] = P[Pr - current];
		}
		// Crossover
		for (uint64_t i = 0; i < r; i++) {
			random = random64() % cumulativeFitness;
			uint64_t increaser = 0;
			uint64_t * current = Pr;
			while ((increaser += *current) < random) {
				++current;
			}
			Ps[popCount - r - 1 + i] = P[Pr - current];
		}
		for (uint64_t i = 0; i < r; i += 2) {
			cross(Ps + popCount - r - 1 + i, Ps + popCount - r + i, rand() % 62);
		}
		// Mutation
		for (uint64_t i = 0; i < mutationRate; i++) {
			Ps[(rand() % (popCount - 3)) + 3] ^= 1i64 << (rand() % 64);
		}
		uint64_t * s = P;
		P = Ps;
		Ps = s;
	}

	std::getchar();
	delete P, Pr, Ps;
	return 0;
}
