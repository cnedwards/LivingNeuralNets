#ifndef NEURON_HPP
#define NEURON_HPP

#include <stdlib.h>
#include "Math.hpp"
#include <iostream>

class Neuron
{
public:
	Neuron();
	Neuron(double bias, double weight, double threshold);

	void reset();

	
	double getWeight();
	double getBias();
	double getThreshold();
	bool getFired();
	double getInput();
	
	void setInput(double arg);
	void addToInput(double arg);
	void setFired(bool arg);

	double calculateFiringAmount();
	void calculateFired();
	
	void print(std::ostream &out);
	void read(std::istream &in);

private:
	double bias;
    double threshold;
	double input;
    ///output
    double weight;
    bool fired;
};

#endif //NEURON_HPP