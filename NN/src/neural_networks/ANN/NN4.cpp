#include "NN4.h"

double inline randomize() {
	return .05;
}

// NEURON
NN4Neuron::NN4Neuron(){
	Weights.clear();
	dWeights.clear();
	Sum = 0.0;
}
NN4Neuron::~NN4Neuron() {
	if (!Weights.empty()) {
		Weights.clear();
		delete &Weights; // probably just deletes the first one
	}
	if (!dWeights.empty()) {
		dWeights.clear();
		delete &dWeights;
	}
}

void NN4Neuron::create(int inputcount) {
	Weights.resize(inputcount);
	dWeights.resize(inputcount);
	for (int i = 0; i < inputcount; i++) {
		Weights[i] = randomize();
		dWeights[i] = 0.0;
	}
}

// LAYER 
NN4Layer::NN4Layer() {
	neurons.clear();
	neuroncount = 0;
	Bias = 0.0;
	dBias = 0.0;
//	layerinput.clear();
	layercount = 0;
}
NN4Layer::~NN4Layer() {
	neurons.erase(neurons.begin());/*
	if (!layerinput.empty()) {
		layerinput.clear();
		delete &layerinput;
	}*/
}

void NN4Layer::create(int inputsize, int _neuroncount) {
	neuroncount = _neuroncount;
	layercount = inputsize;
	neurons.resize(neuroncount);
	Bias = randomize();
	dBias = 0.0;
	for (int i = 0; i < neuroncount; i++) {
		neurons.push_back(NN4Neuron());
		neurons[i].create(inputsize);
	}
	//layerinput.resize(inputsize);
}

void NN4Layer::calculate(const NN4Layer &in) {
	int i, j;
	double sum;

	for (i = 0; i < neuroncount; i++) {
		sum = Bias;
		for (j = 0; j < layercount; j++) {
			sum += neurons[i].Weights[j] * in.neurons[j].Sum;
		}
		neurons[i].Sum = 1.0/(1.0 + exp(-sum));
		std::cout << neurons[i].Sum << std::endl;
	}
}


// NEURAL NETWORK
ANN::ANN() {
	hiddencount = 0;
	hiddenLayer.resize(1);
	hiddenLayer.clear();
	target.resize(1);
	target.clear();
}

ANN::~ANN() {
	if (!hiddenLayer.empty()) {
		hiddenLayer.clear();
		delete &hiddenLayer;
	}
	if (!target.empty()) {
		target.clear();
		delete &target;
	}
}

void ANN::create(int inputcount, int inputneurons, int outputcount, int *hiddenlayers, int hiddenlayercount) {
	inputLayer.create(inputcount, inputneurons);
	
	if (hiddenlayers && hiddenlayercount) {
		hiddenLayer.resize(hiddenlayercount);
		hiddencount = hiddenlayercount;
		
		for (int i = 0; i < hiddencount; i++) {
			hiddenLayer.push_back(NN4Layer());

			if (i == 0)
				hiddenLayer.back().create(inputneurons, hiddenlayers[i]);
			else
				hiddenLayer.back().create(hiddenlayers[i - 1], hiddenlayers[i]);
		}
		outputLayer.create(hiddenlayers[hiddenlayercount], outputcount);
	}
	else
		outputLayer.create(inputneurons, inputcount);
}

void ANN::fit(int epochs) {
	for (int e = 0; e < epochs; e++) {
		feedforward();
		backprop();
		update();
	}
}

void ANN::feedforward() {
	// (weight * input) + bias
	// squash w/ sig func
	// using the calculate function
	NN4Layer curr = hiddenLayer.front();
	
	for (int i = 0; i < hiddencount; i++) { // goes thru all of the hidden layers
		
		for (int j = 0; j < curr.layercount; j++) { // goes thru the current HL's inputs
			
			if (i == 0) {
				// input layer
				for (int k = 0; k < inputLayer.neuroncount; k++) { // goes thru all of neurons from the input 
					/*curr.layerinput.swap(m_inputLayer.neurons);
					curr.layerinput.push_back(m_inputLayer);
					curr.layerinput[k] = m_inputLayer.neurons[k];*/
					curr.calculate(inputLayer);
				}
			}

			else if (i == hiddencount+1) {
				// output layer
				for (int k = 0; k < outputLayer.neuroncount; k++) { // goes thru all of neurons from the input 
					curr.calculate(outputLayer);
				}
			}

			else {
				for (int k = 0; k < hiddenLayer[i - 1].neuroncount; k++) { // goes thru all of neurons from the input 
					curr.calculate(hiddenLayer[i - 1]);
				}
			}
		}
		curr = hiddenLayer[i + 1];
	}
	output = Sums(outputLayer);
}
void ANN::backprop() {
	// SGD
	// uses Sums for results
	std::vector <double> err;
	err.resize(target.size());
	for (int i = 0; i < err.size(); i++) {
		err[i] = (target[i] - output[i]) * (target[i] - output[i]) * .5;
	}
}

// unsure of necesity, could just do that in the backprop without having to call another function
void ANN::update() {
	// goes through each weight & bias & updates it

}

void ANN::predict() {

}

std::vector<double> Sums(NN4Layer out) {
	std::vector<double> result;
	result.resize(out.neuroncount);
	for (int i = 0; i < out.neuroncount; i++) 
		result[i] = out.neurons[i].Sum;
	return result;
}