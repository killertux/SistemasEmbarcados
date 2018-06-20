#include "ThreadCalculations.h"

unsigned int factorial(unsigned int n) {
	int i;
	unsigned int retval = 1;
	for (i = n; i > 1; --i)
		retval *= i;
	return retval;
}

void calculateThreadA(float *p) {
	long i, sum = 0;
	for (i = 1; i <= 256; i++) {
		(*p) = i / 256.0;
		sum += (i + (i + 2));
	}
}

void calculateThreadB(float *p) {
	long i, sum = 0;
	for (i = 1; i <= 16; i++) {
		(*p) = i / 16.0;
		sum += pow(2, i) / factorial(i);
	}
}

void calculateThreadC(float *p) {
	long i, sum = 0;
	for (i = 1; i <= 72; i++) {
		(*p) = i / 72.0;
		sum += (i + 1) / i;
	}
}

void calculateThreadD(float *p) {
	long i, sum = 0;
	for (i = 3; i <= 9; i += 2) {
		(*p) = i / 9.0;
		sum += 5 / factorial(i);
	}
}

void calculateThreadE(float *p) {
	long i, sum = 0;
	for (i = 1; i <= 100; i++) {
		(*p) = i / 100.0;
		sum += i * pow(PI, 2);
	}
}

void calculateThreadF(float *p) {
	long i, sum = 0;
	for (i = 1; i <= 128; i++) {
		(*p) = i / 128.0;
		sum += pow(i, 3) / pow(2, i);
	}
}
