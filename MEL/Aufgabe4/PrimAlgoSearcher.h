#pragma once
#include "VM.h"
#include <random>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class PrimAlgoSearcher
{
private:

	int genCount, genSize, stackSize, bestToHold;
	double crossoverRate, mutationRate;

	// array of programm memories
	int ** gens;
	int ** nextGeneration;
	int ** stacks;
	int * fitnessOfGens;
	int * bestIndices;
	void getBestIndices(int * indices);
	int sumOfAllFitness, currentBestFitnes = 0;
	void copyGene(int* from, int* to);
	void crossOverTwoGens(int * genA, int * genB);
	void mutateSingleGen(int * gen);
public:
	PrimAlgoSearcher(int numOfGens = 20, int genSize = 1024, int stackSize = 1024, int bestToHold = 3, double crossoverRate = 0.5, double mutationRate = 0.1);
	PrimAlgoSearcher(string file, int bestToHold = 3, double crossoverRate = 0.5, double mutationRate = 0.1);
	~PrimAlgoSearcher();
	int random32();
	void runAndCalcFitness();
	void crossOver();
	void mutation();
	void selection();
	void swapGenerations();
	void initGenes();
	int getBestFitness();
	void saveGenes(string file);
};

