#pragma once
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

#define byte __int8
#define LOAD  0 // Reg = #1234
#define PUSH  1 // push(Reg)
#define POP  2 // Reg = pop()
#define MUL  3 // Reg = reg*pop()
#define DIV  4 // Reg = Reg/pop()
#define ADD  5 // Reg = Reg+pop()
#define SUB  6 // Reg = Reg-pop()
#define JIH  7 // if Reg>0 then pc = pc + pop()


class VM {

public:

	const int MaxCycles = 100000;



	VM(int * memory, int memorySize, int * stack, int stackSize) : mem(memory), memSize(memorySize), stack(stack), stackSize(stackSize) {
		primes.reserve(100);

		

#ifdef _DEBUG
		for (int i = 0; i < stackSize; i++) {
			stack[i] = 0;
		}
#endif

	}

	~VM() {
	}

	void simulate() {
		pc = 0;	sp = 0;	reg = 0; cycles = 0;
		do {
			cycles++;
			switch (mem[pc] & 7) {
			case LOAD: {
				reg = mem[pc] >> 3;
				push(reg);
				pc++;
				break;
			}
			case PUSH: {
				push(reg);
				pc++;
				break;
			}
			case POP: {
				reg = pop();
				pc++;
				break;
			}
			case MUL: {
				reg = reg*pop();
				pc++;
				break;
			}
			case DIV: {
				int d = pop();
				if (d != 0) {
					reg = (reg / d);
					push(reg);
				}
				pc++;
				break;
			}
			case ADD: {
				reg = reg + pop();
				pc++;
				break;
			}
			case SUB: {
				reg = reg - pop();
				pc++;
				break;
			}
			case JIH: {
				if (reg>0) {
					pc = (pc + pop()) % memSize;
				}
				else {
					pc++;
				}
				break;
			}
			}
		} while (pc<memSize && sp >= 0 && cycles < MaxCycles && sp < stackSize);
	}

	int getPrimes() {
		std::set<int> seen;
		for (size_t i = 0; i < primes.size(); i++) {
			seen.insert(primes[i]);
		}
		return seen.size();
	}
private:
	std::vector<int> primes;
	int * mem;
	int * stack;
	int pc, sp, reg, cycles, memSize, stackSize;
	

	void push(int x) {
		if (sp < stackSize) {
			stack[sp++] = x;
			if (isPrime(x)) {
				primes.push_back(x);
			}
		}
		else {
			std::cout << "wtf" << std::endl;
		}
	}



	bool isPrime(int elem) {
		//check if elem is a multiple of 2
		if (elem % 2 == 0) return false;
		//if not, then just check the odds
		for (int i = 3; i * i <= elem; i += 2) {
			if (elem % i == 0)
				return false;
		}
		return true;
	}

	int pop() {
		if (sp >= 1)
			sp--;
		return stack[sp];
	}

};
