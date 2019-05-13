#include "GRUNeuron.h"

GRUNeuron::GRUNeuron() {
	*z = 0.0; 
	*r = 0.0;
	*h = 0.0;
	*s = 0.0;
}

GRUNeuron::~GRUNeuron() {
	delete[] U;
	delete[] W;
	delete[] z;
	delete[] r;
	delete[] h;
	delete[] s;
	input.erase(input.begin());
}

void GRUNeuron::create(int numInputs, std::vector <double> Inputs) {
	// init all the stuff
	input = Inputs;
	for (int i = 0; i < 3; i++) {
		U[i] = .05; // have to properly init this later
		W[i] = .05;
	}
}

void GRUNeuron::create(int numInputs) {
	// init all the stuff
	*z = *r = *h = *s = 0.0;
	input.resize(numInputs);
	for (int i = 0; i < 3; i++) {
		U[i] = weightInit(); 
		W[i] = weightInit();
	}
}

double GRUNeuron::weightInit() {
	std::random_device rd;
	std::normal_distribution <double> dist(-.05, .05);
	return dist(rd);
}