#pragma once

//#include <iostream>
#include <vector>

struct Neuron {
	double U, V, *W; // U = last; B = bias; W = weights
	double sum, output;

	Neuron();
	~Neuron();
};

struct Layer {
	std::vector <Neuron> neuron;

	Layer();
	~Layer();

	void calculate();
};

class RNN {
public:
};