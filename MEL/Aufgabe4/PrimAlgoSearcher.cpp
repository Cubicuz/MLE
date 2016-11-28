#include "PrimAlgoSearcher.h"
using namespace std;


void PrimAlgoSearcher::getBestIndices()
{
	for (int i = 0; i < bestToHold; i++) {
		bestIndices[i] = -1;
	}
	for (int i = 0; i < genCount; i++) {
		for (int j = bestToHold - 1; j >= 0; j--) {
			if (bestIndices[j] == -1 || fitnessOfGens[i] > fitnessOfGens[bestIndices[j]]) {
				if (j < bestToHold - 1) {
					bestIndices[j + 1] = bestIndices[j];
					bestIndices[j] = i;
				}
				else {
					bestIndices[j] = i;
				}
			}
			else {
				break;
			}
		}
	}
	currentBestFitnes = fitnessOfGens[bestIndices[0]];
}

PrimAlgoSearcher::PrimAlgoSearcher(int genCount,int genSize, int stackSize, int bestToHold, double crossoverRate, double mutationRate)
	: genCount(genCount), genSize(genSize), stackSize(stackSize), bestToHold(bestToHold), crossoverRate(crossoverRate), mutationRate(mutationRate)
{
	gens.resize(genCount);
	nextGeneration.resize(genCount);
	stacks.resize(genCount);
	fitnessOfGens.resize(genCount);
	bestIndices.resize(bestToHold);
	for (int i = 0; i < genCount; i++) {
		gens[i].resize(genSize);
		stacks[i].resize(stackSize);
		nextGeneration[i].resize(genSize);
	}
}

PrimAlgoSearcher::PrimAlgoSearcher(string file, int bestToHold, double crossoverRate, double mutationRate)
	: bestToHold(bestToHold), crossoverRate(crossoverRate), mutationRate(mutationRate)
{
	string word;
	ifstream myfile(file);
	if (myfile.is_open()) {
		// Init sizes
		myfile >> genCount;

		myfile >> genSize;

		myfile >> stackSize;


		// Reserve space
		gens.resize(genCount);
		nextGeneration.resize(genCount);
		stacks.resize(genCount);
		fitnessOfGens.resize(genCount);
		bestIndices.resize(bestToHold);
		for (int i = 0; i < genCount; i++) {
			gens[i].resize(genSize);
			stacks[i].resize(stackSize);
			nextGeneration[i].resize(genSize);

			// Load Values
			for (int j = 0; j < genSize; j++) {
				myfile >> gens[i][j];
			}

		}
		myfile.close();
	}
	else {
		cout << "File could not be read" << endl;
	}
}


PrimAlgoSearcher::~PrimAlgoSearcher()
{
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
		for (int j = 0; j < stackSize; j++) {
			stacks[i][j] = 0;
		}
		VM vm(gens[i], genSize, stacks[i], stackSize);
		vm.simulate();
		fitnessOfGens[i] = vm.getPrimes() + 1;
		sumOfAllFitness += fitnessOfGens[i];
	}
	getBestIndices();
}

void PrimAlgoSearcher::crossOver()
{
	for (int i = bestToHold; i < genCount*crossoverRate; i+=2) {
		crossOverTwoGens(i,i + 1);
	}
}

void PrimAlgoSearcher::mutation()
{
	int index;
	for (int i = 0; i < genCount*mutationRate; i++) {
		index = (rand() % (genCount - bestToHold)) + bestToHold;
		mutateSingleGen(index);
	}
}

void PrimAlgoSearcher::crossOverTwoGens(int genAIndex, int genBIndex)
{
	int position = (rand() % (genSize - 2)) + 1;
	int s;
	for (int i = 0; i < position; i++) {
		s = nextGeneration[genAIndex][i];
		nextGeneration[genAIndex][i] = nextGeneration[genBIndex][i];
		nextGeneration[genBIndex][i] = s;
	}
}

void PrimAlgoSearcher::mutateSingleGen(int genIndex)
{
	int index = rand() % genSize;
	nextGeneration[genIndex][index] = random32();
}

void PrimAlgoSearcher::selection()
{
	getBestIndices();
	// keep the best
	for (int i = 0; i < bestToHold; i++) {
		//copyGene(gens[bestIndices[i]], nextGeneration[i]);
		nextGeneration[i] = gens[bestIndices[i]];
	}
	// select with fitness in Probability
	int r = 0;
	int j = 0;
	for (int i = bestToHold; i < genCount; i++) {
		r = random32();
		r = r % sumOfAllFitness;
		j = 0;
		r -= fitnessOfGens[j];
		while (j < (genCount - 1) && r >= 0) {
			j++;
			r -= fitnessOfGens[j];
		}
		//copyGene(gens[j], nextGeneration[i]);
		nextGeneration[i] = gens[j];
	}
}

void PrimAlgoSearcher::swapGenerations()
{
	gens.swap(nextGeneration);
}

void PrimAlgoSearcher::initGenes()
{
	for (int i = 0; i < genCount; i++) {
		for (int j = 0; j < genSize; j++) {
			gens[i][j] = random32();
		}
	}
}

int PrimAlgoSearcher::getBestFitness()
{

	return currentBestFitnes;
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

