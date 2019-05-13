#include "GRU.h"

// NN
GRU::GRU() {
	_layers.clear();
}

GRU::~GRU() {
	for (int i = 0; i < _layers.size(); i++)
		_layers[i].~GRULayer();
	_layers.erase(_layers.begin());
}

void GRU::create(int numLayers, int numNeurons, int numInputs, std::vector <double> inputs) {
	_layers.resize(numLayers);
	for (int i = 0; i < _layers.size(); i++) {
		GRULayer l = GRULayer();
		l.create(numNeurons, numInputs, inputs);
		_layers.push_back(l);
	}
	batch_size = _layers.size();
}

void GRU::create(int numLayers, int numInputs, std::vector <double> inputs) {
	_layers.resize(numLayers);
	for (int i = 0; i < _layers.size(); i++) {
		GRULayer l = GRULayer();
		l.create(numInputs, inputs);
		_layers.push_back(l);
	}
	batch_size = _layers.size();
}

void inline GRU::setText() {
	pp.getText(_text, batch_iter);
	_target = _text;
	for (auto t : _target)
		lexSize = t.size();
}

void GRU::setBatchSize() {
	batch_size = pp.getBatchSize();
	batch_count = _target.size() / batch_size;
}

void GRU::train(double error_threshold, int num_epochs) {
	std::vector <double> tmp;
	tmp.resize(_target.size());
	for (int epoch = 0; epoch <= num_epochs; epoch++) {
		// What this needs to do is read one word/character, then predict the next
		// then it'll look at what the next one actually is and do the stuff already implemented
		// is that not done through the layer.calculate() ?
		setText();
		// propagate
		predictNext();
		/*for (GRULayer lay : _layers) 
			lay.calculate();
		*/
		// bp
		for (int i = 0; i < _layers.size(); i++)
			_layers[i].CE(_target[i]);
		for (GRULayer lay : _layers) {
			if (lay.multiNeuron) {
				for (double err : lay.errorO) {
					errorTotal += err;
				}
			}
			else{
				for (double err : lay.errsO) {
					errorTotal += err;
				}
			}
		}
		std::cout << "=================================================\n";
		std::cout << "Epoch: " << epoch << "\n" << "Error: " << errorTotal << "\n";
		std::cout << "=================================================\n";
		if (errorTotal < error_threshold) { 
			printf("\n\nError Under Threshold! Holy SHit\n\n");
			break; 
		}
		batch_iter++;
	}
}

void GRU::shuffle(std::vector <std::vector <double>> &input) {
	int num;
	std::vector <std::vector <double>> tmp;
	std::random_device rd;
	std::uniform_int_distribution <int> dist(0, input.size());
	tmp.resize(input.size());
	for (int i = 0; i < input.size(); i++) {
		num = dist(rd);
		tmp.push_back(input[i]);
	}
	input.swap(tmp);
}

std::string GRU::generate(int length) {
	std::vector <std::vector <bool>> tmp;
	std::vector <std::string> vocab;
	std::string result;
	if (pp.getUsingLexicon()) {
		vocab = pp.getVocab();
		int loc = 0;
		for (int i = 0; i < length; i++) {
			tmp[i] = predictNext();
			for (int j = 0; j < tmp[i].size(); j++) {
				if (j == 0) continue;
				if (tmp[i][j] == 0) continue;
				else {
					loc = j;
					break;
				}
			}
			result += vocab[loc];
		}
	}
	else {
		vocab = pp.getAlphabet();
		int loc = 0;
		for (int i = 0; i < length; i++) {
			tmp[i] = predictNext();
			for (int j = 0; j < tmp[i].size(); j++) {
				if (j == 0) continue;
				if (tmp[i][j] == 0) continue;
				else {
					loc = j;
					break;
				}
			}
			result += vocab[loc];
		}
	}
	return result;
}

std::vector <bool> GRU::predictNext() {
	std::vector <double> tmp;
	std::vector <bool> result;
	tmp.resize(lexSize);
	result.resize(tmp.size());
	int mostConfident = 0;
	int i = 0;
	for (GRULayer la : _layers) {
		la.calculate();
		tmp[i] = la.layerSum;
		i++;
	}
	/*for (int i = 0; i < tmp.size(); i++)
		std::cout << tmp[i] << std::endl; */
	for (int i = 1; i < tmp.size(); i++) 
		if (tmp[mostConfident] < tmp[i]) mostConfident = i;
	for (bool b : result) b = 0;
	result.at(mostConfident) = 1;
	tmp.erase(tmp.begin());
	return result;
}