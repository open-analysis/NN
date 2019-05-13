#include <iostream>
#include "input.h"


Read::Read() {
	memset(target, 0, sizeof(target));
}


void Read::readFlowers() {
	f.open(loc);
	if (f.is_open()) {
		while (std::getline(f, line)) {
			std::stringstream ss(line);
		//	std::getline(ss, curr_char, ',');
			count = 0;
			while (std::getline(ss, curr_char, ',')) {
				if (curr_char[0] == 'I') {
					if (curr_char == "Iris-setosa") {
						target[arr_count][0] = 1;
						//target[arr_count][1] = 0;
					}
					else if (curr_char == "Iris-versicolor") {
						target[arr_count][0] = -1;
						//target[arr_count][1] = 1;
					}
					/*else if (curr_char == "Iris-virginica") {
						target[arr_count][0] = 1;
						target[arr_count][1] = 1;
					}*/
				}
				else {
					double curr = stod(curr_char);
					inputs[arr_count][count] = curr;
				}
				count++;
			}
/*
			if (curr_char == "1") {
				target[arr_count][2] = 1.0;
				count = 0;
				while (std::getline(ss, curr_char, ',')) {
					double curr = stod(curr_char);
					inputs[arr_count][count] = curr;
					count++;
				}
			}
			else if (curr_char == "2") {
				target[arr_count][1] = 1.0;
				count = 0;
				while (std::getline(ss, curr_char, ',')) {
					double curr = stod(curr_char);
					inputs[arr_count][count] = curr;
					count++;
				}
			}
			else if (curr_char == "3") {
				target[arr_count][0] = 1.0;
				count = 0;
				while (std::getline(ss, curr_char, ',')) {
					double curr = stod(curr_char);
					inputs[arr_count][count] = curr;
					count++;
				}
			} */
			arr_count++;
			/*	if (arr_count == 70 && pos == 2)
			arr_count = 0;
			else if (arr_count == 59 && pos == 1)
			arr_count = 0; */
			/*
			//	int count = 0;
			while (std::getline(ss, curr_char, ',')) {
			double curr = stod(curr_char);
			if (curr == 1) {
			*curr_list = train;
			continue;
			}
			else if (curr == 2) {
			*curr_list = validate;
			continue;
			}
			else if (curr == 3) {
			*curr_list = test;
			continue;
			}
			*curr_list[count] = curr;
			// ADD THE MULTI-DIMENTIONALITY TO THE ARRAYS :)
			*/
		}
	}

	f.close();
}

void Read::read() {
	f.open(loc3);
	if (f.is_open()) {
		while (std::getline(f, line)) {
			std::stringstream ss(line);
			std::getline(ss, curr_char, ',');
			
			if (curr_char == "1") {
				target[arr_count][2] = 1.0;
				count = 0;
				while (std::getline(ss, curr_char, ',')) {
					double curr = stod(curr_char);
					inputs[arr_count][count] = curr;
					count++;
				}
			}
			else if (curr_char == "2") {
				target[arr_count][1] = 1.0;
				count = 0;
				while (std::getline(ss, curr_char, ',')) {
					double curr = stod(curr_char);
					inputs[arr_count][count] = curr;
					count++;
				}
			}
			else if (curr_char == "3") {
				target[arr_count][0] = 1.0;
				count = 0;
				while (std::getline(ss, curr_char, ',')) {
					double curr = stod(curr_char);
					inputs[arr_count][count] = curr;
					count++;
				}
			} 
			arr_count++;
		/*	if (arr_count == 70 && pos == 2)
				arr_count = 0;
			else if (arr_count == 59 && pos == 1)
				arr_count = 0; */
			/* 
			//	int count = 0;
			while (std::getline(ss, curr_char, ',')) {
			double curr = stod(curr_char);
			if (curr == 1) {
			*curr_list = train;
			continue;
			}
			else if (curr == 2) {
			*curr_list = validate;
			continue;
			}
			else if (curr == 3) {
			*curr_list = test;
			continue;
			}
			*curr_list[count] = curr;
			// ADD THE MULTI-DIMENTIONALITY TO THE ARRAYS :)
			*/
		}
	}

	f.close();
}


void Read::readIn() {
	f.open(loc3);
	if (f.is_open()) {
		while (std::getline(f, line)) {
			std::stringstream ss(line);
			std::getline(ss, curr_char, ',');

			if (curr_char == "1") {
				pos = 1;
				count = 0;
				while (std::getline(ss, curr_char, ',')) {
					double curr = stod(curr_char);
					train[arr_count][count] = curr;
					count++;
				}
			}
			else if (curr_char == "2") {
				pos = 2;
				count = 0;
				while (std::getline(ss, curr_char, ',')) {
					double curr = stod(curr_char);
					validate[arr_count][count] = curr;
					count++;
				}
			}
			else if (curr_char == "3") {
				pos = 3;
				count = 0;
				while (std::getline(ss, curr_char, ',')) {
					double curr = stod(curr_char);
					test[arr_count][count] = curr;
					count++;
				}
			}
			arr_count++;
			if (arr_count == 70 && pos == 2) 
				arr_count = 0;
			else if (arr_count == 59 && pos == 1)
				arr_count = 0;
			/*
				//	int count = 0;
				while (std::getline(ss, curr_char, ',')) {
					double curr = stod(curr_char);
					if (curr == 1) {
						*curr_list = train;
						continue;
					}
					else if (curr == 2) {
						*curr_list = validate;
						continue;
					}
					else if (curr == 3) {
						*curr_list = test;
						continue;
					}
					*curr_list[count] = curr;
					// ADD THE MULTI-DIMENTIONALITY TO THE ARRAYS :)
					*/
		}
	}


	f.close();
}

void Read::randomize() {
	int num;
	int last_num = -1;
	double temp[2][13];
	std::memset(temp, 0, sizeof(temp));
	for (int i = 0; i <= 178; i++) {
		num = rand() % 177;
		if (num == last_num)
			num = rand() % 177;
		for (int j = 0; j < 13; j++) {
			temp[0][j] = inputs[num][j];
			inputs[num][j] = inputs[i][j];
			inputs[i][j] = temp[0][j];				
			if (j < 3) {
				temp[1][j] = target[num][j];
				target[num][j] = target[i][j];
				target[i][j] = temp[1][j];
			}
		}
		num = last_num;
	}
}