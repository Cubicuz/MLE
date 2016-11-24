#pragma once
#include "VM.h"
#include <random>
#include <memory>
class PrimAlgoSearcher
{
private:
	VM vm;
	int32_t numberOfGens;

	// array of programm memories
	int32_t ** gens;
	int32_t ** nextGeneration;
	int32_t ** stacks;
	int32_t * fitnessOfGens;
public:
	PrimAlgoSearcher(int numOfGens = 20);
	~PrimAlgoSearcher();
	int32_t random32();


	int32_t countPrimesInStack(int32_t * stack);
	void runAndCalcFitness();
	void crossOver(int32_t * genA, int32_t * genB);
	void mutation(int32_t * gen);
	void selection();

};

