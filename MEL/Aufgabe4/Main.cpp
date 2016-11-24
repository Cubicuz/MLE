#include "VM.h"
#include <random>

#define NumberOfGenes 21


int random32() {
	return (rand() << 16) | rand();
}

int main() {
	VM vm = VM();
	int ** memories = new int *[NumberOfGenes];
	for (int i = 0; i < NumberOfGenes; i++) {
		memories[i] = new int[vm.MAX];
		for (int j = 0; j < vm.MAX; j++) {
			memories[i][j] = random32();
		}
	}
	return 0;
}