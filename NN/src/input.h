#pragma once

#include <fstream>
#include <sstream>
#include <string>

static struct Read {
private:
	std::string loc = "C:\\Users\\Josh Chica\\Desktop\\Flowers\\Data.txt";
	std::string loc2 = "C:\\Users\\Josh Chica\\Desktop\\Flowers\\Data2.txt";
	std::string loc3 = "C:\\Users\\Josh Chica\\Desktop\\Wine\\Data.txt";
	std::string loc4 = "C:\\Users\\Josh Chica\\Desktop\\wikidatawiki-20170601-pages-articles-multistream.xml";
	std::ifstream f;
	std::string last_char, line, curr_char;
	int pos, arr_count = 0, count = 0;
	//double **curr_list;

public:
	Read();
	void readIn();
	void read();
	void readFlowers();

	void randomize();

	double train[59][13], validate[71][13], test[48][13];
	double inputs[100][4], target[100][1];

	// temp, sunniness (%), humidity, chance of percipition
	int conditions[7][4] = {
		{ 70, 75, 20, 5 },
		{ 50, 40, 30, 45 },
		{ 55, 20, 2, 70 },
		{ 60, 50, 10, 0 },
		{ 65, 90, 25, 15 },
		{ 50, 40, 40, 60 },
		{ 70, 80, 5, 10 },
	};
	// aye or nay | 1 or -1
	int sport[7][1] = {
		{ 1 },
		{ -1 },
		{ -1 },
		{ 1 },
		{ 1 },
		{ -1 },
		{ 1 }
	};
};