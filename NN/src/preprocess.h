#pragma once

#define _CRT_SECURE_NO_WARNINGS

//#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>
#include "input.h"
#include <iostream>

static class Preprocess {
	std::vector <std::string> text;
	std::vector <std::string> dict;
	std::vector <int> dictCount;
	std::vector <std::string> vocab;
	std::vector <std::string> alphabet; // a b c d e f g h i j k l m n o p q r s t u v w x y z
	// one-hot array
	std::vector <std::vector <bool>> lexicon;
	bool _usingVocab = false;

	int fileLength = 0;

	int vocab_MIN = 500;
	int vocab_MAX = 0;

	std::fstream f;
	std::string _pathway;

	int batch_size;
	int batch_iter = 0;
	int batch_count = 0;
	bool batch_set = false;
	
	void getOneHotText(std::vector <std::vector <bool>> &te, int iter);
public:
	Preprocess();
												// v get rid of this
	void setUseVocab(bool f) { _usingVocab = f; }
	void setBatchSize(int size) { batch_size = size; batch_set = true; }
	void setText(std::string path) { _pathway = path; }
	void setVocabMin(int min) { vocab_MIN = min; }
	void setVocabMax(int max) { vocab_MAX = max; }

	bool getUsingLexicon() { return _usingVocab; }
	std::vector <std::vector <bool>> getLexicon() { return lexicon; }
	std::vector <std::string> getAlphabet() { return alphabet; }
	std::vector <std::string> getVocab() { return vocab; }
	void getText(std::vector <std::vector <bool>> &te, int iter) {getOneHotText(te, iter); }
	int getBatchSize() { return batch_size; }
	bool getBatchSet() { return batch_set; }

	void read();
};