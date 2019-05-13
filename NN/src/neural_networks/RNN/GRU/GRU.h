#pragma once

#include <iostream>
#include <vector>
#include "Layer\GRULayer.h"
#include "../../../preprocess.h"
#include "../../../input.h"

class GRU {
	Preprocess pp;
	std::vector <GRULayer> _layers;
	// first vector is the size of the sentence & the second/inner vector is the size of the lexicon that's being used
	std::vector <std::vector <bool>> _text;
	// the whole point of this is guessing the next word/character thus target is really just text at one index greater
	std::vector <std::vector<bool>> _target;

	int lexSize = 0;

	int batch_size;
	int batch_count;
	int batch_iter = 0;
	
	double errorTotal;
	
	void setText();
	std::vector <bool> predictNext();
public:
	// the number of layers is defined by the number of elements in the lexicon
	void create(int numLayers, int numNeurons, int numInputs, std::vector <double> inputs);
	void create(int numLayers, int numInputs, std::vector <double> inputs);

	void train(double error_threshold, int num_epochs);

	void setBatchSize();

	void shuffle(std::vector <std::vector <double>> &input);

	std::string generate(int length);

	GRU();
	~GRU();
};