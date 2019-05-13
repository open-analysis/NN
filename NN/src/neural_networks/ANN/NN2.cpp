#include "NN2.h"

N::N() {

	//read.readFlowers();
	//set();

	std::memcpy(Input, read.conditions, sizeof(Input));
	std::memcpy(Target, read.sport, sizeof(Input));

	// set input & target

	std::memset(Hidden, 0, sizeof(Hidden));
	std::memset(Output, 0, sizeof(Output));
	// set weights & biases
	// hidden -> output
	for (j = 0; j < NUMOUT; j++) {
		BiasO[j] = 0.05; // should a random number between 0 & 1
		DeltaBiasO[j] = 0;
		DeltaO[j] = 0;
		for (i = 0; i < NUMHID; i++) {
			WeightHO[i][j] = .05; // should a random number between 0 & 1
			DeltaWeightHO[i][j] = 0.0;
			SumDOW[i] = 0.0;
		}
	}
	// input -> hidden
	for (j = 0; j < NUMHID; j++) {
		BiasH[j] = .05; // should a random number between 0 & 1
		DeltaBiasH[j] = 0.0;
		DeltaH[j] = 0.0;
		SumDOW[j] = 0.0;
		for (i = 0; i < NUMIN; i++) {
			WeightIH[i][j] = 0.05; // should a random number between 0 & 1
			DeltaWeightIH[i][j] = 0.0;
		}
	}
	for (k = 0; k < SETS; k++)
		Error[k] = 0.0;

	// training
	for (e = 0; e <= EPOCH; e++) {
	//	set();
		TError = 0.0;
		propagate();
		printf("\nHidden:\n");
		for (k = 0; k < SETS; k++)
			for (i = 0; i < NUMHID; i++)
				std::cout << Hidden[k][i] << " ";
		printf("\nOutput:\n");
		for (k = 0; k < SETS; k++)
			for (i = 0; i < NUMOUT; i++)
				std::cout << Output[k][i] << " ";
		train();
		for (k = 0; k < SETS; k++)
			TError += Error[k];// * Error[k] * .5;
		printf("\n");
		std::cout << "================================================\n";
		std::cout << "Epoch: " << e << "\t" << "Error: " << TError << "\n";
		std::cout << "================================================\n";
		if (e == 1 || e == 5 || e == 10 || e == 15|| e == 25 || e == 50)
			std::cin.get();
	}
}

void N::propagate() {
	for (k = 0; k < SETS; k++) {
		Error[k] = 0;
		// input -> hidden
		for (i = 0; i < NUMHID; i++) {
			SumH[k][i] = BiasH[i];
			for (j = 0; j < NUMIN; j++) {
				SumH[k][i] += Input[k][j] * WeightIH[j][i];
				std::cout << "Hidden Sum " << SumH[k][i] << "\n";
			}
			Hidden[k][i] = 1.0 / (1.0 + exp(-SumH[k][i]));
		}

		// hidden -> output
		for (i = 0; i < NUMOUT; i++) {
			SumO[k][i] = BiasO[i];
			for (j = 0; j < NUMHID; j++) {
				SumO[k][i] += Hidden[k][j] * WeightHO[j][i];
				std::cout << "Output Sum " << SumO[k][i] << "\n";
			}
			Output[k][i] = 1.0 / (1.0 + exp(-SumO[k][i]));
			Error[k] += .5 * (Target[k][i] - Output[k][i]) * (Target[k][i] - Output[k][i]);
			DeltaO[i] = (Target[k][i] -Output[k][i]) * Output[k][i] * (1.0 - Output[k][i]);
		}
	}
}

void N::train() {
	for (k = 0; k < SETS; k++) {
		// getting the DeltaH
		for (j = 0; j < NUMHID; j++) {
			for (i = 0; i < NUMOUT; i++) {
				SumDOW[j] += WeightHO[j][i] * DeltaO[i];
			}
			DeltaH[j] = SumDOW[j] * Hidden[k][j] * (1.0 - Hidden[k][j]);
		}

		// WeightIH
		for (j = 0; j < NUMHID; j++) {
			DeltaBiasH[j] = ETA * DeltaH[j] + LR * DeltaBiasH[j];
			BiasH[j] = DeltaBiasH[j];
			for (i = 0; i < NUMIN; i++) {
				DeltaWeightIH[i][j] = ETA * Input[k][i] * DeltaH[j] + LR * DeltaWeightIH[j][i];
				WeightIH[i][j] += DeltaWeightIH[i][j];
			}
		}

		// WeightHO
		for (j = 0; j < NUMOUT; j++) {
			DeltaBiasO[j] = ETA * DeltaO[j] + LR * DeltaBiasO[j];
			BiasO[j] = DeltaBiasO[j];
			for (i = 0; i < NUMHID; i++) {
				DeltaWeightHO[i][j] = ETA * Hidden[k][i] * DeltaO[j] + LR * DeltaWeightHO[j][i];
				WeightHO[i][j] += DeltaWeightHO[i][j];
			}
		}
	}
}

void N::set() {
	read.randomize();
	std::memcpy(Input, read.inputs, sizeof(Input));
	std::memcpy(Target, read.target, sizeof(Target));
}