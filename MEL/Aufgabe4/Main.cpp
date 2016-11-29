#include "PrimAlgoSearcher.h"
#include <random>
#include <iostream>
#include <time.h>

using namespace std;


int random32() {
	return (rand() << 16) | rand();
}

int main() {
	srand(time(NULL));
	PrimAlgoSearcher lala(31, 512, 512, 3,	0.5, 0.1);
	lala.initGenes();
	for (int i = 0; i < 1000; i++) {
		lala.runAndCalcFitness();
		lala.selection();
		cout << "Run " << i << " best Fittnes " << lala.getBestFitness() << endl;
		lala.crossOver();
		lala.mutation();
		lala.makeLastGenRandom();
		lala.swapGenerations();
	}


	lala.saveGenes("../Aufgabe4/PrimAlgoFile.txt");
	return 0;
}