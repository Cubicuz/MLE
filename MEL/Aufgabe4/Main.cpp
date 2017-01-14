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
	//PrimAlgoSearcher PAS(31, 512, 512, 3,	0.5, 0.1);
	//PAS.initGenes();
	PrimAlgoSearcher PAS("../Aufgabe4/PrimAlgoFile4.txt", 3, 0.5, 0.4);
	for (int i = 0; i < 1000; i++) {
		PAS.runAndCalcFitness();
		PAS.selection();
		cout << "best Fittnes " << PAS.getBestFitness() << endl;
		PAS.crossOver();
		PAS.mutation();
		PAS.makeLastGenRandom();
		PAS.swapGenerations();
	}
	cout << "best Fittnes " << PAS.getBestFitness() << endl;


	PAS.saveGenes("../Aufgabe4/PrimAlgoFile4.txt");
	string a;
	cout << "fertig";
	cin >> a;
	return 0;
}