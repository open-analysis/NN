#pragma once

#include <iostream>
#include "../../input.h"

#define NUMPAT 4
#define NUMIN 3
#define NUMOUT 2
#define NUMHIDDEN 7
#define EPOCH 100
#define MAXDOU .99
#define MINDOU .01

#define rando() ((double)rand()/((double)RAND_MAX+1))

class NN {
private:
	void propagate();
	void train();
	void set();
	double fRand();

	Read read = Read();

	int e, i, j, k, p, np, op, ranpat[NUMPAT];
	double lerr = 0, gerr = 0;
	double /*sumH = 0, sumO = 0,*/ sumHE = 0, sumOE = 0, Error = 0, momentum = .5, alpha = .9;
	double DeltaO[NUMOUT], DeltaWeightHO[NUMHIDDEN][NUMOUT], DeltaH[NUMHIDDEN], DeltaWeightIH[NUMIN][NUMHIDDEN];
	double sumDOW[NUMHIDDEN + 1], sumH[NUMPAT][NUMHIDDEN], sumO[NUMPAT][NUMOUT],/* input[NUMPAT][NUMIN], target[NUMPAT][NUMOUT] ,*/ output[NUMPAT][NUMOUT], hidden[NUMPAT][NUMHIDDEN];
	/*static*/ double WeightIH[NUMIN][NUMHIDDEN], WeightHO[NUMHIDDEN][NUMOUT], BiasH[NUMHIDDEN], BiasO[NUMOUT];
	double target[NUMPAT][NUMOUT] = { { 0, 0 },{ 0, 0 },{ 0, 1 },{ 0, 1 } };
	double input[NUMPAT][NUMIN] = { { 0, 0, 0 },{ 0, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } };

public:
	NN();
};