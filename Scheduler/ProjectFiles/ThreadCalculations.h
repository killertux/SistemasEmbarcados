#ifndef MATH_CALCULATIONS_H
#define MATH_CALCULATIONS_H

#include <math.h>

#define PI 3.1415926

unsigned int factorial(unsigned int n);

void calculateThreadA(float *p);
void calculateThreadB(float *p);
void calculateThreadC(float *p);
void calculateThreadD(float *p);
void calculateThreadE(float *p);
void calculateThreadF(float *p);

#endif
