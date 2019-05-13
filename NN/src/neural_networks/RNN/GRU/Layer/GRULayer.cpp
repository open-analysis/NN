#include "GRULayer.h"

GRULayer::GRULayer() {
	neurons.clear();
}

GRULayer::~GRULayer() {
	for (int i = 0; i < neurons.size(); i++)
		neurons[i].~GRUNeuron();

	neurons.erase(neurons.begin());
}

void GRULayer::create(int numNeurons, int numInputs, std::vector <double> inputs) {
	multiNeuron = true;
	neurons.resize(numNeurons);
	for (int i = 0; i < numNeurons; i++) {
		GRUNeuron n = GRUNeuron();
		if (i == 0)
			n.create(numInputs, inputs);
		else
			n.create(numInputs);
		neurons.push_back(n);
	}
}

void GRULayer::create(int numInputs, std::vector <double> inputs) {
	multiNeuron = false;
	_numInputs = numInputs;
	neuron = GRUNeuron();
	neuron.create(numInputs, inputs);
}

void GRULayer::calculate() {
	if (!multiNeuron) {
		for (int t = 0; t < _numInputs; t++) {
			if (t == 0) {
				neuron.z[t] = (neuron.input[t] * neuron.U[0]);
				neuron.z[t] = 1.0 / (1.0 + exp(-neuron.z[t]));

				neuron.r[t] = (neuron.input[t] * neuron.U[1]);
				neuron.r[t] = 1.0 / (1.0 + exp(-neuron.r[t]));

				neuron.h[t] = (neuron.input[t] * neuron.U[2]);
				neuron.h[t] = 1.0 / (1.0 + exp(-neuron.h[t]));
			}
			else {
				neuron.z[t] = (neuron.input[t] * neuron.U[0]) + (neuron.s[t - 1] * neuron.W[0]);
				neuron.z[t] = 1.0 / (1.0 + exp(-neuron.z[t]));

				neuron.r[t] = (neuron.input[t] * neuron.U[1]) + (neuron.s[t - 1] * neuron.W[1]);
				neuron.r[t] = 1.0 / (1.0 + exp(-neuron.r[t]));

				neuron.h[t] = (neuron.input[t] * neuron.U[2]) + ((neuron.s[t - 1] * neuron.r[t]) * neuron.W[2]);
				neuron.h[t] = 1.0 / (1.0 + exp(-neuron.h[t]));
			}
			neuron.s[t] = (1 - neuron.z[t]) * neuron.h[t] + neuron.z[t] * neuron.s[t - 1];
			layerSum += neuron.s[t];
		}
	}
	else {
		for (int n = 0; n < neurons.size(); n++) {
			for (int t = 0; t < _numInputs; t++) {
				if (t == 0) {
					neurons[n].z[t] = (neurons[n].input[t] * neurons[n].U[0]);
					neurons[n].z[t] = 1.0 / (1.0 + exp(-neurons[n].z[t]));

					neurons[n].r[t] = (neurons[n].input[t] * neurons[n].U[1]);
					neurons[n].r[t] = 1.0 / (1.0 + exp(-neurons[n].r[t]));

					neurons[n].h[t] = (neurons[n].input[t] * neurons[n].U[2]);
					neurons[n].h[t] = 1.0 / (1.0 + exp(-neurons[n].h[t]));
				}
				else {
					neurons[n].z[t] = (neurons[n].input[t] * neurons[n].U[0]) + (neurons[n].s[t - 1] * neurons[n].W[0]);
					neurons[n].z[t] = 1.0 / (1.0 + exp(-neurons[n].z[t]));

					neurons[n].r[t] = (neurons[n].input[t] * neurons[n].U[1]) + (neurons[n].s[t - 1] * neurons[n].W[1]);
					neurons[n].r[t] = 1.0 / (1.0 + exp(-neurons[n].r[t]));

					neurons[n].h[t] = (neurons[n].input[t] * neurons[n].U[2]) + ((neurons[n].s[t - 1] * neurons[n].r[t]) * neurons[n].W[2]);
					neurons[n].h[t] = 1.0 / (1.0 + exp(-neurons[n].h[t]));
				}
				neurons[n].s[t] = (1 - neurons[n].z[t]) * neurons[n].h[t] + neurons[n].z[t] * neurons[n].s[t - 1];
				layerSum += neurons[n].s[t];
			}
		}
	}
}

void GRULayer::CE(std::vector <bool> target) {
	if (multiNeuron) {
		for (int t = 0; t < target.size(); t++) {
			errsO.push_back(target[t] - *neurons[t].s);
			neurons[t].W[0] += learningRate * neurons[t].s[t] * errsO[t];
			neurons[t].W[1] = neurons[t].W[0] + learningRate * neurons[t].s[t] * errsO[t];
			neurons[t].W[2] = neurons[t].W[1] + learningRate * neurons[t].s[t] * errsO[t];

			errsH.push_back(*neuron.h * (errorO[t] * neurons[t].W[t]));
			neurons[t].U[0] += learningRate * neurons[t].s[t - 1] * errsH[t];
			neurons[t].U[1] = neurons[t].U[0] + learningRate * neurons[t].s[t - 1] * errsH[t];
			neurons[t].U[2] = neurons[t].U[1] + learningRate * neurons[t].s[t - 1] * errsH[t];
		}
	}
	else {
		for (int t = 1; t < target.size(); t++) {
			errorO[t] += (target[t] - *neuron.s);
			neuron.W[0] += learningRate * neuron.s[t] * errorO[t];
			neuron.W[1] = neuron.W[0] + learningRate * neuron.s[t] * errorO[t];
			neuron.W[2] = neuron.W[1] + learningRate * neuron.s[t] * errorO[t];

			errorH[t] += *neuron.h * (errorO[t] * neuron.W[t]);
			neuron.U[0] += learningRate * neuron.s[t - 1] * errorH[t];
			neuron.U[1] = neuron.U[0] + learningRate * neuron.s[t - 1] * errorH[t];
			neuron.U[2] = neuron.U[1] + learningRate * neuron.s[t - 1] * errorH[t];
		}
	}
}
