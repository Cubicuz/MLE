#include "PrimAlgoSearcher.h"
using namespace std;


void PrimAlgoSearcher::getBestIndices(int * indices)
{
	for (int i = 0; i < bestToHold; i++) {
		indices[i] = -1;
	}
	for (int i = 0; i < genCount; i++) {
		for (int j = bestToHold - 1; j >= 0; j--) {
			if (indices[j] == -1 || fitnessOfGens[i] > fitnessOfGens[indices[j]]) {
				if (j < bestToHold - 1) {
					indices[j + 1] = indices[j];
					indices[j] = i;
				}
				else {
					indices[j] = i;
				}
			}
			else {
				break;
			}
		}
	}
}

void PrimAlgoSearcher::copyGene(int* from, int* to)
{
	for (int i = 0; i < genSize; i++) {
		to[i] = from[i];
	}
}

PrimAlgoSearcher::PrimAlgoSearcher(int numOfGens,int genSize, int bestToHold, double crossoverRate, double mutationRate)
	: genCount(numOfGens), genSize(genSize), bestToHold(bestToHold), crossoverRate(crossoverRate), mutationRate(mutationRate)
{
	gens = new int *[genCount];
	nextGeneration = new int *[genCount];
	stacks = new int *[genCount];
	fitnessOfGens = new int[genCount];
	for (int i = 0; i < genCount; i++) {
		gens[i] = new int[genSize];
		stacks[i] = new int[stackSize];
		nextGeneration[i] = new int[genSize];
	}
}

PrimAlgoSearcher::PrimAlgoSearcher(string file, int bestToHold, double crossoverRate, double mutationRate)
	: bestToHold(bestToHold), crossoverRate(crossoverRate), mutationRate(mutationRate)
{
	string word;
	ifstream myfile(file);
	if (myfile.is_open()) {
		// Init sizes
		myfile >> word;
		genCount = stoi(word);
		myfile >> word;
		genSize = stoi(word);
		myfile >> word;
		stackSize = stoi(word);

		// Reserve space
		gens = new int *[genCount];
		nextGeneration = new int *[genCount];
		stacks = new int *[genCount];
		fitnessOfGens = new int[genCount];
		for (int i = 0; i < genCount; i++) {
			gens[i] = new int[genSize];
			stacks[i] = new int[stackSize];
			nextGeneration[i] = new int[genSize];

			// Load Values
			for (int j = 0; j < genSize; j++) {
				myfile >> word;
				gens[i][j] = stoi(word);
			}

		}
		myfile.close();
	}
	else {
		cout << "try not to cry but something went horribly wrong" << endl;
		gens = 0;
	}
}


PrimAlgoSearcher::~PrimAlgoSearcher()
{
	if (gens) {
		for (int i = 0; i < genCount; i++) {
			delete[] gens[i];
			delete[] stacks[i];
			delete[] nextGeneration[i];
		}
		delete[] gens;
		delete[] nextGeneration;
		delete[] stacks;
		delete[] fitnessOfGens;
	}
}

int PrimAlgoSearcher::random32()
{
	return (rand() << 16) | rand();
}

// the worst Fitness is 1, the best Fitnes would be int.MAX, this is important for the beginning and keeping the gens heterogeneous
void PrimAlgoSearcher::runAndCalcFitness()
{
	sumOfAllFitness = 0;
	for (int i = 0; i < genCount; i++) {
		VM vm(gens[i], genSize, stacks[i], stackSize);
		vm.simulate();
		fitnessOfGens[i] = vm.getPrimes() + 1;
		sumOfAllFitness += fitnessOfGens[i];
	}
}

void PrimAlgoSearcher::crossOver(int * genA, int * genB)
{
	int position = (rand() % (genSize - 2)) + 1;
	int s;
	for (int i = 0; i < position; i++) {
		s = genA[i];
		genA[i] = genB[i];
		genB[i] = s;
	}
}

void PrimAlgoSearcher::mutation(int * gen)
{
	int index = rand() % genSize;
	gen[index] = random32();
}

void PrimAlgoSearcher::selection()
{
	int r = 0;
	for (int i = bestToHold; i < genCount; i++) {
		r = random32();
		r = r % sumOfAllFitness;
		int j = 0;
		r -= fitnessOfGens[j];
		while (j < genCount && r >= 0) {
			genCount++;
			r -= fitnessOfGens[j];
		}
		copyGene(gens[j], nextGeneration[i]);
	}
}

void PrimAlgoSearcher::swapGenerations()
{
	int ** s = gens;
	gens = nextGeneration;
	nextGeneration = gens;
}

void PrimAlgoSearcher::initGenes()
{
	for (int i = 0; i < genCount; i++) {
		for (int j = 0; j < genSize; j++) {
			gens[i][j] = random32();
		}
	}
}

void PrimAlgoSearcher::saveGenes(string file)
{
	ofstream myfile;
	myfile.open(file, ios::out);
	if (myfile.is_open()) {
		myfile << genCount << " ";
		myfile << genSize << " ";
		myfile << stackSize << endl;
		for (int i = 0; i < genCount; i++) {
			for (int j = 0; j < genSize; j++) {
				myfile << gens[i][j] << " ";
			}
			myfile << endl;
		}
		myfile.close();
	}
}

