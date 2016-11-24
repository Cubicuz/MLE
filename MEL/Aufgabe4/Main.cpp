#include "PrimAlgoSearcher.h"
#include <random>
#include <iostream>
using namespace std;


int random32() {
	return (rand() << 16) | rand();
}

int main() {
	PrimAlgoSearcher lala("../Aufgabe4/PrimAlgoFile.txt");
	lala.saveGenes("../Aufgabe4/PrimAlgoFile.txt");
	getchar();
	return 0;
}