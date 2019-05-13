#pragma once
#include <iostream>
#include <vector>

double randomize();

struct NN4Neuron {
	std::vector <double> Weights, dWeights;
	double Sum = 0.0;

	NN4Neuron();
	~NN4Neuron();

	void create(int inputcount); // init the memeory & shit
};

struct NN4Layer {
	std::vector <NN4Neuron> neurons; // neurons[0] = 5 or whatever
	int neuroncount;
	//std::vector <double> layerinput;
	int layercount;

	double Bias, dBias;

	NN4Layer();
	~NN4Layer();

	void create(int inputsize, int _neuroncount);
	void inline calculate(const NN4Layer &in);
};

class ANN {
	void inline feedforward(); // send the inputs forward thru the system to see what their output is
	void inline backprop(); // compare the output to the target, & fix it
	void inline update(); // update the weights & shit // implementation will change depending on system used, GD will be at end, SGD will be for each iteration
public:
	// find a more dynamic way to do this
	std::vector <double> target;
	std::vector <double> output;
	
	NN4Layer inputLayer;
	NN4Layer outputLayer;
	std::vector <NN4Layer> hiddenLayer;
	
	int hiddencount;

	ANN();
	~ANN();

	void create(int inputcount, int inputneurons, int outputcount, int *hiddenlayers, int hiddenlayercount);
	void fit(int epochs); // one epoch essentially
	void predict(); // using the final weights to predict what new input will be
};

std::vector<double> Sums(NN4Layer out);