#pragma once

#include <string>

// neuron
struct Neuron{
public:
	double *weights, *dweights, gain, wgain;
	double output;

	void create(int inputcount);
};

// layer
class Layer {
public:
	Neuron **neurons;
	int neuroncount;
	double *layerinput;
	int inputcount;

	void create(int inputsize, int _neuroncount);
	void calculate();
};

// ANN
class NN {
private:
	Layer m_inputlayer;//input layer of the network
	Layer m_outputlayer;//output layer..contains the result of applying the network
	Layer **m_hiddenlayers;//Additional hidden layers
	int m_hiddenlayercount;//the count of additional hidden layers

public:
			 //Creates the network structure on memory
	void create(int inputcount, int inputneurons, int outputcount, int *hiddenlayers, int hiddenlayercount);

	void propagate(const float *input);//Calculates the network values given an input pattern
									   //Updates the weight values of the network given a desired output and applying the backpropagation
									   //Algorithm
	float train(const float *desiredoutput, const float *input, float alpha, float momentum);

	//Updates the next layer input values
	void update(int layerindex);

	//Returns the output layer..this is useful to get the output values of the network
	Layer &amp; Layer getOutput()
	{
		return m_outputlayer;
	}

};