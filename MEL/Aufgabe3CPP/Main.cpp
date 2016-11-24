#include <iostream>
#include <iomanip>
#include <random>

#pragma region statics
	static uint64_t notHit = 0;
	static uint64_t target = 0xFEDCBA9876543210;
	static uint64_t globalBeschde = UINT64_MAX;
#pragma endregion
	

int GenerateGenAndOptimize();

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
	uint64_t Mask = ((1 << (position + 1)) - 1);
	uint64_t aSave = *genA;
	uint64_t bSave = *genB;
	*genA = ((uint64_t) (aSave & Mask)) | ((uint64_t) (bSave & ~Mask));
	*genB = ((uint64_t) (aSave & ~Mask)) | ((uint64_t) (bSave & Mask));
}

// Calculate Fitnes and save the best three in bestThree
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
		std::cout << "beschde der Generation: " << std::setfill('0') << std::setw(16) << std::hex << bestThree[0] << "  Hammingdist: " << std::dec << best0 << std::endl;
		globalBeschde = best0;
	}
	return cumulative;
}

// init random Genes
void init(uint64_t * P, uint64_t n) {
	for (uint64_t i = 0; i < n; i++) {
		P[i] = random64();
	}
}

int main() {
	int rounds = 50;
	uint64_t totalGens = 0;
	int * GenCounts = new int [rounds];
	for (int i = 0; i < rounds; i++) {
		GenCounts[i] = GenerateGenAndOptimize();
		totalGens += GenCounts[i];
	}
	system("CLS");
	std::cout << std::dec;
	std::cout << "average Generations neccesarry: " << totalGens / rounds << std::endl;
	std::cout << "total Gens: " << totalGens << std::endl;
	std::getchar();
	return 0;
}

int GenerateGenAndOptimize() {
	srand((unsigned) time(0));
	target = random64();
	std::cout << "Target: " << std::setfill('0') << std::setw(16) << std::hex << target << std::endl;
	uint64_t * P, * Ps, * Pr, * bestThree;
	uint64_t r(4), popCount(21), mutationRate(13);
	// Population
	P = new uint64_t[popCount];
	// Next Generation
	Ps = new uint64_t[popCount];
	// Fitness of Population
	Pr = new uint64_t[popCount];
	// best three
	bestThree = new uint64_t[3];

	init(P, popCount);
	int64_t countGenerations = 0;
	uint64_t cumulativeFitness;
	uint64_t random;
	notHit = 0;
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
			Ps[i+3] = P[current - Pr];
		}
		// Crossover
		for (uint64_t i = 0; i < r; i++) {
			random = random64() % cumulativeFitness;
			uint64_t increaser = 0;
			uint64_t * current = Pr;
			while ((increaser += *current) < random) {
				++current;
			}
			Ps[popCount - r + i] = P[current - Pr];
		}
		for (uint64_t i = 0; i < r; i += 2) {
			cross(Ps + popCount - r + i, Ps + popCount - r + i + 1, rand() % 63);
		}
		// Mutation
		for (uint64_t i = 0; i < mutationRate; i++) {
			Ps[(rand() % (popCount - 3)) + 3] ^= 1i64 << (rand() % 64);
		}
		uint64_t * s = P;
		P = Ps;
		Ps = s;
		countGenerations++;
	}
	std::cout << "Generationen: " << countGenerations << std::endl;
	delete P, Pr, Ps;
	return countGenerations;
}
