#pragma once

#include "../../input.h"
#include <iostream>

#define SETS 10
#define NUMIN 4
#define NUMOUT 1
#define NUMHID 2
#define EPOCH 100
#define ETA .4
#define LR -.05

struct N {
private:
	Read read = Read();
	int e, i, j, k;
	//double const eta = -.5, lr = .01;
	double TError = 0.0;
	double Input[SETS][NUMIN], Target[SETS][NUMOUT], Output[SETS][NUMOUT], Hidden[SETS][NUMHID];
	double WeightIH[NUMIN][NUMHID], WeightHO[NUMHID][NUMOUT], DeltaWeightIH[NUMIN][NUMHID], DeltaWeightHO[NUMHID][NUMOUT];
	double BiasH[NUMHID], BiasO[NUMOUT], DeltaBiasH[NUMHID], DeltaBiasO[NUMOUT], SumH[SETS][NUMHID], SumO[SETS][NUMOUT]; // shoud the sums be multi arrays?
	double DeltaH[NUMHID], DeltaO[NUMOUT], SumDOW[NUMHID], Error[SETS];

	void propagate();
	void train();
	void set();
public:
	N();

//	int inline getNumIn() { return NUMIN; }
//	int inline getNumOut() { return NUMOUT; }
};