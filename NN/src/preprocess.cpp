#include "preprocess.h"

Preprocess::Preprocess() {
	vocab.clear();
	alphabet = { 
		"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", 
		"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k","l","m", "n",	"o", "p", "q", "r", "s", "t", "u", "v",	"w", "x", "y", "z",
		".", ",", "!", "?", "-", "_", "$", "\"", "\'", "#", "@", "%", "^", "&", "*", "(", ")", "+", "=", "[", "]", "{", "}", "|", "\\",
		":", ";", "<", ">", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "~", "`"};
}

void Preprocess::getOneHotText(std::vector <std::vector <bool>> &te, int iter) {
	te.resize(text.size());
	for (std::vector <bool> vb : te)
		vb.resize(lexicon.size());
	for (int i = 0; i < text.size(); i++) {
		if (_usingVocab) {
			for (int j = 0; j < vocab.size(); j++)
				if (text[iter] == vocab[j]) {
					te[i][j] = 1;
					continue;
				}
		}
		else {
			for (int j = 0; j < alphabet.size(); j++)
				if (text[iter] == alphabet[j]) {
					te[i][j] = 1;
					continue;
				}
		}
	}
}

void Preprocess::read() {
	// reading in
	f.open(_pathway, std::ios::in | std::ios::beg);
	if (f.is_open()) {
		// use vocab vector
		if (_usingVocab) {
			std::string line;
			std::string index;
			char curr_char;
			// making sure the batch has a set amount, if not using the size size of the file as the batch length (probs not the best idea tbh)
			if (!batch_set) {
				f.seekg(0, std::ios::end);
				fileLength = f.tellg();
				f.seekg(0, std::ios::beg);
				batch_size = fileLength;
				batch_iter = fileLength / batch_size;
				text.resize(batch_iter);
				batch_set = true;
			}
			// read thru the file
			while (!f.eof()) {
				// going thru in the batch sizes
				for (int i = 0; i <= batch_iter; i++) {
					f.seekg(batch_count * batch_size, std::ios::beg);
					while (std::getline(f, line)) {
						if (text.size() == batch_size) {
							batch_count++;
							break;
						}
						text.push_back(line);
						//std::stringstream ss(line);
						//while (std::getline(ss, curr_char, ' ')) 
						for (int i = 0; i < line.size(); i++)
							curr_char = line[i];
						if (curr_char != ',' || curr_char != '.' || curr_char != '!' || curr_char != '?')
							index += curr_char;
						// needs to be the root word (e.g. knowing -> know, gained -> gain)
						// does it? vastly increases lexicon size but having verb tense is useful...
						// there are far too many "special cases" (i.e. fought -> fight & bought -> buy & knew -> know) to bother
#if 0
					// remove "ing"
						if (index[index.back() - 2] == 'i')
							if (index[index.back() - 1] == 'n')
								if (index[index.back()] == 'g') {
									index.pop_back();
									index.pop_back();
									index.pop_back();
								}
						// remove "ed"
						if (index[index.back() - 1] == 'e')
							if (index[index.back()] == 'd') {
								index.pop_back();
								index.pop_back();
							}
#endif
					for (int i = 0; i < dict.size(); i++) {
						if (dict[i] == index) {
							dictCount[i]++;
							index = "";
							break;
						}
					}
					if (index != "") {
						dict.push_back(index);
						dictCount.push_back(1);
						index = "";
					}
					for (int i = 0; i < dict.size(); i++) {
						if (dictCount[i] >= vocab_MIN) {
							if (vocab_MAX != 0) {
								if (dictCount[i] <= vocab_MAX) {
									vocab.push_back(dict[i]);
								}
							}
							else {
								vocab.push_back(dict[i]);
							}
						}
					}
					}
				}
			}
			// setting up the lexicon to use the vocab vector
			lexicon.resize(vocab.size());
			for (std::vector <bool> bo : lexicon) {
				bo.resize(lexicon.size());
				for (bool b : bo)
					b = 0;
			}
			for (int i = 0; i < lexicon.size(); i++) {
				lexicon[i][i] = 1;
			}
		}
		// setting up the lexicon for using the alphabet vector
		else {
			lexicon.resize(alphabet.size());
			for (std::vector <bool> d : lexicon) {
				d.resize(alphabet.size());
				for (bool b : d)
					b = 0;
			}
			for (int i = 0; i < lexicon.size(); i++)
				for (int j = 0; j < lexicon[i].size(); j++)
					lexicon[i][j] = 1;
		}
		f.close();
		// writing out the vocab
		if (_usingVocab) {
			time_t now = time(0);
			tm *time = localtime(&now);
			std::string path = "/vocab/";
#if 0
			path += 1900 + time->tm_year;
			path += "/";
			path += 1 + time->tm_mon;
			path += "/";
			path += time->tm_mday;
			path += "/";
			path += "vocab.txt";
#else
			path += 1900 + time->tm_year;
			path += "-";
			path += 1 + time->tm_mon;
			path += "-";
			path += time->tm_mday;
			path += "-";
			path += "vocab.txt";
#endif
			f.open(path, std::ios::out | std::ios::trunc);
			if (f.is_open()) {
				for (int i = 0; i < vocab.size(); i++) {
					if (10 % i == 0) f << "\n";
					f << vocab[i];
					f << "\t";
				}
				f.close();
			}
		}
		/*		
		dict.clear();
		dict.shrink_to_fit();
		dictCount.clear();
		dictCount.shrink_to_fit();
		vocab.clear();
		vocab.shrink_to_fit();
		alphabet.clear();
		alphabet.shrink_to_fit();
		*/
	}
}