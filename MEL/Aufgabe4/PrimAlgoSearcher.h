#pragma once
#include "VM.h"
#include <random>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


class PrimAlgoSearcher
{
private:
	// shuld be const but then problem with loading from file
	int genCount, genSize, stackSize, bestToHold;
	double crossoverRate, mutationRate;

	// var
	int sumOfAllFitness, currentBestFitnes = 0;

	// array of programm memories
	std::vector<std::vector<int>> gens;
	std::vector<std::vector<int>> nextGeneration;
	std::vector<std::vector<int>>  stacks;
	std::vector<int> fitnessOfGens;
	std::vector<int> bestIndices;

	void getBestIndices();
	void crossOverTwoGens(int genAIndex, int genBIndex);
	void mutateSingleGen(int genIndex);
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

