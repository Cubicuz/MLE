#include "PrimAlgoSearcher.h"
using namespace std;


PrimAlgoSearcher::PrimAlgoSearcher(int32_t numOfGens)
{
	numberOfGens = numOfGens;
	
	gens = new int32_t *[numOfGens];
	nextGeneration = new int32_t *[numOfGens];
	stacks = new int32_t *[numOfGens];
	fitnessOfGens = new int32_t[numOfGens];
	for (int32_t i = 0; i < numOfGens; i++) {
		gens[i] = new int32_t[vm.MAX];
		stacks[i] = new int32_t[vm.MAX];
		nextGeneration[i] = new int32_t[vm.MAX];
	}
}


PrimAlgoSearcher::~PrimAlgoSearcher()
{
	for (int i = 0; i < numberOfGens; i++) {
		delete[] gens[i];
		delete[] stacks[i];
		delete[] nextGeneration[i];
	}
	delete[] gens;
	delete[] nextGeneration;
	delete[] stacks;
	delete[] fitnessOfGens;
}

int PrimAlgoSearcher::random32()
{
	return (rand() << 16) | rand();
}

void PrimAlgoSearcher::runAndCalcFitness()
{
	for (int i = 0; i < numberOfGens; i++) {
		vm.mem = gens[i];
		vm.stack = stacks[i];
		vm.simulate();
	}
	//todo Calculate Fitness
}

void PrimAlgoSearcher::crossOver(int32_t * genA, int32_t * genB)
{
	int32_t position = (rand() % (vm.MAX - 2)) + 1;
	int32_t s;
	for (int32_t i = 0; i < position; i++) {
		s = genA[i];
		genA[i] = genB[i];
		genB[i] = s;
	}
}

void PrimAlgoSearcher::mutation(int32_t * gen)
{
	int32_t index = rand() % vm.MAX;
	gen[index] = random32();
}

void PrimAlgoSearcher::selection()
{

}
