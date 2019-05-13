#include "nn.h"

NN::NN() {
	//read.read();

	// set weights & biases
	// input -> hidden
	for (i = 0; i < NUMIN; i++) {
		BiasH[i] = fRand();
		for (j = 0; j < NUMHIDDEN; j++) {
			WeightIH[i][j] = fRand();
			DeltaWeightIH[i][j] = 0.0;
		}
	}
	// hidden -> output
	for (i = 0; i < NUMHIDDEN; i++) {
		for (j = 0; j < NUMOUT; j++) {
			WeightHO[i][j] = fRand();
			BiasO[j] = fRand();
			DeltaWeightHO[i][j] = 0.0;
		}
	}
	// training
	for (e = 0; e < EPOCH; e++) {
		for (p = 0; p < NUMPAT; p++) { // randomize order of training patterns
			ranpat[p] = p;
		}
		for (p = 0; p < NUMPAT; p++) {
			np = p + rando() * (NUMPAT + 1 - p);
			op = ranpat[p]; ranpat[p] = ranpat[np]; ranpat[np] = op;
		}
		//set inputs & targets
		//set();

		propagate();
		Error = 0;
		train();
		printf("\n");
		for (int l = 0; l < 10; l++)
			std::cout << "=";
		printf("\n");
		std::cout << "Epoch: " << e << "\t";
		std::cout << "Error: " << Error << "\n";
		for (int l = 0; l < 10; l++)
			std::cout << "=";
		printf("\n");
		system("PAUSE");
	}
}

void NN::propagate() {
	for (np = 0; np < NUMPAT; np++) {
		k = ranpat[np];
		// INPUT -> HIDDEN
		for (i = 0; i < NUMHIDDEN; i++) {
			sumH[k][i] = BiasH[i];
			for (j = 0; j < NUMIN; j++) {
				sumH[k][i] += input[k][j] * WeightIH[j][i];
			}
			// sig func
			hidden[k][i] = 1.0 / (1.0 + exp(-sumH[k][i]));
		}

		// HIDDEN -> OUTPUT
		for (i = 0; i < NUMOUT; i++) {
			sumO[k][i] = BiasO[i];
			for (j = 0; j < NUMHIDDEN; j++) {
				sumO[k][i] += hidden[k][j] * WeightHO[j][i];
			}
			// sig func
			output[k][i] = 1.0 / (1.0 + exp(-sumO[k][i]));
			Error += 0.5 * (target[k][i] - output[k][i]) * (target[k][i] - output[k][i]);
			DeltaO[i] = (target[k][i] - output[k][i]) * output[k][i] * (1.0 - output[k][i]);
		}
	}
}

void NN::train() {
	for (k = 0; k < NUMPAT; k++) {		
		
		for (j = 1; j <= NUMHIDDEN; j++) {    /* 'back-propagate' errors to hidden layer */
			sumDOW[j] = 0.0;
			for (k = 1; k <= NUMOUT; k++) {
				sumDOW[j] += WeightHO[j][k] * DeltaO[k];
			}
			DeltaH[j] = sumDOW[j] * hidden[k][j] * (1.0 - hidden[k][j]);
		}
		for (j = 1; j <= NUMHIDDEN; j++) {     /* update weights WeightIH */
			DeltaWeightIH[0][j] = momentum * DeltaH[j] + alpha * DeltaWeightIH[0][j];
			WeightIH[0][j] += DeltaWeightIH[0][j];
			for (i = 1; i <= NUMIN; i++) {
				DeltaWeightIH[i][j] = momentum * input[k][i] * DeltaH[j] + alpha * DeltaWeightIH[i][j];
				WeightIH[i][j] += DeltaWeightIH[i][j];
			}
		}
		for (i = 1; i <= NUMOUT; i++) {    /* update weights WeightHO */
			DeltaWeightHO[0][i] = momentum * DeltaO[i] + alpha * DeltaWeightHO[0][i];
			WeightHO[0][i] += DeltaWeightHO[0][i];
			for (j = 1; j <= NUMHIDDEN; j++) {
				DeltaWeightHO[j][i] = momentum * hidden[k][j] * DeltaO[i] + alpha * DeltaWeightHO[j][i];
				WeightHO[j][i] += DeltaWeightHO[j][i];
			}
		}
		/*
		// output
		for (i = 0; i < NUMHIDDEN; i++) {
			sumDOW[i] = 0.0;
			//lerr += .5 * (target[k][i] - output[k][i]) * (target[k][i] - output[k][i]); // output[k][i] * (1.0 - output[k][i]);
			//gerr = .5 * (target[i] - output[i]) ^ 2;
			for (j = 0; j < NUMOUT; j++) {
				sumDOW[i] += WeightHO[k][i] * DeltaO[i];
				BiasO[j] = momentum * DeltaO[j] + alpha * BiasO[j];
				BiasO[j] = (target[k][i] - output[k][i]) * output[k][i] * (target[k][i] - output[k][i]);
				for (int l = 0; l < NUMHIDDEN; l++) {
					// = lr * lerr * output[k][i] + momentum * deltaHO[j][i];
					WeightHO[j][i] += DeltaWeightHO[j][i];
					DeltaO[i] = DeltaWeightHO[j][i];
					sumOE += DeltaO[i];
				}
					Error += WeightHO[j][i] * lerr;
			}
			DeltaH[i] = sumDOW[i] * hidden[k][i] * (1.0 - hidden[k][i]);
		}
		// hidden
		for (i = 0; i < NUMHIDDEN; i++) {
			//lerr = hidden[k][i] * (1 - hidden[k][i]) * Error;
			BiasH[i] = momentum * DeltaH[i] + alpha * BiasH[i];
			for (j = 0; j < NUMIN; j++) {
				DeltaWeightIH[j][i] = momentum * input[k][j] * BiasH[i] + alpha * DeltaWeightIH[j][i];
				WeightIH[j][i] += DeltaWeightIH[j][i];
			}
		}*/
	} 
}

//set inputs & target
void NN::set() {
	read.randomize();

	memcpy(input, read.inputs, sizeof(input));
	memcpy(target, read.target, sizeof(target));
	/*for (j = 0; j < NUMPAT; j++) {
	for (i = 0; i < NUMIN; i++) {
	input[j][i] = read.inputs[j][i];
	}
	for (k = 0; k < NUMOUT; k++) {
	target[j][k] = read.target[j][k];
	}
	}*/
}

double NN::fRand() {
	double f = (double)rand() / RAND_MAX;
	return MINDOU + f * (MAXDOU - MINDOU);
}