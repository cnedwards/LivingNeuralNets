#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <stdlib.h>
#include "Math.hpp"
#include <vector>
#include "Neuron.hpp"
#include <iostream>

class NeuralNetwork
{
public:
	NeuralNetwork(int input, int output, int hidden);

	void reset();

	std::vector<bool> testCombination(std::vector<double> inputValues);

	double calculateFiringAmount();

	std::vector<Neuron> input;
    std::vector<Neuron> hidden;
	std::vector<Neuron> output;

	int inputNumber, hiddenNumber, outputNumber;

	void print(std::ostream &out);
	void read(std::istream &in);
};

#endif //NEURALNETWORK_HPP 