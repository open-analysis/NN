#include "NN3.h"

void Layer::calculate()
{
	int i, j;
	float sum;
	//Apply the formula for each neuron
	for (i = 0; i<neuroncount; i++)
	{
		sum = 0;//store the sum of all values here
		for (j = 0; j<inputcount; j++)
		{
			//Performing function
			sum += neurons[i]->weights[j] * layerinput[j]; //apply input * weight
		}
		sum += neurons[i]->wgain * neurons[i]->gain; //apply the gain or theta multiplied by the gain weight.
													 //sigmoidal activation function
		neurons[i]->output = 1.f / (1.f + exp(-sum));//calculate the sigmoid function
	}
}

void NN::propagate(const float *input)
{
	//The propagation function should start from the input layer
	//first copy the input vector to the input layer Always make sure the size
	//"array input" has the same size of inputcount
	std::memcpy(m_inputlayer.layerinput, input, m_inputlayer.inputcount * sizeof(float));
	//now calculate the inputlayer
	m_inputlayer.calculate();

	update(-1);//propagate the inputlayer out values to the next layer
	if (m_hiddenlayers)
	{
		//Calculating hidden layers if any
		for (int i = 0; i<m_hiddenlayercount; i++)
		{
			m_hiddenlayers[i]->calculate();
			update(i);
		}
	}

	//calculating the final statge: the output layer
	m_outputlayer.calculate();
}

//Main training function. Run this function in a loop as many times needed per pattern
float NN::train(const float *desiredoutput, const float *input, float alpha, float momentum)
{
	//function train, teaches the network to recognize a pattern given a desired output
	float errorg = 0; //general quadratic error
	float errorc; //local error;
	float sum = 0, csum = 0;
	float delta, udelta;
	float output;
	//first we begin by propagating the input
	propagate(input);
	int i, j, k;
	//the backpropagation algorithm starts from the output layer propagating the error  from the output
	//layer to the input layer
	for (i = 0; i<m_outputlayer.neuroncount; i++)
	{
		//calculate the error value for the output layer
		output = m_outputlayer.neurons[i]->output; //copy this value to facilitate calculations
												   //from the algorithm we can take the error value as
		errorc = (desiredoutput[i] - output) * output * (1 - output);
		//and the general error as the sum of delta values. Where delta is the squared difference
		//of the desired value with the output value
		//quadratic error
		errorg += (desiredoutput[i] - output) * (desiredoutput[i] - output);

		//now we proceed to update the weights of the neuron
		for (j = 0; j<m_outputlayer.inputcount; j++)
		{
			//get the current delta value
			delta = m_outputlayer.neurons[i]->dweights[j];
			//update the delta value
			udelta = alpha * errorc * m_outputlayer.layerinput[j] + delta * momentum;
			//update the weight values
			m_outputlayer.neurons[i]->weights[j] += udelta;
			m_outputlayer.neurons[i]->dweights[j] = udelta;

			//we need this to propagate to the next layer
			sum += m_outputlayer.neurons[i]->weights[j] * errorc;
		}

		//calculate the weight gain
		m_outputlayer.neurons[i]->wgain += alpha * errorc * m_outputlayer.neurons[i]->gain;

	}

	for (i = (m_hiddenlayercount - 1); i >= 0; i--)
	{
		for (j = 0; j<m_hiddenlayers[i]->neuroncount; j++)
		{
			output = m_hiddenlayers[i]->neurons[j]->output;
			//calculate the error for this layer
			errorc = output * (1 - output) * sum;
			//update neuron weights
			for (k = 0; k<m_hiddenlayers[i]->inputcount; k++)
			{
				delta = m_hiddenlayers[i]->neurons[j]->dweights[k];
				udelta = alpha * errorc * m_hiddenlayers[i]->layerinput[k] + delta * momentum;
				m_hiddenlayers[i]->neurons[j]->weights[k] += udelta;
				m_hiddenlayers[i]->neurons[j]->dweights[k] = udelta;
				csum += m_hiddenlayers[i]->neurons[j]->weights[k] * errorc;//needed for next layer

			}

			m_hiddenlayers[i]->neurons[j]->wgain += alpha * errorc * m_hiddenlayers[i]->neurons[j]->gain;

		}
		sum = csum;
		csum = 0;
	}

	//and finally process the input layer
	for (i = 0; i<m_inputlayer.neuroncount; i++)
	{
		output = m_inputlayer.neurons[i]->output;
		errorc = output * (1 - output) * sum;

		for (j = 0; j<m_inputlayer.inputcount; j++)
		{
			delta = m_inputlayer.neurons[i]->dweights[j];
			udelta = alpha * errorc * m_inputlayer.layerinput[j] + delta * momentum;
			//update weights
			m_inputlayer.neurons[i]->weights[j] += udelta;
			m_inputlayer.neurons[i]->dweights[j] = udelta;
		}
		//and update the gain weight
		m_inputlayer.neurons[i]->wgain += alpha * errorc * m_inputlayer.neurons[i]->gain;
	}

	//return the general error divided by 2
	return errorg / 2;

}