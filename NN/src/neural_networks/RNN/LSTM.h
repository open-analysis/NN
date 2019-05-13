#pragma once

#pragma once

//#include <iostream>
#include <vector>

struct Neuron {
	double i, f, o, g, c, s;
	double U[4], W[4];

	Neuron();
	~Neuron();
};

struct Layer {
	std::vector <Neuron> neuron;

	Layer();
	~Layer();

	void calculate();
};

class LSTM {

};