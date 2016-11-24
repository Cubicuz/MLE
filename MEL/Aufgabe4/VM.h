#pragma once
#include <vector>

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
private:
	int32_t * mem = 0;
	int32_t * stack = 0;
	int32_t pc, sp, reg, cycles;
	std::vector<int32_t> primes;

public: 
	const int32_t MAX = 1024;
	const int32_t MaxCycles = 100000;

	

	VM(int32_t * memory, int32_t * stack) : pc(0), sp(0), reg(0), cycles(0) {


	}
	~VM() {
	}
	void push(int32_t x) {
		stack[sp++] = x;
		if (isPrime(x)) {
			
		}
	}

	bool isPrime(int32_t elem) {
		//check if elem is a multiple of 2
		if (elem % 2 == 0) return false;
		//if not, then just check the odds
		for (int i = 3; i * i <= elem; i += 2) {
			if (elem % i == 0)
				return false;
		}
		return true;
	}

	int32_t pop() {
		if (sp >= 1)
			sp--;
		return stack[sp];
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
				int32_t d = pop(); 
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
					pc = (pc + pop()) % MAX; 
				} else { 
					pc++; 
				} 
				break; 
			}
			}
		} while (pc<MAX && sp >= 0 && cycles < MaxCycles && sp < MAX);
	}
};
