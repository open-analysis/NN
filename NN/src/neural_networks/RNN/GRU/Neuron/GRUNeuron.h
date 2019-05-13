#pragma once

#include <random>
#include <vector>

struct GRUNeuron {
	double *z, *r, *h, *s;
	std::vector <double> input;
	double U[3], W[3];

	void create(int numInputs, std::vector <double> Inputs);
	void create(int numInputs);

	double weightInit();

	GRUNeuron();
	~GRUNeuron();
};