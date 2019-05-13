#pragma once

#include <vector>
#include "../Neuron/GRUNeuron.h"

struct GRULayer {
	std::vector <GRUNeuron> neurons;
	std::vector <double> errsO;
	std::vector <double> errsH;

	double learningRate = 0.01;

	// v is probably useless
	bool multiNeuron;
	GRUNeuron neuron;
	std::vector <double> errorO;
	std::vector <double> errorH;

	int _numInputs;
	double layerSum = 0.0;

	GRULayer();
	~GRULayer();

	void create(int numNeurons, int numInputs, std::vector <double> inputs);
	void create(int numInputs, std::vector <double> inputs);

	void calculate();
	// void calculate2();

	void CE(std::vector <bool> target);
};